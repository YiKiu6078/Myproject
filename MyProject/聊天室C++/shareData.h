/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							shareData.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef SHAREDATA_H_
#define SHAREDATA_H_

const int DEFAULT_GROUP_INDEX = 0;                             //默认分组号

const int DEFAULT_GROUP_COUNT = 3;                             //缺省好友分组数量

const int MSGPORT = 4808;                                      //數据发送端口

const int FILEPORT = 8010;                                     //传送文件端口

const unsigned long MAXSIZE = 1048576;                  //读文件最大尺寸1M

const QString DRIVER = "QSQLITE";                              //数据库驱动

const QString DATABASE_NAME = "database/linux_chat.db";        //数据库名

const int DEVIECE_INDEX = 1;                                   //网卡驱动设备

const QString LOOKBACKIP = "127.0.0.1";                        //设置本机环回IP

const QString DEFAULT_LOGO = "logo/logo.png";                  //默认应用程序logo

const QString DEFAULT_PATH = "head";                           //本地头像的相对路径

const QString DEFAULT_HEAD = "head/2.png";                     //默认头像

const QString DEFAULT_USER_NAME = "Adminstrator";              //默认用户名

/**********************************通信协议声明************************/

const unsigned int HEADID = 0X55AA;                            //通信协议标识

enum ACTION{LOGIN,OUT,SENDMSG,SENDFILE,ACCEPTFILE,REFUSEFILE}; //消息类型表示

struct message                                                 //通信协议的消息结构体
{
	unsigned int headId;                                       //通信消息标识
	unsigned int msgFlag;                                      //消息的标识

	unsigned int nameLen;                                      //用户名长度
	unsigned int headLen;                                      //头像长度
	unsigned int hostNameLen;                                  //主机名长度
	unsigned int IpLen;                                        //IP长度
	unsigned int writeLen;                                     //个人签名长度

	unsigned int msgLen;                                       //发送消息长度
	unsigned int fileSize;                                     //文件尺寸
	unsigned int fileUrlLen;                                   //发送文件名长度
};

typedef struct message MSG;                                    //重命名消息结构体

/*********************************通信协议定义结束************************/


#endif /* SHAREDATA_H_ */
