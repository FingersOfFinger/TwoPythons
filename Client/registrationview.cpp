#include "registrationview.h"

RegistrationView::RegistrationView(QWidget *parent) :
    QWidget(parent)
{

}

void Registration::drowElements()
{
    this->setWindowTitle("Регистрация");
    this->setWindowIcon(QIcon("image/Registration.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

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

RegistrationView ::~RegistrationView()
{

}
