#include "picture_loader.hpp"
#include "QNetworkReply"
#include "QObject"
#include "QPainter"


void drawPixmapText(QPixmap * pixmap, QString str)
{
   pixmap->fill(Qt::white);

   QPainter painter(pixmap);

   QFont font("Monospace", 16);
   painter.setFont(font);
   painter.setPen(Qt::black);

   painter.drawText(pixmap->rect(), Qt::AlignCenter, str);
   painter.end(); 
}


PictureLoader::PictureLoader()
{
   mloading = QPixmap(100, 100);
   mfailed = QPixmap(100, 100);
   
   drawPixmapText(&mloading, "loading");
   drawPixmapText(&mfailed, "failed");
}


QPixmap PictureLoader::getPicture(QString url)
{
   if ( !mpictureMap.contains(url) ) {
      mpictureMap[url] = mloading;
      loadPicture(url);
   }

   return mpictureMap[url];
}


void PictureLoader::handleResponse(QNetworkReply * reply, QString url)
{
   if ( reply->error() == QNetworkReply::NoError ) {

      // in case reply got here a bit too late
      if ( mpictureMap.contains(url) ) {

         bool ok = mpictureMap[url].loadFromData(reply->readAll());
         if ( !ok ) mpictureMap[url] = mfailed;
      }

   } else {
      qWarning() << "error: " << reply->errorString();
   }

   emit pictureLoaded();
   reply->deleteLater();
}


void PictureLoader::loadPicture(QString url)
{
   QNetworkRequest request(url);
   QNetworkReply * reply = mnetManager.get(request);

   QObject::connect(reply, &QNetworkReply::finished, [this, reply, url]() { handleResponse(reply, url); });
}


void PictureLoader::clear()
{
   mpictureMap.clear();
}
