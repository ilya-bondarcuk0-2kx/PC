//
// Created by tanya on 17.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_VALIDATORS_H
#define PASSWORDCONTAINERPROD_VALIDATORS_H

#include <QRegularExpression>
#include <QRegularExpressionValidator>
class Validator
{

public:
    Validator();
    ~Validator();
    static void EmailValidation(const QString &email, bool &isValidEmail);
    static void PasswordValidation(const QString &password, bool &isValidPassword);
private:
    static QRegularExpression emailPattern;
    static QRegularExpressionValidator *emailValidator;
    static  QRegularExpression passwordPattern;
    static  QRegularExpressionValidator *passwordValidator;
};


#endif //PASSWORDCONTAINERPROD_VALIDATORS_H
