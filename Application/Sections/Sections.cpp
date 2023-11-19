#include "Sections.h"


HelloSection::HelloSection(QWidget *parent) : QWidget(parent)
{

}
void HelloSection::setUpHelloSection(QStackedWidget *&stackedWidget, QWidget *parent)
{
    parent->setWindowTitle("Здравствуйте");
    helloSignInButton = new Button(this);
    helloSignUpButton = new Button(this);
    helloLabel = new Label(this);

    helloSignUpButton->setText("Зарегистрироваться");
    helloSignUpButton->setGeometry(120,300 , 150, 30);
    helloSignInButton->setText("Войти");
    helloSignInButton->setGeometry(120,340 , 150, 30);


    helloLabel->setText("Здравствуйте!");
    helloLabel->setFont(QFont("Inter", 32));
    helloLabel->setGeometry(65, 20, 280, 200);


    connect(helloSignUpButton, &QPushButton::clicked, this, [=]()
    {
        parent->setWindowTitle("Регистрация");
        stackedWidget->setCurrentIndex(1);
    });
    connect(helloSignInButton, &QPushButton::clicked, this, [=]()
    {
        parent->setWindowTitle("Вход");
        stackedWidget->setCurrentIndex(2);
    });
}
HelloSection::~HelloSection()
{

}



SignUpSection::SignUpSection(QWidget *parent) : QWidget(parent)
{
    sqlQuery = new SqlQuery;
}
void SignUpSection::setUpSignUpSection(MainSection *&mainSection,  DataBase *&db, QStackedWidget *&stackedWidget, User *&user,QWidget *parent)
{

    this->isSignUpCorrect = false;
    isValidEmail = false;
    isValidPassword = false;
    emailField = new LineEdit(this);
    passwordField = new LineEdit(this);
    rememberMeCheckBox  = new CheckBox(this);
    showPasswordCheckBox = new CheckBox(this);
    rememberMeLabel = new Label(this);
    signUpButton = new Button(this);
    errorMessage = new ErrorMessage(this);

    emailField->setPlaceholderText("Ваш email");
    emailField->setClearButtonEnabled(true);

    passwordField->setPlaceholderText("Пароль");
    passwordField->move(90, 130);
    passwordField->setClearButtonEnabled(true);
    passwordField->setEchoMode(QLineEdit::Password);

    rememberMeLabel->setText("Запомнить меня?");
    rememberMeLabel->setGeometry(115, 158, 200, 50);


    signUpButton->setText("Регистрация");


    showPasswordCheckBox->move(300, 135);
    showPasswordCheckBox->setToolTip("Показать пароль");


    QPushButton *switchToSignInLabel = new QPushButton(this);
    switchToSignInLabel->setText("Войти?");
    switchToSignInLabel->setStyleSheet("text-decoration:underline; background-color: rgba(255, 255, 255, 0);");
    switchToSignInLabel->setGeometry(120, 420, 150, 50);
    switchToSignInLabel->show();


    connect(signUpButton, &Button::clicked, this, [=](){

        user->setUserEmail(emailField->text());
        user->setUserPassword(passwordField->text());

        Validator::EmailValidation(emailField->text(), isValidEmail);
        Validator::PasswordValidation(passwordField->text(), isValidPassword); //Доделать

        if(isValidEmail && isValidPassword)
        {
            if(rememberMeCheckBox->isChecked())
            {
                user->saveUserData();
            }
            sqlQuery->signUp(db->getDatabase(), user->getUserEmail(), user->getUserPassword(), isSignUpCorrect);

            if(isSignUpCorrect) {

                qDebug()<<"Успешная регистрация"<<"\n";
                mainSection->setUpMainSection(user, this);
                if(EmailSender::SendEmail(user->getUserEmail().toStdString()))
                {
                    parent->setWindowTitle("Код подтверждения");
                    stackedWidget->setCurrentIndex(3);
                }
                else
                {
                    errorMessage->showMessage("Ошибка отправки кода подтверждения! Проверьте email!");
                }
            }
            else
            {
                errorMessage->showMessage("Ошибка! Пользователь с таким именем уже существует!");
            }
        }
        else
        {
            emailField->setStyleSheet("border: 1px solid red;");
            emailField->setToolTip("Некорректный email");
            passwordField->setStyleSheet("border: 1px solid red;");
            passwordField->setToolTip("Некорректный пароль.\n*Пароль должен содержать как минимум одну строчную и заглавную букву\n*Минимум шесть символов");
            errorMessage->showMessage("Email или пароль введены некорректно");
        }


    });
    connect(switchToSignInLabel, &QPushButton::clicked, this, [=]()
    {
        parent->setWindowTitle("Вход");
        stackedWidget->setCurrentIndex(2);
    });
    connect(showPasswordCheckBox, &CheckBox::clicked, this, [=]{
        if(showPasswordCheckBox->isChecked())
        {
            passwordField->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            passwordField->setEchoMode(QLineEdit::Password);
        }
    });
}
SignUpSection::~SignUpSection()
{
    delete sqlQuery;
}



