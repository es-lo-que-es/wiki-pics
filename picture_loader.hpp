#ifndef PICTURE_LOADER_HEADER
#define PICTURE_LOADER_HEADER

#include "QMap"
#include "QObject"
#include "QNetworkAccessManager"
#include "QPixmap"

class PictureLoader : public QObject {

   Q_OBJECT

 public:
   void clear();
   PictureLoader();
   QPixmap getPicture(QString url);

 signals:
   void pictureLoaded();

 private:
   void handleResponse(QNetworkReply * reply, QString url);
   void loadPicture(QString url);
   
   QMap<QString, QPixmap> mpictureMap;
   QNetworkAccessManager mnetManager;

   QPixmap mloading;
   QPixmap mfailed;
};


#endif
