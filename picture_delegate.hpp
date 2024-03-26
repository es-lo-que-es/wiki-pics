#ifndef PICTURE_DELEGATE_HEADER
#define PICTURE_DELEGATE_HEADER

#include "QStyledItemDelegate"
#include "picture_loader.hpp"


class PictureDelegate : public QStyledItemDelegate {
   
 public:
   void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
   QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

   PictureDelegate(PictureLoader * picLoader, QSize size, QObject * parent = nullptr);
   void resize(QSize size);

 private:
   QRect getPictureRect(QRect optionRect) const;

   PictureLoader * mpicLoader;
   QSize msize;

};


#endif