SignInSection::SignInSection(QWidget *parent) : QWidget(parent)
{
    sqlQuery = new SqlQuery;
}
void SignInSection::setUpSignInSection(MainSection *&mainSection, DataBase *&db, QStackedWidget *&stackedWidget, User *&user,QWidget *parent)
{
    isSignInCorrect = false;
    emailField = new LineEdit(this);
    passwordField = new LineEdit(this);
    rememberMeCheckBox  = new CheckBox(this);
    showPasswordCheckBox = new CheckBox(this);
    rememberMeLabel = new Label(this);
    signInButton = new Button(this);
    errorMessage = new ErrorMessage(this);


    emailField->setPlaceholderText("Ваш email");
    emailField->setClearButtonEnabled(true);

    passwordField->setPlaceholderText("Пароль");
    passwordField->move(90, 130);
    passwordField->setClearButtonEnabled(true);
    passwordField->setEchoMode(QLineEdit::Password);

    rememberMeLabel->setText("Запомнить меня?");
    rememberMeLabel->setGeometry(115, 158, 200, 50);


    signInButton->setText("Вход");


    showPasswordCheckBox->move(300, 135);
    showPasswordCheckBox->setToolTip("Показать пароль");


    QPushButton *switchToSignUpLabel = new QPushButton(this);
    switchToSignUpLabel->setText("Регистрация?");
    switchToSignUpLabel->setStyleSheet("text-decoration:underline; background-color: rgba(255, 255, 255, 0);");
    switchToSignUpLabel->setGeometry(120, 420, 150, 50);
    switchToSignUpLabel->show();


    connect(signInButton, &Button::clicked, this, [=](){

        user->setUserEmail(emailField->text());
        user->setUserPassword(passwordField->text());

        Validator::EmailValidation(emailField->text(), isValidEmail);
        Validator::PasswordValidation(passwordField->text(), isValidPassword);

        sqlQuery->signIn(db->getDatabase(), user->getUserEmail(), user->getUserPassword(), isSignInCorrect);
        if(isValidEmail && isValidPassword) {
            if(rememberMeCheckBox->isChecked())
            {
                user->saveUserData();
            }
            if (isSignInCorrect) {
                mainSection->setUpMainSection(user, parent);
                if(EmailSender::SendEmail(user->getUserEmail().toStdString()))// Возможно добавить if с обработкой ошибки отправки кода
                {
                    qDebug()<<"Успешный вход"<< "\n";
                    parent->setWindowTitle("Код подтверждения");
                    stackedWidget->setCurrentIndex(3);
                }
                else
                {
                    errorMessage->showMessage("Ошибка отправки кода подтверждения! Проверьте email!");
                }

            }
            else{
                errorMessage->showMessage("Ошибка! Пользователя с таким именем не существует!");
            }
        }
        else
        {
            emailField->setStyleSheet("border: 1px solid red;");
            emailField->setToolTip("Некорректный email");
            passwordField->setStyleSheet("border: 1px solid red;");
            passwordField->setToolTip("Некорректный пароль.\n*Пароль должен содержать как минимум одну строчную и заглавную букву\n*Минимум шесть символов");
            errorMessage->showMessage("Email или пароль введены некорректно");
        }
    });
    connect(switchToSignUpLabel, &QPushButton::clicked, this, [=]()
    {
        parent->setWindowTitle("Регистрация");
        this->close();
        stackedWidget->setCurrentIndex(1);
    });
    connect(showPasswordCheckBox, &CheckBox::clicked, this, [=]{
        if(showPasswordCheckBox->isChecked())
        {
            passwordField->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            passwordField->setEchoMode(QLineEdit::Password);
        }
    });
}
SignInSection::~SignInSection()
{
    delete sqlQuery;
}



