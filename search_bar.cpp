#include "search_bar.hpp"

#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include <qobjectdefs.h>


const char * SEARCH_QUERY = "https://en.wikipedia.org/w/api.php?action=query&generator=images&prop=imageinfo&iiprop=url&format=json&gimlimit=50&titles=";


QString parse_title(QString str)
{
   QString result = str.mid(5);
   return result;
}


void SearchBar::parseSearchResponse(QByteArray data)
{
   QJsonDocument doc = QJsonDocument::fromJson(data);

   if ( doc.isNull() || !doc.isObject() ) {
      mstatus.setText("failed to parse wikipedia response");
      return;
   }

   QJsonObject json = doc.object()["query"].toObject()["pages"].toObject();

   for ( QString pic : json.keys() ) {
      QJsonObject entry = json[pic].toObject();

      QString url = entry["imageinfo"].toArray()[0].toObject()["url"].toString();
      QString title = parse_title(entry["title"].toString());

      mpicListModel.addItem(title, url);
   }

   QString count = QString::number(mpicListModel.rowCount());
   mstatus.setText(QString("%1 results for: '%2'").arg(count, mlastQuery));
}


void SearchBar::handleSearchResponse(QNetworkReply * reply)
{
   if ( reply->error() == QNetworkReply::NoError ) parseSearchResponse(reply->readAll());
   else mstatus.setText("bad response: " + reply->errorString());

   reply->deleteLater();
}


void SearchBar::searchButtonPressed()
{
   if ( mlineEdit.text().length() == 0 ) return;

   QNetworkRequest request(QString(SEARCH_QUERY) + mlineEdit.text());
   QNetworkReply * reply = mnetManager.get(request);
   // replies are destroyed together with its networkManager so we dont have to worry about much
   connect(reply, &QNetworkReply::finished, [this, reply]() { handleSearchResponse(reply); });

   mlastQuery = mlineEdit.text();
   mstatus.setText(QString("fetching pictures for: '%1'").arg(mlastQuery));

   mpicListModel.clear();
   mpicLoader->clear();
}


SearchBar::SearchBar(PictureLoader * loader, QWidget * parent)
   : QWidget(parent), mpicLoader(loader)
{ 
   mstatus.setText("awaiting input...");
   mlineEdit.setPlaceholderText("type here");
   mlineEdit.setMaxLength(32);

   msearchButton.setText("search");
   connect(&msearchButton, &QPushButton::clicked, this, &SearchBar::searchButtonPressed);
   connect(&mlineEdit, &QLineEdit::returnPressed, this, &SearchBar::searchButtonPressed);

   setupStyles();
   setupLayout();
}


void SearchBar::setupStyles()
{
   msearchButton.setStyleSheet("font-size: 20px");
   mstatus.setStyleSheet("padding: 5px; font-style: italic; border: 1px solid #262626; font-size: 20px");
   mlineEdit.setStyleSheet("border: none; border-bottom: 1px solid #262626; font-size: 24px");

   mstatus.setAlignment(Qt::AlignCenter);
   mstatus.setWordWrap(true);
}


void SearchBar::setupLayout()
{
   mhbox.addWidget(&mlineEdit);
   mhbox.addWidget(&msearchButton);

   mvbox.addLayout(&mhbox);
   mvbox.addWidget(&mstatus);

   setLayout(&mvbox);

}


PictureListModel * SearchBar::picListModel()
{
   return &mpicListModel;
}
