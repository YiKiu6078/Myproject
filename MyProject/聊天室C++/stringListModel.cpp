/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							stringListModel.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include "stringListModel.h"

StringListModel::StringListModel(const QStringList &strings, QObject *parent)
                                                      : QAbstractListModel(parent)
{
    stringList = strings;
}

StringListModel::~StringListModel()
{

}

/************************************************************
 函数名:                             insertRows
 功能:                               插入新行
 ************************************************************/
bool StringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row+count-1);
    for (int i=0; i<count; i++)
    {
    	stringList.insert(row, "");
    }
    endInsertRows();

    return true;
}

/************************************************************
 函数名:                             removeRows
 功能:                               删除行
 ************************************************************/
bool StringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row+count-1);
    for (int i=0; i<count; i++)
    {
    	stringList.removeAt(row);
    }
    endRemoveRows();

    return true;
}

/************************************************************
 函数名:                             setData
 功能:                               设置数据
 ************************************************************/
bool StringListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
    	stringList.replace(index.row(), value.toString());
    	emit dataChanged(index, index);
    	return true;
    }

    return false;
}

/************************************************************
 函数名:                             data
 功能:                               数据
 ************************************************************/
QVariant StringListModel::data( const QModelIndex & index, int role) const
{
    if (!index.isValid())
    {
    	return QVariant();
    }

    if (index.row() >= stringList.size())
    {
    	return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
    	return stringList.at(index.row());
    }
    else
    {
    	return QVariant();
    }
}

/************************************************************
 函数名:                             rowCount
 功能:                               计算行总数
 ************************************************************/
int StringListModel::rowCount(const QModelIndex & parent) const
{
    return stringList.count();
}