MainSection::MainSection(QWidget *parent) : QWidget(parent)
{

}
void MainSection::setUpMainSection(User *user,QWidget *parent)
{
    addServiceWindow = new AddServiceWindow(user,this);
    servicesWindow = new ServicesWindow(this);
    userEmailLabel = new Label(this);
    addServiceButton = new Button(this);
    showServicesButton = new Button(this);
    exitFromAccountButton = new Button(this);


    userEmailLabel->move(62, 100);
    userEmailLabel->setFont(QFont("Inter", 12));
    userEmailLabel->setAlignment(Qt::AlignCenter);
    userEmailLabel->setText("Вы вошли в Password Container\n под Email: " + user->getUserEmail());


    addServiceButton->move(120,330);
    addServiceButton->setText("Добавить сервис");

    showServicesButton->move(120,370);
    showServicesButton->setText("Показать сервисы");

    exitFromAccountButton->move(120,410);
    exitFromAccountButton->setText("Выйти из аккаунта");

    connect(addServiceButton, &Button::clicked, parent, [=]{
        addServiceWindow->show();
    });
    connect(showServicesButton, &Button::clicked, parent, [=]{
        servicesWindow->setUpServicesWindow(user);
        servicesWindow->show();
    });
    connect(exitFromAccountButton, &Button::clicked, parent, [=]{
        QApplication::quit();
        user->dropUserData();
    });
}
MainSection::~MainSection()
{

}



AddServiceWindow::AddServiceWindow(User *&user,QWidget *parent) : QMainWindow(parent)
{
    addServiceMessage = new Message(this);
    addServiceErrorMessage = new ErrorMessage(this);
    serviceNameField = new LineEdit(this);
    servicePasswordField = new LineEdit(this);
    addButton = new Button(this);
    sqlQuery = new SqlQuery;
    isServiceAdded = false;

    this->setFixedSize(300 , 400);
    this->setWindowTitle("Добавить сервис");
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);

    serviceNameField->setPlaceholderText("Название сервиса");
    serviceNameField->setGeometry(40, 50, 200, 25);
    serviceNameField->setClearButtonEnabled(true);

    servicePasswordField->setPlaceholderText("Пароль от сервиса");
    servicePasswordField->setGeometry(40, 80, 200, 25);
    servicePasswordField->setClearButtonEnabled(true);

    addButton->setText("Добавить");
    addButton->setGeometry(70,300, 150, 30);

    connect(addButton, &QPushButton::clicked, this, [=](){
        if(serviceNameField->text().isEmpty() || servicePasswordField->text().isEmpty())
        {
            addServiceErrorMessage->showMessage("Поля имя сервиса и пароль не должны быть пустыми!");
        }
        else
        {
            sqlQuery->addService(serviceNameField->text(), servicePasswordField->text(),user->getUserEmail(), user->getUserPassword(), isServiceAdded);
            if (isServiceAdded) {
            addServiceMessage->setText("Сервис успешно добавлен!");
            addServiceMessage->show();
            }
            else
            {
            addServiceErrorMessage->showMessage(
                    "Cервис и пароль не добавлены!\nПроверьте правильность введённой информации.\n\n"
                    "*Примечание: возможно вы пытаетесь добавить сервис, имя котрого присутсвует в списке.\n "
                    "Если это так, то пожалуйста, поменяйте имя!");
            }
        }
    });

}
AddServiceWindow::~AddServiceWindow()
{
    delete sqlQuery;
}


ServicesWindow::ServicesWindow( QWidget *parent) : QMainWindow(parent)
{

}
void ServicesWindow::setUpServicesWindow(User *user)
{
    this->setFixedSize(300, 500);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    deleteServiceWindow = new DeleteServiceWindow(user, this);
    deleteServicesButton = new Button(this);
    servicesTable = new ServicesTable(this);
    searchServices = new LineEdit(this);

    searchServices->move(45, 410);
    searchServices->setPlaceholderText("Поиск сервиса");

    deleteServicesButton->move(70,455);
    deleteServicesButton->setText("Удалить сервисы");

    servicesTable->ShowServices(user->getUserEmail(), user->getUserPassword());
    connect(searchServices, &LineEdit::textChanged, this, [=]{
        if(searchServices->text().isEmpty())
        {
            servicesTable->ShowServices(user->getUserEmail(), user->getUserPassword());
        }
        else {
            servicesTable->ShowServicesOnSearch(user->getUserEmail(), user->getUserPassword(),
                                                searchServices->text());
        }
    });
    connect(deleteServicesButton, &Button::clicked, this, [=]{
        deleteServiceWindow->show();
    });
}
ServicesWindow::~ServicesWindow() {

}



