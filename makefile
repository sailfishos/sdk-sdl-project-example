# Name of the application
TARGET := harbour-sdltest

# Source code files
SOURCES := sdltest.cpp common.cpp

# pkg-config requirements
PKGS := sdl2 glesv2

DESKTOP_FILE := $(patsubst %,%.desktop,$(TARGET))
ICON_FILE := $(patsubst %,%.png,$(TARGET))
DESKTOPS := $(patsubst %,%.desktop,$(TARGET))
DATA_FILES := $(wildcard data/*)

DESTDIR ?=
PREFIX ?= /usr

DATADIR := $(PREFIX)/share/$(TARGET)/

CXXFLAGS ?= -g
CXXFLAGS += -DDATADIR=\"$(DATADIR)\"

PKGCONFIG_FLAGS := $(shell pkg-config --libs --cflags $(PKGS))

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(PKGCONFIG_FLAGS)

INSTALLMSG := @echo
INSTALLCMD := @install

install: $(TARGET) $(DESKTOP_FILE) $(ICON_FILE)
	$(INSTALLMSG) Installing binary
	$(INSTALLCMD) -d $(DESTDIR)$(PREFIX)/bin/
	$(INSTALLCMD) -m755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/
	$(INSTALLMSG) Installing .desktop file
	$(INSTALLCMD) -d $(DESTDIR)$(PREFIX)/share/applications/
	$(INSTALLCMD) -m644 $(DESKTOP_FILE) $(DESTDIR)$(PREFIX)/share/applications/
	$(INSTALLMSG) Installing icon file
	$(INSTALLCMD) -d $(DESTDIR)$(PREFIX)/share/icons/hicolor/86x86/apps/
	$(INSTALLCMD) -m644 $(ICON_FILE) $(DESTDIR)$(PREFIX)/share/icons/hicolor/86x86/apps/
	$(INSTALLMSG) Installing data files
	$(INSTALLCMD) -d $(DESTDIR)$(DATADIR)
	$(INSTALLCMD) -m644 $(DATA_FILES) $(DESTDIR)$(DATADIR)

clean:
	rm -f $(TARGET)

.PHONY: all install clean
