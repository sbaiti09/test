#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{

}

bool Connection::createconnection(){
    bool test=false;
    db = QSqlDatabase::addDatabase ("QODBC");
        db.setDatabaseName("test");
        db.setUserName("system");
        db.setPassword("azerty");
if (db.open()) test=true;

else {
        qDebug() << "Erreur de connexion:" << db.lastError().text();
    }

return test;
}
void Connection::closeconnection(){db.close();}
