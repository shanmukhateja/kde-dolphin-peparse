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
include(FeatureSummary)

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
    src/hello-dolphin-plugin.cpp
)
# Set properties for the shared library
set_target_properties(hello-dolphin-plugin PROPERTIES
    VERSION "${RELEASE_SERVICE_VERSION}"
    SOVERSION "1"
)
target_link_libraries(hello-dolphin-plugin KF6::CoreAddons KF6::XmlGui)
target_link_libraries(hello-dolphin-plugin KF6::KIOCore KF6::KIOFileWidgets KF6::KIOWidgets)

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
install(TARGETS hello-dolphin-plugin DESTINATION ${PLUGIN_INSTALL_DIR})

# Ensure that CMake uses the specified binary directory by adding an empty add_subdirectory call
# add_subdirectory("./build/")
