#ifndef PICTURE_LIST_VIEW_HEADER
#define PICTURE_LIST_VIEW_HEADER

#include "QListView"
#include "picture_delegate.hpp"
#include "picture_loader.hpp"


class PictureListView : public QListView {

 public:
   PictureListView(PictureLoader * loader, QWidget * parent = nullptr);
 
 protected:
   void resizeEvent(QResizeEvent *event);

 private:
   PictureDelegate mdelegate;
   void resizeDelegate();
   
};


#endif
