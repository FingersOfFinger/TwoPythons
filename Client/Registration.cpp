#include "Registration.h"

Registration::Registration(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Регистрация");
    this->setWindowIcon(QIcon("image/Registration.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    drowElements();

    socket = new QTcpSocket(this);
    socket->connectToHost("104.154.224.15",49002);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    char str[100];
    std::string str2 = "{\"globalType\":\"connection\",\"type\":\"registration\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
}

void Registration::drowElements()
{
    image = new QLabel(this);
    i = new QImage("image/background2.png");
    QImage img = i->scaled(QSize(this->width(),height()), Qt::IgnoreAspectRatio);
    image->show();
    image->resize(QSize(this->width(),height()));
    image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

    loginLine = new QLineEdit(this);
    loginLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+")));
    loginLine->setMaxLength(15);
    loginLine->setFixedSize(160, 20);

    passwordLine = new QLineEdit(this);
    passwordLine->setMaxLength(20);
    passwordLine->setFixedSize(160, 20);
    passwordLine->setEchoMode(QLineEdit::Password);

    loginLabel = new QLabel("<font face = Georgia size = 5>Логин: </font>");
    passwordLabel = new QLabel("<font face = Georgia size = 5>Пароль:</font>");

    registerButton = new QPushButton();
    registerButton->setEnabled(false);
    registerButton->setFlat(true);
    registerButton->setIcon(QPixmap("image/register_button"));
    registerButton->setIconSize(QSize(150, 30));
    registerButton->setShortcut(QKeySequence(Qt::Key_Return));
    connect(registerButton, SIGNAL(clicked(bool)), this, SLOT(registerButtonPressed()));

    cancelButton = new QPushButton();
    cancelButton->setEnabled(true);
    cancelButton->setFlat(true);
    cancelButton->setIcon(QPixmap("image/cancel_button"));
    cancelButton->setIconSize(QSize(150, 30));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));

    connect(loginLine, SIGNAL(textChanged(QString)), this, SLOT(enableRegisterButton(QString)));
    connect(passwordLine, SIGNAL(textChanged(QString)), this, SLOT(enableRegisterButton(QString)));

    QVBoxLayout *registerButtons = new QVBoxLayout();
    registerButtons->addWidget(cancelButton);
    registerButtons->addWidget(registerButton);

    QFormLayout *labelLayout = new QFormLayout();
    labelLayout->addRow(loginLabel, loginLine);
    labelLayout->addRow(passwordLabel, passwordLine);
    labelLayout->setLabelAlignment(Qt::AlignRight);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(labelLayout,1,0);
    mainLayout->addLayout(registerButtons,1,1,Qt::AlignRight);

    setLayout(mainLayout);
}

void Registration::enableRegisterButton(QString text)
{
    registerButton->setEnabled(!loginLine->text().isEmpty() && !passwordLine->text().isEmpty());
}

void Registration::registerButtonPressed()
{
    QByteArray login = QByteArray::fromStdString(loginLine->text().toStdString());
    QByteArray password = QByteArray::fromStdString(passwordLine->text().toStdString());
    QByteArray str = "{\"globalType\":\"connection\",\"type\":\"registration\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (checkCorrectInput())
    {
        QMessageBox::information(this, "Информация","Приветствуем, "+loginLine->text()+"!");
        closeWindow();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "<div align=center>Ошибка корректности ввода данных!</div>");
    }
}

bool Registration::checkCorrectInput()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "connection") && (doc.object().value("type").toString() == "registration") && (doc.object().value("access").toString() == "true"))
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
    }
}

void Registration::closeWindow()
{
    Authorization *closeReg = new Authorization;
    this->hide();
    closeReg->show();
}

void Registration::sockConnect()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
    }
}

void Registration::sockDisc()
{
    socket->deleteLater();
}

Registration::~Registration()
{
    delete i;
    delete image;
}
