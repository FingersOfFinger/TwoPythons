#include "Authorization.h"

Authorization::Authorization(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Авторизация");
    this->setWindowIcon(QIcon("image/window.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    drowElements();

    socket = new QTcpSocket(this);
    socket->connectToHost("104.154.224.15",49002);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    char str[100];
    std::string str2 = "{\"globalType\":\"connection\",\"type\":\"authorization\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
}

void Authorization::drowElements()
{
    image = new QLabel(this);
    i = new QImage("image/background2.png");
    QImage img = i->scaled(QSize(this->width(),this->height()), Qt::IgnoreAspectRatio);
    image->show();
    image->resize(QSize(this->width(),this->height()));
    image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

    loginEdit = new QLineEdit(this);
    loginEdit->setFixedSize(325, 40);
    loginEdit->setPlaceholderText("Логин");
    loginEdit->setFont(QFont("Georgia", 15, -1, false));
    QAction *loginEditAction;
    loginEditAction = loginEdit->addAction(QIcon("image/login.png"), QLineEdit::LeadingPosition);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setFixedSize(325, 40);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setFont(QFont("Georgia", 15, -1, false));
    passwordEdit->setEchoMode(QLineEdit::Password);
    QAction *passwordEditAction;
    passwordEditAction = passwordEdit->addAction(QIcon("image/password.png"), QLineEdit::LeadingPosition);

    signInButton = new QPushButton;
    signInButton->setEnabled(false);
    signInButton->setFlat(true);
    signInButton->setIcon(QPixmap("image/signin_button.png"));
    signInButton->setIconSize(QSize(145, 40));
    signInButton->setShortcut(QKeySequence(Qt::Key_Return));
    connect(signInButton, SIGNAL(clicked(bool)), this, SLOT(signInButtonPressed()));

    registrationlButton = new QPushButton;
    registrationlButton->setFlat(true);
    registrationlButton->setIcon(QPixmap("image/register_button.png"));
    registrationlButton->setIconSize(QSize(145, 40));
    registrationlButton->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(registrationlButton, SIGNAL(clicked(bool)), this, SLOT(registrationButtonPressed()));

    connect(loginEdit, SIGNAL(textChanged(QString)), this, SLOT(enableSignInButton(QString)));
    connect(passwordEdit, SIGNAL(textChanged(QString)), this, SLOT(enableSignInButton(QString)));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->addWidget(signInButton);
    buttonsLayout->addWidget(registrationlButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(loginEdit);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

void Authorization::enableSignInButton(QString text)
{
    signInButton->setEnabled(!loginEdit->text().isEmpty() && !passwordEdit->text().isEmpty());
}

void Authorization::signInButtonPressed()
{
    /*
    QByteArray login = QByteArray::fromStdString(loginEdit->text().toStdString());
    QByteArray password = QByteArray::fromStdString(passwordEdit->text().toStdString());
    QByteArray str = "{\"globalType\":\"connection\",\"type\":\"authorization\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    */
    char str[100];
    std::string login = loginEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    std::string str2 = "{\"globalType\":\"connection\",\"type\":\"authorization\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (checkTheEnteredData())
    {
        QMessageBox::information(this,"Информация","Добро пожаловать, "+loginEdit->text()+"!");
        Lobby *openLobby = new Lobby(loginEdit->text());
        this->hide();
        openLobby->show();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "<div align=center>Неверный логин или пароль!</div> \n <div align = center>Пожалуйста, попробуйте ещё раз</div>");
    }
}

bool Authorization::checkTheEnteredData()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "connection") && (doc.object().value("type").toString() == " authorization") && (doc.object().value("access").toString() == "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Authorization::registrationButtonPressed()
{
    Registration *openRegistration = new Registration;
    this->hide();
    openRegistration->show();
}

void Authorization::sockConnect()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
    }
}

void Authorization::sockDisc()
{
    socket->deleteLater();
}

Authorization ::~Authorization()
{
    delete i;
    delete image;
}
