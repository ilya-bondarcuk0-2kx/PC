#include "User.h"

User::User()
{
    settings = new QSettings("BBD", "PasswordContainer");
    user_email = new QString;
    user_password = new QString;
    qDebug() << settings->allKeys();
}
User::~User()
{
    delete settings;
    delete user_email;
    delete user_password;
}

QString User::getUserEmail()
{
    return *user_email;
}
QString User::getUserPassword()
{
    return *user_password;
}

void User::setUserEmail( const QString& _user_email)
{
    *user_email = _user_email;
}
void User::setUserPassword(const QString& _user_password)
{
    *user_password = _user_password;
}

void User::saveUserData()
{

    settings->setValue("saved_user_email", *user_email);
    settings->setValue("saved_user_password", *user_password);
}
void User::dropUserData()
{
    settings->clear();
}

const QString User::getSavedUserEmail()
{
    return settings->value("saved_user_email").toString();
}
const QString User::getSavedUserPassword()
{
    return settings->value("saved_user_password").toString();
}