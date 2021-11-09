#ifndef __IINFOTYPE__HPP__
#define __IINFOTYPE__HPP__

	enum typeDevice { PC_TYPE = 1, MONITOR_TYPE, PRINTER_TYPE, OTHER_TYPE };

	struct IInfoType {
		virtual typeDevice getType() const = 0;
	};
#endif // !__IINFOTYPE__HPP__

