TEMPLATE = subdirs

SUBDIRS += \    
    src/core \
    src/console \
    src/widgetApp \
    tests

tests.depends = src/core
src/console.depends = src/core
src/widgetApp.depends = src/core
