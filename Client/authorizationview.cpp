#include "authorizationview.h"

AuthorizationView::AuthorizationView(QWidget *parent) :
    QWidget(parent)
{

}

void Authorization::drowElements()
{
    this->setWindowTitle("Авторизация");
    this->setWindowIcon(QIcon("image/window.png"));
    this->setFixedSize(768, 432);
    //this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    image = new QLabel(this);
    i = new QImage("image/background.jpg");
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

    registrationlButton = new QPushButton;
    registrationlButton->setFlat(true);
    registrationlButton->setIcon(QPixmap("image/register_button.png"));
    registrationlButton->setIconSize(QSize(145, 40));
    registrationlButton->setShortcut(QKeySequence(Qt::Key_Escape));

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

void Authorization::enableSignInButton()
{
    signInButton->setEnabled(!loginEdit->text().isEmpty() && !passwordEdit->text().isEmpty());
}

AuthorizationView ::~AuthorizationView()
{

}
