
#include "PCeditDialog.hpp"

PCeditDialog::PCeditDialog(DataManager* dm, QWidget* parent):
	ui {new Ui::PCeditDialog()},
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
}

PCeditDialog::PCeditDialog(DataManager* dm, Item* item, QWidget* parent)
	:AbstractEditDialog(dm, parent),
	ui{ new Ui::PCeditDialog() }
{
	ui->setupUi(this);
	ui->leName->setText(QString::fromStdString(item->getName()));
	ui->leNumber->setText(QString::number(item->getInventoryNumber()));
	auto pITEquipment{ item->getITequipment().get() };
	PC* pc = dynamic_cast<PC*>(pITEquipment);
	
	auto type{ pc->getTypePC() };
	switch (type)
	{
	case PC::TypePC::SystemBlock:
		ui->rbPCtype->setChecked(true);
		break;
	case PC::TypePC::Laptop:
		ui->rbLaptopType->setChecked(true);
		break;
	case PC::TypePC::Monoblock:
		ui->rbMonoblockType->setChecked(true);
		break;
	}

	auto [motherboard, _cpu, grapicCard, ram, storageDevice, operSystem] 
		=  *pc->getComplectComponents();

	ui->leMotherboard  ->setText(QString::fromStdString(motherboard.getName()));
	ui->leCPUname	   ->setText(QString::fromStdString(_cpu.getName()));
	ui->leCPUfrequency ->setText(QString::number(_cpu.getFrequency()));
	ui->leVideocardName->setText(QString::fromStdString(grapicCard.getName()));
	ui->leVideocardVolumeRam->setText(QString::number(grapicCard.getVolume()));

	switch (storageDevice.getStorageDeviceType())
	{
	case StorageDevice::typeStorageDevice::HDD:
		ui->rbHDDtype->setChecked(true); 
		break;
	case StorageDevice::typeStorageDevice::SSD:
		ui->rbSSDtype->setChecked(true);
		break;
	}
	ui->leStorageDeviceName	 ->setText(QString::fromStdString(storageDevice.getName()));
	ui->leStorageDeviceVolume->setText(QString::number(storageDevice.getVolume()));

	ui->leRAMvolume->setText(QString::number(ram.getVolume()));
	ui->leOperationSystem->setText(QString::fromStdString(operSystem));
}

PCeditDialog::~PCeditDialog() {
	delete ui;
}

Item* PCeditDialog::createItem()
{
	auto number { ui->leNumber->text().toLongLong() };

	auto type{ [&]()->PC::TypePC {
		if (ui->rbPCtype->isChecked()) {
			return PC::TypePC::SystemBlock;
		}
		else if (ui->rbLaptopType->isChecked()) {
			return PC::TypePC::Laptop;
		}
		else {
			return  PC::TypePC::Monoblock;
		}
	}() };

	auto name		 { ui->leName->text().toStdString() };
	auto motherboard { ui->leMotherboard->text().toStdString() };
	auto _cpu		 { std::make_pair(
		ui->leCPUname->text().toStdString(),
		ui->leCPUfrequency->text().toFloat())
	};
	auto graphicCard{ std::make_pair(
		ui->leVideocardName->text().toStdString(),
		ui->leVideocardVolumeRam->text().toFloat())
	};
	auto ram{ ui->leRAMvolume->text().toFloat() };

	auto storageDevice{ std::make_tuple(
		ui->leStorageDeviceVolume->text().toFloat(),
		ui->leStorageDeviceName->text().toStdString(),
		[&]()->StorageDevice::typeStorageDevice {
			if (ui->rbHDDtype->isChecked())
				return StorageDevice::typeStorageDevice::HDD;
			else
				return StorageDevice::typeStorageDevice::SSD;
		}())
	};
	auto operationSystem{ ui->leOperationSystem->text().toStdString() };
	auto data{ 
		std::make_tuple(
			name, type, 
			motherboard, _cpu,
			graphicCard, ram, 
			storageDevice,
			operationSystem) 
	};
	dataManager->setDataPC(std::move(data));
	auto item{std::move(
		dataManager->createItem(
			DataManager::typeITEquipment::typePC,
			number,
			dataManager->getCurrentLocationIndexes()
	)) };
	return item;
}

