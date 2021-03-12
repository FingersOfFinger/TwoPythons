#include "createlobbyview.h"

CreateLobbyView::CreateLobbyView(QWidget *parent) :
    QWidget(parent)
{

}

void CreateLobby::drowElements()
{
    this->setWindowTitle("Создать лобби");
    this->setWindowIcon(QIcon("image/window.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    image = new QLabel(this);
    i = new QImage("image/background2.png");
    QImage img = i->scaled(QSize(this->width(),height()), Qt::IgnoreAspectRatio);
    image->show();
    image->resize(QSize(this->width(),height()));
    image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

    nameLine = new QLineEdit(this);
    //nameLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я]+")));
    nameLine->setMaxLength(15);
    nameLine->setFixedSize(160, 20);

    ownerLine = new QLineEdit(this);
    ownerLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я]+")));
    ownerLine->setMaxLength(15);
    ownerLine->setFixedSize(160, 20);

    nameLabel = new QLabel("<font face = Georgia size = 5>Название: </font>");
    ownerLabel = new QLabel("<font face = Georgia size = 5>Создатель:</font>");

    createButton = new QPushButton();
    createButton->setEnabled(false);
    createButton->setFlat(true);
    createButton->setIcon(QPixmap("image/register_button"));
    createButton->setIconSize(QSize(150, 30));
    createButton->setShortcut(QKeySequence(Qt::Key_Return));

    cancelButton = new QPushButton();
    cancelButton->setEnabled(true);
    cancelButton->setFlat(true);
    cancelButton->setIcon(QPixmap("image/cancel_button"));
    cancelButton->setIconSize(QSize(150, 30));

    QVBoxLayout *registerButtons = new QVBoxLayout();
    registerButtons->addWidget(cancelButton);
    registerButtons->addWidget(createButton);

    QFormLayout *labelLayout = new QFormLayout();
    labelLayout->addRow(nameLabel, nameLine);
    labelLayout->addRow(ownerLabel, ownerLine);
    labelLayout->setLabelAlignment(Qt::AlignRight);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(labelLayout,1,0);
    mainLayout->addLayout(registerButtons,1,1,Qt::AlignRight);

    setLayout(mainLayout);

    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(createButtonPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));

    connect(nameLine, SIGNAL(textChanged(QString)), this, SLOT(enableCreateButton(QString)));
    connect(ownerLine, SIGNAL(textChanged(QString)), this, SLOT(enableCreateButton(QString)));
}

void CreateLobby::enableCreateButton(QString text)
{
    createButton->setEnabled(!nameLine->text().isEmpty() && !ownerLine->text().isEmpty());
}

CreateLobbyView ::~CreateLobbyView()
{

}
