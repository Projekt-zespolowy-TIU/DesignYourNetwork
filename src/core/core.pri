BASEDIR   = $${PWD}
INCLUDEPATH += $${BASEDIR}

LIBRARY_OUT_PWD = $$clean_path($$OUT_PWD/$$relative_path($$PWD, $$_PRO_FILE_PWD_))

win32-g++: LIBS += -L$$LIBRARY_OUT_PWD/ -lcore
else:win32:!win32-g++:CONFIG(release, debug|release): LIBS += -L$$LIBRARY_OUT_PWD/release/ -lcore
else:win32:!win32-g++:CONFIG(debug, debug|release): LIBS += -L$$LIBRARY_OUT_PWD/debug/ -lcore
else:unix: LIBS += -L$$LIBRARY_OUT_PWD/ -lcore
