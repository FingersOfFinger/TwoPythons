#include "registrationview.h"

RegistrationView::RegistrationView(QWidget *parent) :
    QWidget(parent)
{

}

void Registration::drowElements()
{
    this->setWindowTitle("Регистрация");
    this->setWindowIcon(QIcon("image/Registration.png"));
    this->setFixedSize(640, 360);
    //this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    image = new QLabel(this);
    i = new QImage("image/background.jpg");
    QImage img = i->scaled(QSize(this->width(),height()), Qt::IgnoreAspectRatio);
    image->show();
    image->resize(QSize(this->width(),height()));
    image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

    loginLine = new QLineEdit(this);
    loginLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+")));
    loginLine->setMaxLength(30);
    loginLine->setFont(QFont("Georgia", 15, -1, false));
    loginLine->setFixedSize(325, 40);

    passwordLine = new QLineEdit(this);
    passwordLine->setMaxLength(30);
    passwordLine->setFont(QFont("Georgia", 15, -1, false));
    passwordLine->setFixedSize(325, 40);
    passwordLine->setEchoMode(QLineEdit::Password);

    loginLabel = new QLabel("<font face = Georgia size = 6>Логин: </font>");
    passwordLabel = new QLabel("<font face = Georgia size = 6>Пароль:</font>");

    registerButton = new QPushButton();
    registerButton->setEnabled(false);
    registerButton->setFlat(true);
    registerButton->setIcon(QPixmap("image/register_button"));
    registerButton->setIconSize(QSize(150, 30));
    registerButton->setShortcut(QKeySequence(Qt::Key_Return));

    cancelButton = new QPushButton();
    cancelButton->setEnabled(true);
    cancelButton->setFlat(true);
    cancelButton->setIcon(QPixmap("image/cancel_button"));
    cancelButton->setIconSize(QSize(150, 30));

    connect(loginLine, SIGNAL(textChanged(QString)), this, SLOT(enableRegisterButton()));
    connect(passwordLine, SIGNAL(textChanged(QString)), this, SLOT(enableRegisterButton()));

    QVBoxLayout *registerButtons = new QVBoxLayout();
    registerButtons->addWidget(cancelButton);
    registerButtons->addWidget(registerButton);

    QFormLayout *labelLayout = new QFormLayout();
    labelLayout->addRow(loginLabel, loginLine);
    labelLayout->addRow(passwordLabel, passwordLine);
    labelLayout->setLabelAlignment(Qt::AlignCenter);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(labelLayout,1,0);
    mainLayout->addLayout(registerButtons,1,1,Qt::AlignRight);

    setLayout(mainLayout);
}

void Registration::enableRegisterButton()
{
    registerButton->setEnabled(!loginLine->text().isEmpty() && !passwordLine->text().isEmpty());
}

RegistrationView ::~RegistrationView()
{

}
