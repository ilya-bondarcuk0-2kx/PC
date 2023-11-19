//
// Created by tanya on 14.11.2023.
//

#include "SqlQuery.h"



SqlQuery::SqlQuery()
{
    signInQuery = new QSqlQuery;
    signUpQuery = new QSqlQuery;
    getUserIdQuery = new QSqlQuery;
    getMaxIdQuery = new QSqlQuery;
    addServiceQuery = new QSqlQuery;
    deleteServiceQuery = new QSqlQuery;
    rememberMeCheckQuery = new QSqlQuery;
}
SqlQuery::~SqlQuery()
{
    delete signInQuery;
    delete signUpQuery;
    delete getUserIdQuery;
    delete getMaxIdQuery;
    delete addServiceQuery;
    delete deleteServiceQuery;
    delete rememberMeCheckQuery;
}

void SqlQuery::rememberMeCheck(const QString &saved_user_email, const QString &saved_user_password, bool &isUserRemembered)
{
    rememberMeCheckQuery->exec("SELECT user_email, user_password FROM users "
                                     "WHERE user_email= \'" + saved_user_email +  "\' AND user_password= \'" + saved_user_password + "\'");
    rememberMeCheckQuery->next();
    if(saved_user_email == rememberMeCheckQuery->value(0) && saved_user_password == rememberMeCheckQuery->value(1))
    {
        isUserRemembered = true;
    }
    else
    {
        isUserRemembered= false;
    }
}
void SqlQuery::signUp(QSqlDatabase &db, const QString &user_email, const QString &user_password, bool &isSignUpCorrect)
{
    db.transaction();

    signUpQuery->prepare("INSERT INTO users(id) "
                         " VALUES " "(\'" + autoIncrementUsersKey() + "\')");
    if (signUpQuery->exec()) {
        signUpQuery->clear();
        signUpQuery->finish();
        signUpQuery->prepare("UPDATE users "
                             "SET user_email = " "\'" + user_email + "\', user_password = \'" +
                                     user_password + "\'"
                                                     "WHERE id = " "(SELECT MAX(id) FROM users)");
        if (signUpQuery->exec()) {

            qDebug()<< "Данные пользователя после РЕГИСТРАЦИИ корректно присвоились переменным" << user_email << " " << user_password;
            db.commit();
            db.transaction();


            if(signInQuery->exec("CREATE TABLE users_services.user_service" + getMaxId() +
                                 " ( \"service\" VARCHAR(40) NOT NULL UNIQUE, \"password\" VARCHAR(40) NOT NULL)")) {
                db.commit();
                isSignUpCorrect = true;

            }
            else{
                qDebug() << signInQuery->lastError().text();
            }
        }
        else
        {
            isSignUpCorrect = false;
            db.rollback();
        }
    }
    else
    {
        isSignUpCorrect = false;
        db.rollback();
        qDebug() << "Ошибка запроса";
    }
}
void SqlQuery::signIn(QSqlDatabase &db, const QString &user_email,const QString &user_password, bool &isSignInCorrect)
{
    db.transaction();

    signInQuery->exec("SELECT user_email, user_password FROM users "
                      "WHERE user_email = " "\'" + user_email + "\' AND "
                                                                        " user_password = " "\'" +
                              user_password + "\'");
    signInQuery->next();


    if (user_email == signInQuery->value(0) || user_password == signInQuery->value(1)) {
        isSignInCorrect = true;
        signInQuery->clear();
        signInQuery->finish();
        db.commit();
        qDebug() << "Данные пользователя после ВХОДА корректно присвоились переменным" <<user_email << " " << user_password;
    } else {
        isSignInCorrect = false;
        db.rollback();
        qDebug() << "Пользователя нет в базе данных";
    }
}
void SqlQuery::addService(const QString &serviceName, const QString &servicePassword,const QString &user_email,const QString &user_password,  bool &isServiceAdded)
{
    addServiceQuery->prepare("INSERT INTO users_services.user_service" + getUserId(user_email,user_password) + "(service, password) "
                                                                                       "VALUES (\'" + serviceName + "\', \'" + servicePassword + "\')");
    if(addServiceQuery->exec())
    {
        qDebug()<<"Сервис успешно добавлен!";
        isServiceAdded = true;
    }
    else
    {
        isServiceAdded = false;
        qDebug()<<"Ошибка добавления сервиса:" << addServiceQuery->lastError().text();
    }
}
void SqlQuery::deleteService(const QString &user_email, const QString &user_password,const QString &serviceNameField, bool &isServiceDeleted)
{
    if(deleteServiceQuery->exec("SELECT service FROM users_services.user_service"+getUserId(user_email,user_password) +
                                " WHERE service = \'" + serviceNameField + "\'"))
    {
        deleteServiceQuery->first();
        QString temp = deleteServiceQuery->value("service").toString();
        if(!temp.isEmpty()) {
            deleteServiceQuery->exec("DELETE FROM users_services.user_service"+getUserId(user_email,user_password) +
                                     " WHERE service = \'" + serviceNameField + "\'");

            qDebug() << "Успешное удаление сервиса" << "\n";
            isServiceDeleted = true;
        }
        else
        {
            isServiceDeleted = false;
            qDebug()<<"Ошибка при удалении сервиса : " << deleteServiceQuery->lastError().text();
        }
    }
    else
    {
        isServiceDeleted = false;
        qDebug()<<"Ошибка при выборе поля удаления: " << deleteServiceQuery->lastError().text();
    }
}
void SqlQuery::deleteAllServices(const QString &user_email,const QString &user_password,bool &isServiceDeleted)
{
    if(deleteServiceQuery->exec("DELETE FROM users_services.user_service"+getUserId(user_email,user_password)))
    {
        isServiceDeleted = true;
        qDebug()<<"Успешное удаление всех сервисов" << "\n";
    }
    else
    {
        isServiceDeleted = false;
        qDebug()<<"Ошибка : " << deleteServiceQuery->lastError().text();
    }
}
QString SqlQuery::getUserId(const QString &user_email,const QString &user_password)
{
    getUserIdQuery->prepare("SELECT id FROM users WHERE user_email = \'" + user_email + "\' AND user_password= \'" + user_password + "\'" );
    getUserIdQuery->exec();
    getUserIdQuery->first();
    return getUserIdQuery->value(0).toString();
}
QString SqlQuery::getMaxId()
{
    getMaxIdQuery->prepare("SELECT MAX(id) FROM users");
    getMaxIdQuery->exec();
    getMaxIdQuery->first();
    return getMaxIdQuery->value(0).toString();
}
QString SqlQuery::autoIncrementUsersKey()
{
    long temp = 0;
    temp = getMaxId().toInt();
    ++temp;
    QString temp_str = QString::number(temp);
    return temp_str;
}



