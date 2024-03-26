#ifndef SEARCH_BAR_HEADER
#define SEARCH_BAR_HEADER

#include "QLabel"
#include "QWidget"
#include "QLineEdit"
#include "QHBoxLayout"
#include "QPushButton"
#include "QNetworkAccessManager"
#include "picture_list_model.hpp"
#include "picture_loader.hpp"


class SearchBar : public QWidget {
   
 public:
   SearchBar(PictureLoader * loader, QWidget * parent = nullptr);
   PictureListModel * picListModel();
  
 private slots:
   void searchButtonPressed();

 private:
   void handleSearchResponse(QNetworkReply * reply);
   void parseSearchResponse(QByteArray data);
   void setupStyles();
   void setupLayout();

   QNetworkAccessManager mnetManager;

   PictureListModel mpicListModel;
   PictureLoader * mpicLoader;

   QVBoxLayout mvbox;
   QHBoxLayout mhbox;

   QPushButton msearchButton;
   QLineEdit mlineEdit;

   QString mlastQuery;
   QLabel mstatus;

};


#endif

