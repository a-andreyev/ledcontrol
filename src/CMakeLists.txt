set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(KDEInstallDirs)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core DBus)
add_executable(ledcontrol main.cpp LEDControl.cpp LED.cpp)

target_link_libraries(ledcontrol
    Qt5::Core
    Qt5::DBus
    )
install(TARGETS ledcontrol DESTINATION bin)

add_custom_command(TARGET ledcontrol
    POST_BUILD
    COMMAND qdbuscpp2xml -s -m -o ${CMAKE_CURRENT_BINARY_DIR}/ch.lindev.LEDControl.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/LEDControl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LED.h
    COMMENT "Generating D-Bus XML with qdbuscpp2xml"
    VERBATIM)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ch.lindev.LEDControl.xml DESTINATION ${DBUS_INTERFACES_INSTALL_DIR})
install(FILES ch.lindev.LEDControl.conf DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dbus-1/system.d")
