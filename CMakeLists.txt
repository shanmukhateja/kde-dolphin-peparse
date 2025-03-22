# Set minimum CMake version
cmake_minimum_required(VERSION 3.16)
# Set project name
project(hello-dolphin-plugin)
set(QT_MIN_VERSION "6.8.2")
set(KF_MIN_VERSION "6.11.0")

# Ensure the build directory is set early in the configuration
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build" CACHE PATH "Build directory" FORCE)

# ECM setup
find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(QtVersionOption)
include(ECMSetupVersion)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMDeprecationSettings)
include(ECMOptionalAddSubdirectory)

#include_directories("/usr/include/pe-parse")
find_package(pe-parse REQUIRED)

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Core5Compat
    Widgets
    Network
    DBus
)
find_package(KF6 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    XmlGui
    I18n
    KIO
    TextWidgets
    Config
    CoreAddons
    WidgetsAddons
    Solid
)

# Add the shared library target
add_library(
    hello-dolphin-plugin
    SHARED
    src/hello-dolphin-plugin.h
    src/hello-dolphin-plugin.cpp
    src/pe-parser-wrapper.h
    src/pe-parser-wrapper.cpp
)

# Set properties for the shared library
set_target_properties(hello-dolphin-plugin PROPERTIES
    VERSION "${RELEASE_SERVICE_VERSION}"
    SOVERSION "1"
)

target_link_libraries(hello-dolphin-plugin KF6::CoreAddons KF6::XmlGui)
target_link_libraries(hello-dolphin-plugin KF6::KIOCore KF6::KIOFileWidgets KF6::KIOWidgets)
target_link_libraries(hello-dolphin-plugin pe-parse::pe-parse)

# Include directories for the project
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Widgets_INCLUDE_DIRS}
    ${KF6_INCLUDE_DIRS}
)

# Ensure that all output directories are set explicitly to the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set the destination for installation if needed
install(TARGETS hello-dolphin-plugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/propertiesdialog/)
install(FILES hello-dolphin-plugin.json DESTINATION  ${KDE_INSTALL_PLUGINDIR}/kf6/propertiesdialog/)

#install(TARGETS hello-dolphin-plugin DESTINATION ~/.local/lib/qt6/plugins/kf6/propertiesdialog/hello-dolphin-plugin)
#install(FILES hello-dolphin-plugin.json DESTINATION  ~/.local/lib/qt6/plugins/kf6/propertiesdialog/hello-dolphin-plugin)
