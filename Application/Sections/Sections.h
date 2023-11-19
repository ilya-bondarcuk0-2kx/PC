//
// Created by tanya on 16.11.2023.
//

#ifndef PASSWORDCONTAINERPROD_SECTIONS_H
#define PASSWORDCONTAINERPROD_SECTIONS_H

#include <QWidget>
#include <QStackedWidget>
#include <QMainWindow>
#include <QPropertyAnimation>
#include "../../Application/Service/SqlDB/DataBase.h"
#include "../../Application/Service/SqlQuery/SqlQuery.h"
#include "../../Application/User/User.h"
#include "../../Application/Widgets/Widgets.h"
#include "../../Application/Service/TextLinesValidators/Validators.h"
#include "../../Application/Service/Email/EmailSender.h"


class SignUpSection;
class SignInSection;
class MainSection;


class HelloSection : public QWidget
{
public:
    explicit HelloSection(QWidget *parent = nullptr);
    void setUpHelloSection(QStackedWidget *&stackedWidget,QWidget *parent);
    ~HelloSection() override;
private:
    Button *helloSignUpButton;
    Button *helloSignInButton;
    Label *helloLabel;


};

class SignUpSection : public QWidget
{
public:

    explicit SignUpSection(QWidget *parent = nullptr);
    void setUpSignUpSection(MainSection *&mainSection, DataBase *&db,QStackedWidget *&stackedWidget ,User *&user, QWidget *parent);
    ~SignUpSection() override;

private:
    Button *signUpButton{};
    LineEdit *emailField{};
    LineEdit *passwordField{};
    CheckBox *rememberMeCheckBox{};
    CheckBox *showPasswordCheckBox{};
    Label *rememberMeLabel{};
    ErrorMessage *errorMessage{};
    SqlQuery *sqlQuery{};
    bool isSignUpCorrect{};
    bool isValidEmail{};
    bool isValidPassword{};
};

class  SignInSection : public QWidget
{
public:
    explicit SignInSection(QWidget *parent = nullptr);
    void setUpSignInSection(MainSection *&mainSection,DataBase *&db,QStackedWidget *&stackedWidget ,User *&user,QWidget *parent);
    ~SignInSection() override;
private:
    Button *signInButton;
    LineEdit *emailField;
    LineEdit *passwordField;
    CheckBox *rememberMeCheckBox;
    CheckBox *showPasswordCheckBox;
    Label *rememberMeLabel;
    SqlQuery *sqlQuery;
    ErrorMessage *errorMessage;
    bool isSignInCorrect;
    bool isValidEmail;
    bool isValidPassword;
};



class AddServiceWindow;
class ServicesWindow;
class DeleteServiceWindow;

class MainSection : public QWidget
{
public:
    explicit MainSection(QWidget *parent = nullptr);
    void setUpMainSection(User *user,QWidget *parent);
    ~MainSection() override;
private:
    Button *addServiceButton;
    Button *showServicesButton;
    Button *exitFromAccountButton;
    AddServiceWindow *addServiceWindow;
    ServicesWindow *servicesWindow;
    Label *userEmailLabel;
};

class AddServiceWindow : public QMainWindow
{
public:
    explicit AddServiceWindow(User *&user,QWidget *parent = nullptr);
    ~AddServiceWindow() override;
private:
    LineEdit *serviceNameField;
    LineEdit *servicePasswordField;
    Message *addServiceMessage;
    ErrorMessage *addServiceErrorMessage;
    Button *addButton;
    SqlQuery *sqlQuery;
    bool isServiceAdded;
};

class ServicesWindow : public QMainWindow
{
public:
    explicit ServicesWindow( QWidget *parent = nullptr);
    void setUpServicesWindow(User *user);
    ~ServicesWindow() override;
private:
    DeleteServiceWindow *deleteServiceWindow;
    LineEdit *searchServices;
    Button *deleteServicesButton;
    ServicesTable *servicesTable;
};

class DeleteServiceWindow : public QMainWindow
{
public:
    explicit DeleteServiceWindow(User *&user,QWidget *parent = nullptr);
    ~DeleteServiceWindow() override;
private:
    LineEdit *serviceNameField;
    Message *deleteServiceMessage;
    ErrorMessage *deleteServiceError;
    Button *deleteServiceButton;
    Button *deleteAllServicesButton;
    SqlQuery *sqlQuery;
    bool isServiceDeleted;
};

class UpdateAppWindow : public QMainWindow
{
public:
    explicit UpdateAppWindow(QWidget *parent = nullptr);
    void setUpUpdateWindow();
    ~UpdateAppWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Label *temp_label;
    QPropertyAnimation *openAnimation;
    QPropertyAnimation *closeAnimation;
};


class EmailCodeSection : public QWidget
{
public:
    explicit EmailCodeSection(QWidget *parent = nullptr);
    void setUpEmailCodeSection(/*User *&user,*/QStackedWidget *&stackedWidget,QWidget *parent);
    ~EmailCodeSection() override;
private:
    Button *sendCodeButton;
    LineEdit *emailCodeField;
    ErrorMessage *codeError;
    Label *emailLabel;
};

#endif //PASSWORDCONTAINERPROD_SECTIONS_H
