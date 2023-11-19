//
// Created by tanya on 17.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_USER_H
#define PASSWORDCONTAINERPROD_USER_H

#include <QSettings>

class User {
public:
    User();
    QString getUserEmail();
    QString getUserPassword();
    void setUserEmail( const QString& _user_email);
    void setUserPassword(const  QString& _user_password);
    void saveUserData();
    void dropUserData();
    const QString getSavedUserEmail();
    const QString getSavedUserPassword();
    ~User();

private:
    QString *user_email;
    QString *user_password;
    QSettings *settings;
};


#endif //PASSWORDCONTAINERPROD_USER_H
