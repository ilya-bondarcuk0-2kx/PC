#include "DataBase.h"



void DataBase::setUpDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("USERS");
    db.setUserName("postgres");
    db.setPassword("12345");
    if(!db.open()) {
        qDebug()<<"Ошибка подключения к базе данных" + db.lastError().text();
    }
    else{
        qDebug()<<"Успешное подключение к БД" ;
    }
}

QSqlDatabase& DataBase::getDatabase()
{
    return db;
}