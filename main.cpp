#include "mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection connection;
     bool test=connection.createconnection();
     MainWindow w;
     if (test){ QMessageBox::information (nullptr, QObject::tr("OK"),
                                          QObject::tr("Connection a la base de donnée etablie \n"
                                         "Click Cancel to exit."), QMessageBox::Ok);

      w.show();
     }
     else{
         QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                    QObject::tr("err : connection n'est pas etablie  \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
     };

    return a.exec();
}
