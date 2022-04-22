QT += core network gui
TARGET =TcpServer
TEMPLATE =app
HEADERS += \
    tcpserver.h \
    TcpClientSocket.h \
    Server.h

SOURCES += \
    tcpserver.cpp \
    TcpClientSocket.cpp \
    Server.cpp \
    main.cpp

FORMS += \
    tcpserver.ui
