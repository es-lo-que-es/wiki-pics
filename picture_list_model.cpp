#include "picture_list_model.hpp"
#include "picture.hpp"
#include "QDebug"


PictureListModel::PictureListModel(QObject * parent)
   : QAbstractListModel(parent) 
{ }


int PictureListModel::rowCount(const QModelIndex &parent) const 
{
   return mdata.size();
}


QVariant PictureListModel::data(const QModelIndex &index, int role) const
{
   if ( !index.isValid() ) return QVariant();
   if ( role != Qt::DisplayRole ) return QVariant();

   return QVariant::fromValue((void*)&mdata[index.row()]);
}


void PictureListModel::addItem(QString name, QString url)
{
   emit beginInsertRows(QModelIndex(), mdata.size(), mdata.size());
   mdata.push_back({name, url});
   emit endInsertRows();
}


void PictureListModel::clear()
{
   emit beginResetModel();
   mdata.clear();
   emit endResetModel();
}
