TEMPLATE = app
TARGET = harbour-sdltest
QT =

PKGCONFIG += sdl2 egl glesv1_cm glesv2 SDL2_image SDL2_ttf SDL2_mixer
CONFIG += link_pkgconfig

# Source files
SOURCES += $$files(*.cpp)

# Headers
HEADERS += $$files(*.h)

# Application icon
OTHER_FILES += $$files(*.desktop)

# Other data files
OTHER_FILES += $$files(data/*)

# Build system files
OTHER_FILES += makefile $$files(rpm/*.spec)

# Installation directories
isEmpty(INSTALL_PREFIX) {
    INSTALL_PREFIX = /usr
}

isEmpty(INSTALL_BIN_DIR) {
    INSTALL_BIN_DIR = $$INSTALL_PREFIX/bin
}

isEmpty(INSTALL_DATA_DIR) {
    INSTALL_DATA_DIR = $$INSTALL_PREFIX/share
}

# Data files
data_files_install.files = data/*
data_files_install.path = $$INSTALL_DATA_DIR/harbour-sdltest

# Desktop
desktop_entry.files = $$files(*.desktop)
desktop_entry.path = $$INSTALL_DATA_DIR/applications
desktop_entry.CONFIG += no_check_exist

# Icon
icon_file.files = $$files(*.png)
icon_file.path = $$INSTALL_DATA_DIR/icons/hicolor/86x86/apps

target.path = $$INSTALL_BIN_DIR
INSTALLS += target desktop_entry icon_file data_files_install
