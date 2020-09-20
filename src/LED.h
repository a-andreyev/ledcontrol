#pragma once

#include <QObject>
#include <QString>

class LED:public QObject {
	Q_OBJECT
public:
	LED(QString const &path, QObject *parent=nullptr);
	Q_CLASSINFO("D-Bus Interface", "ch.lindev.LED")
public Q_SLOTS:
	Q_SCRIPTABLE bool turnOn(int brightness=100);
	Q_SCRIPTABLE bool turnOff();
	Q_SCRIPTABLE int setBrightness(int brightness=100);
	Q_SCRIPTABLE int brightness();
	Q_SCRIPTABLE int maxBrightness();
	Q_SCRIPTABLE bool flash();
	Q_SCRIPTABLE bool flash(int duration);
protected:
	QString	_path;
};
