#include <QtGui/QApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tcpserver w;
    w.show();
    
    return a.exec();
}
