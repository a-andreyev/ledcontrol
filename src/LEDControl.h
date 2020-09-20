#pragma once

#include <QCoreApplication>
#include <QDBusObjectPath>
#include <QString>
#include <QStringList>
#include <QMap>

class LED;

class LEDControl:public QCoreApplication {
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "ch.lindev.LEDControl")
public:
	LEDControl(int &argc, char **&argv);
public Q_SLOTS:
	// D-Bus interface
	Q_SCRIPTABLE QStringList LEDs(QString type=QString());
protected:
	QMap<QString,LED*>	_leds;
};
