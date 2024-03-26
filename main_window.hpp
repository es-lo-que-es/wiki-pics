#ifndef MAIN_WINDOW_HEADER
#define MAIN_WINDOW_HEADER

#include "picture_list_view.hpp"
#include "picture_loader.hpp"
#include "search_bar.hpp"

#include "QVBoxLayout"
#include "QListView"
#include "QWidget"
#include "QLabel"
#include <QHBoxLayout>


class MainWindow : public QWidget {

 public:
   explicit MainWindow(QWidget * parent = nullptr);

 private:
   void setupLayout();

   PictureLoader mpicLoader;
   QVBoxLayout mvbox;
   QHBoxLayout mhbox;

   PictureListView mview;
   SearchBar msearchBar;
   QLabel mtitle;

};



#endif
