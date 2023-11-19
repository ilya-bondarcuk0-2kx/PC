#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    qDebug()<<"Программа запущена"<<"\n";
    isUserRemembered = false;
    this->setWindowIcon(QIcon(R"(.\resources\PasswordContainerIcon.png)"));
    this->setFixedSize(400, 500);
    dataBase = new DataBase;
    dataBase->setUpDatabase();
    user = new User;
    sqlQuery = new SqlQuery;
    stackedWidget = new QStackedWidget(this);
    helloSection = new HelloSection(this);
    signUpSection = new SignUpSection(this);
    signInSection = new SignInSection(this);
    mainSection = new MainSection(this);
    updateWindow = new UpdateAppWindow(this);
    emailSection = new EmailCodeSection(this);
    updateWindowButton = new Button(this);



    updateWindowButton->setGeometry(370,0,30,30);
    updateWindowButton->setStyleSheet("background-color: transparent;");
    updateWindowButton->setIcon(QIcon(R"(.\resources\PasswordContainerIcon.png)"));


    stackedWidget->addWidget(helloSection);
    stackedWidget->addWidget(signUpSection);
    stackedWidget->addWidget(signInSection);
    stackedWidget->addWidget(emailSection);
    stackedWidget->addWidget(mainSection);

    this->setCentralWidget(stackedWidget);

    sqlQuery->rememberMeCheck(user->getSavedUserEmail(), user->getSavedUserPassword(), isUserRemembered);

    if(!isUserRemembered)
    {
        stackedWidget->setCurrentWidget(helloSection);
        helloSection->setUpHelloSection(stackedWidget, this);
        signUpSection->setUpSignUpSection(mainSection,dataBase, stackedWidget, user, this);
        signInSection->setUpSignInSection(mainSection,dataBase, stackedWidget, user,this);
        emailSection->setUpEmailCodeSection(/*user,*/stackedWidget,this);
    }
    else
    {
        user->setUserEmail(user->getSavedUserEmail());
        user->setUserPassword(user->getSavedUserPassword());
        stackedWidget->setCurrentWidget(mainSection);
        mainSection->setUpMainSection(user, this);
        this->setCentralWidget(stackedWidget);
    }

    themeComboBox = new ComboBox(this);
    connect(updateWindowButton, &Button::clicked, this, [=]{
       showUpdateWindow();
    });
    connect(themeComboBox, &ComboBox::currentTextChanged,this, [=]{
       if(themeComboBox->currentIndex() == 0)
       {
           QApplication::setStyle("Windows");
       }
       if(themeComboBox->currentIndex() == 1)
       {
           QApplication::setStyle("windowsvista");
       }
    });
    this->show();
}


void MainWindow::showUpdateWindow()
{
    updateWindow->setUpUpdateWindow();
}

MainWindow::~MainWindow()
{
    delete sqlQuery;
    delete user;
    delete dataBase;
    qDebug()<<"\nПрограмма завершена корректно"<<"\n";
}