ServicesTable::ServicesTable(QWidget *parent) : QTableView(parent)
{
    model = new QSqlQueryModel(this);
    sqlQuery = new SqlQuery;
    this->setFixedSize(300, 400);
    this->setStyleSheet("background-color: #333;color: white;border-color:white; padding: 5px; border-radius: 5px;");
    this->horizontalHeader()->close();
    this->verticalHeader()->close();
    this->resizeRowsToContents();
    this->resizeColumnsToContents();
    this->show();
}
void ServicesTable::ShowServices(const QString &user_email,const QString &user_password)
{
    model->setQuery("SELECT service, password FROM users_services.user_service" + sqlQuery->getUserId(user_email, user_password));
    this->setModel(model);
    qDebug()<<"Успешный вывод ВСЕХ паролей";

}
void ServicesTable::ShowServicesOnSearch(const QString &user_email,const QString &user_password, const QString &searchServiceField)
{
    model->setQuery("SELECT service, password FROM users_services.user_service"+sqlQuery->getUserId(user_email,user_password) +
                   " WHERE service LIKE \'%" + searchServiceField + "%\'");
    this->setModel(model);

    qDebug()<<"Сервисы на основе поиска выведены!";
}
ServicesTable::~ServicesTable()
{
    delete sqlQuery;
}