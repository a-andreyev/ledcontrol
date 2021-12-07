cmake_minimum_required(VERSION 3.18.2)
project(ledcontrol VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(QT_MIN_VERSION "5.15.0")
add_definitions(${QT_DEFINITIONS} -DQT_DISABLE_DEPRECATED_BEFORE=0x050f00)
set(KF5_MIN_VERSION "5.88.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

add_subdirectory(src)
