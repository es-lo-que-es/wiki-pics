#ifndef PICTURE_LIST_MODEL_HEADER
#define PICTURE_LIST_MODEL_HEADER

#include "picture.hpp"
#include "QAbstractListModel"


class PictureListModel : public QAbstractListModel {
   Q_OBJECT

 public:
   explicit PictureListModel(QObject * parent = nullptr);

   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role) const override;

   void addItem(QString name, QString url);
   void clear();

 private:
   QVector<Picture> mdata;

};


#endif

