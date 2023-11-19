//
// Created by tanya on 14.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_DATABASE_H
#define PASSWORDCONTAINERPROD_DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class DataBase {
public:
    void setUpDatabase();
    QSqlDatabase& getDatabase();
private:
    QSqlDatabase db;
};


#endif //PASSWORDCONTAINERPROD_DATABASE_H
