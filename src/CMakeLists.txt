set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(ledcontrol main.cpp LEDControl.cpp LED.cpp)
target_link_libraries(ledcontrol Qt5Core Qt5DBus)
install(TARGETS ledcontrol DESTINATION bin)

add_custom_target(dbus COMMAND qdbuscpp2xml -s -m -o ${CMAKE_CURRENT_BINARY_DIR}/ch.lindev.LEDControl.xml ${CMAKE_CURRENT_SOURCE_DIR}/LEDControl.h ${CMAKE_CURRENT_SOURCE_DIR}/LED.h)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ch.lindev.LEDControl.xml DESTINATION share/dbus-1/interfaces)
install(FILES ch.lindev.LEDControl.conf DESTINATION /etc/dbus-1/system.d)
