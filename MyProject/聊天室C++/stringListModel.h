/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							stringListModel.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef STRINGLISTMODEL_H_
#define STRINGLISTMODEL_H_


/*******************************************************
 类名:                           StringListModel
 功能:                           继承于QAbstractListModel创建模型
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

#include <QtGui>

class StringListModel : public QAbstractListModel
{
	Q_OBJECT

public:

	StringListModel(const QStringList &strings, QObject *parent = 0);
	virtual ~StringListModel();

public:																							//重新实现父类虚函数

	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
	virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
	virtual bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

private:

	QStringList stringList;
};

#endif /* STRINGLISTMODEL_H_ */
