#include <QtGui>
#include <QSqlDatabase>
#include "MasterControl.h"
#include "shareData.h"

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(DEFAULT_LOGO));                     //设置应用程序的图标

    MasterControl mc;                                                                    //主控制类

    if (!mc.getIsRight() || !mc.initUserInfo())                                       //判断是否初始化成功
	{
		return 1;
	}
	else
	{
		mc.sendPersonalInfo();                                                           //广播形式发送个人登录信息
		mc.showWindow();                                                                 //显示用户界面

		QObject::connect(&app, SIGNAL(lastWindowClosed()), &mc, SLOT(outLogin()));       //广播形式发送退出信息
		QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(closeAllWindows()));
	}

	return app.exec();
}
