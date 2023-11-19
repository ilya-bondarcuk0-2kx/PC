//
// Created by tanya on 14.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_SQLQUERY_H
#define PASSWORDCONTAINERPROD_SQLQUERY_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include <QLineEdit>
#include <QString>
#include <QHeaderView>


class SqlQuery{
public:
    SqlQuery();
    ~SqlQuery();
    void rememberMeCheck(const QString &user_email, const QString &user_password, bool &isUserRemembered);
    void signUp(QSqlDatabase &db, const QString &user_email, const QString &user_password, bool &isSignUpCorrect);
    void signIn(QSqlDatabase &db, const QString &user_email,const QString &user_password,bool &isSignInCorrect);
    void addService(const QString &serviceName,const QString &servicePassword,const QString &user_email, const QString &user_password, bool &isServiceAdded);
    void deleteService(const QString &user_email,const QString &user_password,const QString &serviceNameField, bool &isServiceDeleted);
    void deleteAllServices(const QString &user_email,const QString &user_password,bool &isServiceDeleted);
    QString getUserId(const QString &user_email,const QString &user_password);
    QString getMaxId();
    QString autoIncrementUsersKey();

private:
    QSqlQuery *signUpQuery{};
    QSqlQuery *signInQuery{};
    QSqlQuery *getUserIdQuery{};
    QSqlQuery *getMaxIdQuery{};
    QSqlQuery *addServiceQuery{};
    QSqlQuery *deleteServiceQuery{};
    QSqlQuery *rememberMeCheckQuery{};
};

class ServicesTable :  public QTableView
{
public:
    explicit ServicesTable(QWidget *parent = nullptr);
    void ShowServices(const QString &user_email, const QString &user_password);
    void ShowServicesOnSearch(const QString &user_email,const  QString &user_password, const QString &searchServiceField);
    ~ServicesTable() override;
private:
    SqlQuery *sqlQuery;
    QSqlQueryModel *model;
};


#endif //PASSWORDCONTAINERPROD_SQLQUERY_H
