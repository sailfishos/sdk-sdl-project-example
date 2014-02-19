TEMPLATE = aux

# Source files
SOURCES += $$files(*.cpp)

# Headers
HEADERS += $$files(*.h)

# Application icon
OTHER_FILES += $$files(*.desktop) $$files(*.png)

# Other data files
OTHER_FILES += $$files(data/*)

# Build system files
OTHER_FILES += makefile $$files(rpm/*.spec)
