#include "Validators.h"


void Validator::EmailValidation(const QString &email, bool &isValidEmail)
{

    QString tempEmail = email;
    int pos = 0;
    QValidator::State state = emailValidator->validate(tempEmail, pos);
    if (state != QValidator::Acceptable) {
        isValidEmail = false;
        QString errorMsg;
        if (state == QValidator::Invalid)
            errorMsg = emailValidator->regularExpression().pattern().isEmpty() ? ("Неверный ввод") : ("Некорректный email");
        else if (state == QValidator::Intermediate)
            errorMsg = ("Некорректный email");

    }
    else
    {
        isValidEmail = true;
    }

}

void Validator::PasswordValidation(const QString &password, bool &isValidPassword)
{

    QString tempPassword = password;
    int pos = 0;
    QValidator::State state = passwordValidator->validate(tempPassword, pos);
    if (state != QValidator::Acceptable) {
        isValidPassword = false;
        QString errorMsg;
        if (state == QValidator::Invalid)
            errorMsg = passwordValidator->regularExpression().pattern().isEmpty() ? ("Некорректный пароль") : ("Некорректный пароль");
        else if (state == QValidator::Intermediate)
            errorMsg = ("Некорректный пароль");
    }
    else
    {
        isValidPassword = true;
    }
}

Validator::Validator() {

    emailValidator->setRegularExpression(emailPattern);
    passwordValidator->setRegularExpression(passwordPattern);

}


QRegularExpression Validator::passwordPattern = QRegularExpression((R"(^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{7,30}$)"));
QRegularExpression Validator::emailPattern = QRegularExpression((R"(^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$)"));
QRegularExpressionValidator* Validator::emailValidator = new QRegularExpressionValidator(emailValidator);
QRegularExpressionValidator* Validator::passwordValidator = new QRegularExpressionValidator(passwordPattern);


Validator::~Validator()
{
    delete emailValidator;
    delete passwordValidator;
}
