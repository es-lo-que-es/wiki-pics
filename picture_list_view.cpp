#include "picture_list_view.hpp"

#define MIN_ITEM_SIDE 100


PictureListView::PictureListView(PictureLoader * loader, QWidget * parent)
   : QListView(parent), mdelegate(loader, QSize())
{
   connect(loader, &PictureLoader::pictureLoaded, [this](){ update(); });

   setStyleSheet("QScrollBar { height: 0px; width: 0px }");
   setItemDelegate(&mdelegate);
   resizeDelegate();
}


void PictureListView::resizeEvent(QResizeEvent * event)
{
   QListView::resizeEvent(event);
   resizeDelegate();
}


void PictureListView::resizeDelegate()
{
   int side = std::max(std::min(width(), height()), MIN_ITEM_SIDE);
   mdelegate.resize(QSize(side, side));
}
