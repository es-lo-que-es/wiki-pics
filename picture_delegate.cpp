#include "picture_delegate.hpp"

#include "picture.hpp"
#include "QPainter"


#define TITLE_FONT_SIZE 14
#define TITLE_HEIGHT 26
#define TITLE_OFFSET 10
#define IMAGE_PADDING 20


QSize PictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
   return msize;
}
   

void PictureDelegate::resize(QSize size)
{
   msize = size;
   emit sizeHintChanged(QModelIndex());
}


QRect paddedRect(QRect r, int padding)
{
   return QRect(
         r.x() + padding, 
         r.y() + padding,
         r.width() - padding*2,
         r.height() - padding*2
      );
}


void drawTitle(QPainter * painter, QRect r, QString str)
{
   painter->setPen(Qt::white);

   QFont font = painter->font();
   font.setBold(true);
   font.setPointSize(TITLE_FONT_SIZE);
   painter->setFont(font);

   QRect textRect = r;
   textRect.setHeight(TITLE_HEIGHT);

   painter->fillRect(textRect, Qt::black);

   textRect.setX(textRect.x() + TITLE_OFFSET);
   painter->drawText(textRect, Qt::AlignLeft, str);
}


QRect PictureDelegate::getPictureRect(QRect rect) const
{
   int cx = ((rect.x() + rect.width()) - msize.width()) / 2;

   rect.setX(cx);
   rect.setWidth(msize.width());

   rect = paddedRect(rect, IMAGE_PADDING);
   
   return rect;
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
   QVariant data = index.data();
   Picture * picture = reinterpret_cast<Picture*>(data.value<void*>());
   
   QPixmap pixmap = mpicLoader->getPicture(picture->url);
   QRect source = pixmap.rect();

   QRect target = getPictureRect(option.rect);

   painter->drawPixmap(target, pixmap, source);
   drawTitle(painter, option.rect, picture->name);
}


PictureDelegate::PictureDelegate(PictureLoader * picLoader, QSize size, QObject * parent)
   : QStyledItemDelegate(parent),
     mpicLoader(picLoader),
     msize(size)
{ }
