TEMPLATE = subdirs

core.subdir = src/core

console.subdir = src/console

widgetApp.subdir = src/widgetApp

SUBDIRS += \
    core \
    console \
    widgetApp \
    tests \

tests.depends = core
console.depends = core
widgetApp.depends = core
