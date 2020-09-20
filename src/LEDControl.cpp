#include "LEDControl.h"
#include "LED.h"

#include <QDBusConnection>
#include <QTimer>
#include <QDir>

#include <iostream>

extern "C" {
#include <fcntl.h>
#include <unistd.h>
}

LEDControl::LEDControl(int &argc, char **&argv):QCoreApplication(argc, argv) {
	setApplicationName("LEDControl");
	setOrganizationName("LinDev");
	setOrganizationDomain("lindev.ch");
	
	if(!QDBusConnection::systemBus().registerService("ch.lindev.LEDControl")) {
		std::cerr << "Failed to register on system bus" << std::endl;
		QTimer::singleShot(0, this, &QCoreApplication::quit);
		return;
	}
	QDBusConnection::systemBus().registerObject("/", this, QDBusConnection::ExportScriptableSlots);

	QDir d("/sys/class/leds");
	for(QString l : d.entryList(QDir::Dirs|QDir::NoDotAndDotDot)) {
		LED *led=new LED(QStringLiteral("/sys/class/leds/") + l, this);
		if(!QDBusConnection::systemBus().registerObject(QStringLiteral("/") + l.replace(':', "_"), led, QDBusConnection::ExportScriptableSlots)) {
			std::cerr << "Failed to register /" << qPrintable(l) << std::endl;
		}
		_leds.insert(l, led);
	}
}

QStringList LEDControl::LEDs(QString type) {
	QStringList leds;
	for(QMap<QString,LED*>::ConstIterator it=_leds.begin(); it!=_leds.end(); it++) {
		if(type.isEmpty() || it.key().endsWith(QStringLiteral("_") + type))
			leds << it.key();
	}
	return leds;
}
