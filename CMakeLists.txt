cmake_minimum_required(VERSION 3.14)

project(hw9 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(hw9
  main.cpp
  SensorMetric.h
  Sensor.h Sensor.cpp
  Logger.h Logger.cpp
  Analyzer.h Analyzer.cpp
  SensorData.h SensorData.cpp
        Config.hpp
)
target_link_libraries(hw9 Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS hw9
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
