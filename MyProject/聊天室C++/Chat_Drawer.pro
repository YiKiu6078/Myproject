TEMPLATE = app
TARGET = Chat_Drawer
QT += core \
    gui \
    sql \
    network
HEADERS += UpdateGroupWnd.h \
    stringListModel.h \
    ManagerGroup.h \
    NewGroupWnd.h \
    TcpServerThread.h \
    TcpClient.h \
    TcpServer.h \
    TcpThread.h \
    ftpserverdialog.h \
    ftpclientdialog.h \
    chatwindow.h \
    MasterControl.h \
    chat_drawer.h \
    HostInfo.h \
    InfoDialog.h \
    shareData.h \
    ToolButton.h \
    User.h
SOURCES += UpdateGroupWnd.cpp \
    stringListModel.cpp \
    ManagerGroup.cpp \
    NewGroupWnd.cpp \
    TcpServerThread.cpp \
    TcpClient.cpp \
    TcpServer.cpp \
    TcpThread.cpp \
    ftpserverdialog.cpp \
    ftpclientdialog.cpp \
    chatwindow.cpp \
    MasterControl.cpp \
    chat_drawer.cpp \
    HostInfo.cpp \
    InfoDialog.cpp \
    main.cpp \
    ToolButton.cpp \
    User.cpp
FORMS += chat_drawer.ui
RESOURCES += 
