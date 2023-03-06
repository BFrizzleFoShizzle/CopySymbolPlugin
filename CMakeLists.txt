cmake_minimum_required(VERSION 3.12)
project(copy-symbol-plugin)

find_package(Cutter REQUIRED)
find_package(Rizin REQUIRED)

set(CUTTER_INSTALL_PLUGDIR "${Cutter_USER_PLUGINDIR}" CACHE STRING "Directory to install Cutter plugin into")

set(CMAKE_AUTOMOC ON)

add_library(copy_symbol_plugin MODULE
    CopySymbolPlugin.h
    CopySymbolPlugin.cpp)
    
target_link_libraries(copy_symbol_plugin PRIVATE Cutter::Cutter Rizin::Core)
install(TARGETS copy_symbol_plugin DESTINATION "${CUTTER_INSTALL_PLUGDIR}")
