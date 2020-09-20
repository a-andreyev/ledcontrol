#include "LEDControl.h"

#include <QDBusConnection>
#include <QDBusConnectionInterface>

#include <iostream>

int main(int argc, char **argv) {
	if(QDBusConnection::systemBus().interface()->isServiceRegistered("ch.lindev.ledcontrol")) {
		std::cerr << "Interface already registered on D-BuS" << std::endl;
		return 1;
	}

	LEDControl l(argc, argv);
	l.exec();
}
