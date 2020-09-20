#include "LED.h"

#include <QTimer>
#include <QFile>

#include <iostream>
#include <cstdlib>

extern "C" {
#include <fcntl.h>
#include <unistd.h>
}

LED::LED(QString const &path, QObject *parent):QObject(parent),_path(path) {
}

bool LED::turnOn(int brightness) {
	int fd=open(QFile::encodeName(_path + "/brightness"), O_WRONLY);
	if(fd < 0) {
		std::cerr << strerror(errno) << std::endl;
		return false;
	}
	write(fd, "1", 1);
	close(fd);
	return true;
}

bool LED::turnOff() {
	int fd=open(QFile::encodeName(_path + "/brightness"), O_WRONLY);
	if(fd < 0) {
		std::cerr << strerror(errno) << std::endl;
		return false;
	}
	write(fd, "0", 1);
	close(fd);
	return true;
}

int LED::setBrightness(int brightness) {
	QString const b = _path + "/brightness";
	char buf[16];
	snprintf(buf, 16, "%u", brightness);
	int fd = open(QFile::encodeName(b), O_RDWR);
	if(fd < 0)
		return -1;
	write(fd, buf, strlen(buf));
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, 16);
	close(fd);
	return atoi(buf);
}

int LED::brightness() {
	char buf[16];
	QString const mb = _path + "/brightness";
	int fd = open(QFile::encodeName(mb), O_RDONLY);
	if(fd < 0)
		return -1;
	int r = read(fd, buf, 16);
	if(r <= 0) {
		close(fd);
		return -1;
	}
	buf[r]=0;
	return atoi(buf);
}

int LED::maxBrightness() {
	char buf[16];
	QString const mb = _path + "/max_brightness";
	int fd = open(QFile::encodeName(mb), O_RDONLY);
	if(fd < 0)
		return -1;
	int r = read(fd, buf, 16);
	if(r <= 0) {
		close(fd);
		return -1;
	}
	buf[r]=0;
	return atoi(buf);
}

bool LED::flash() {
	QString const fs = _path + "/flash_strobe";
	if(QFile::exists(fs)) {
		int fd=open(QFile::encodeName(fs), O_WRONLY);
		if(fd >= 0) {
			write(fd, "1", 1);
			close(fd);
			return true;
		}
	}
	// No flash functionality in the kernel driver, so let's fake it
	if(turnOn()) {
		QTimer::singleShot(250, this, &LED::turnOff);
		return true;
	}
	return false;
}

bool LED::flash(int duration) {
	QString const fs = _path + "/flash_strobe";
	if(QFile::exists(fs)) {
		QString const t = _path + "/flash_timeout";
		int fd=open(QFile::encodeName(t), O_WRONLY);
		char buf[16];
		snprintf(buf, 16, "%u", duration);
		write(fd, buf, strlen(buf));
		close(fd);

		fd=open(QFile::encodeName(fs), O_WRONLY);
		if(fd >= 0) {
			write(fd, "1", 1);
			close(fd);
			return true;
		}
	}
	// No flash functionality in the kernel driver, so let's fake it
	if(turnOn()) {
		QTimer::singleShot(duration / 1000, this, &LED::turnOff);
		return true;
	}
	return false;
}