DeleteServiceWindow::DeleteServiceWindow(User *&user,QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(300 , 400);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setWindowTitle("Удаление сервиса(ов)");
    deleteServiceMessage = new Message(this);
    deleteServiceError = new ErrorMessage(this);
    serviceNameField = new LineEdit(this);
    deleteServiceButton = new Button(this);
    deleteAllServicesButton = new Button(this);
    sqlQuery = new SqlQuery;

    serviceNameField->setPlaceholderText("Название сервиса");
    serviceNameField->setGeometry(40, 50, 200, 25);
    serviceNameField->setClearButtonEnabled(true);

    deleteServiceButton->setGeometry(70, 150, 150, 25);
    deleteServiceButton->setText("Удалить");

    deleteAllServicesButton->setGeometry(70, 180, 150, 25);
    deleteAllServicesButton->setText("Удалить ВСЕ сервисы");


    connect(deleteServiceButton, &QPushButton::clicked, this, [=](){
        sqlQuery->deleteService(user->getUserEmail(), user->getUserPassword(), serviceNameField->text(), isServiceDeleted);
        QString temp = serviceNameField->text();
        if(isServiceDeleted)
        {
            if(!temp.isEmpty()) {
                deleteServiceMessage->setText("Сервис успешно удалён");
                deleteServiceMessage->show();
            }
            else
            {
                deleteServiceError->showMessage("Введите название сервиса,\n который хотите удалить");
            }
        }
        else
        {
            deleteServiceError->showMessage("Такого сервиса не существует");
        }
    });
    connect(deleteAllServicesButton, &QPushButton::clicked, this, [=](){
        sqlQuery->deleteAllServices(user->getUserEmail(), user->getUserPassword(), isServiceDeleted);
        if(isServiceDeleted)
        {
            deleteServiceMessage->setText("Сервисы успешно удалены");
            deleteServiceMessage->show();
        }
        else
        {
            deleteServiceError->showMessage("Ошибка при удалении всех сервисов");
        }
    });
}
DeleteServiceWindow::~DeleteServiceWindow()
{
    delete sqlQuery;
}



UpdateAppWindow::UpdateAppWindow(QWidget *parent) : QMainWindow(parent) {

}
void UpdateAppWindow::setUpUpdateWindow() {
    this->setFixedSize(300, 300);
    this->move(1200, 300);
    this->setWindowTitle("Обновления");
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setAnimated(true);

    temp_label = new Label(this);
    temp_label->setText("Данная функция пока в разработке");
    temp_label->setFixedSize(300,300);
    temp_label->move(50,0);

    this->show();
}
void UpdateAppWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);

}
UpdateAppWindow::~UpdateAppWindow()
{}


EmailCodeSection::EmailCodeSection(QWidget *parent)
{

}
void EmailCodeSection::setUpEmailCodeSection(/*User *&user, */QStackedWidget *&stackedWidget,QWidget *parent)
{
    emailCodeField = new LineEdit(this);
    sendCodeButton = new Button(this);
    codeError = new ErrorMessage(this);
    emailLabel = new Label(this);

    emailCodeField->setPlaceholderText("Код подтверждения");
    emailCodeField->setClearButtonEnabled(true);

    sendCodeButton->setText("Подтвердить");

    emailLabel->setText("Код подтверждения отправлен на ваш email");
    emailLabel->move(42, 170);
    emailLabel->setFont(QFont("Inter", 12));
    emailLabel->setAlignment(Qt::AlignCenter);


    connect(sendCodeButton, &Button::clicked, this, [=]{

        if(emailCodeField->text().toStdString() == EmailSender::getCode())
        {
            parent->setWindowTitle("Password Container");
            stackedWidget->setCurrentIndex(4);
        }
        else
        {
            codeError->showMessage("Неверный код подтверждения");
        }
    });
//    connect("") нужна еще одна кнопка для переотправления кода подтверждения
}

EmailCodeSection::~EmailCodeSection()
{

}

