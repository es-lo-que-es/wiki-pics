#include "main_window.hpp"

#include "QApplication"


int main(int argc, char * argv[])
{
   QApplication app(argc, argv);
   MainWindow window;

   window.setStyleSheet("font-size: 24px; background: #f2f2f2; color: #262626; font-family: monospace");
   window.setMinimumWidth(200);
   window.resize(400, 600);

   window.show();

   return app.exec();
}
