#include "main_window.hpp"


MainWindow::MainWindow(QWidget * parent)
   : msearchBar(&mpicLoader), 
     mview(&mpicLoader)
{
   mview.setModel(msearchBar.picListModel());

   mtitle.setAlignment(Qt::AlignCenter);
   mtitle.setText("Wikipedia Images");

   setupLayout();
}


void MainWindow::setupLayout()
{
   mvbox.setAlignment(Qt::AlignCenter);

   mvbox.addWidget(&mtitle);
   mvbox.addWidget(&msearchBar);

   mhbox.addWidget(&mview);
   mvbox.addLayout(&mhbox);

   setLayout(&mvbox);
}
