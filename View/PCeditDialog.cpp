
#include "PCeditDialog.hpp"

PCeditDialog::PCeditDialog(DataManager* dm, QWidget* parent):
	ui {new Ui::PCeditDialog()},
	AbstractEditDialog(dm, parent)
{
	ui->setupUi(this);
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
			if (ui->rbHDDtype)
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

