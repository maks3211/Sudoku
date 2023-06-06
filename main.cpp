#include "main_window.h"
#include "login_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   Login_Window l;
   l.show();

   Main_Window *mainWindow = nullptr;

       QObject::connect(&l, &Login_Window::logged, [&mainWindow, &l]() {
           mainWindow = new Main_Window(l.get_user());
           mainWindow->show();
         QObject::connect(mainWindow, &Main_Window::loggedOut, &l, &Login_Window::show);
       });



    return a.exec();
}


/*
 * PRZEKAZYWANIE PARAMETU DO KONSTRUKOTA MAIN WINDOW
  QObject::connect(&L, &Login_Window::logged, [&mainWindow](const QString& name) {
        mainWindow = new Main_Window(name);
        mainWindow->show();
    });
*/
