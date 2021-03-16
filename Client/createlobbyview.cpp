#include "createlobbyview.h"

CreateLobbyView::CreateLobbyView(QWidget *parent) :
    QWidget(parent)
{

}

void CreateLobby::drowElements()
{
    this->setWindowTitle("Создать лобби");
    this->setWindowIcon(QIcon("image/window.png"));
    this->setFixedSize(640, 360);
    //this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    image = new QLabel(this);
    i = new QImage("image/background.jpg");
    QImage img = i->scaled(QSize(this->width(),height()), Qt::IgnoreAspectRatio);
    image->show();
    image->resize(QSize(this->width(),height()));
    image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

    nameLine = new QLineEdit(this);
    //nameLine->setValidator(new QRegExpValidator(QRegExp("[a-zA-Zа-яА-Я]+")));
    nameLine->setMaxLength(30);
    nameLine->setFont(QFont("Georgia", 15, -1, false));
    nameLine->setFixedSize(325, 40);

    nameLabel = new QLabel("<font face = Georgia size = 6>Название: </font>");

    createButton = new QPushButton();
    createButton->setEnabled(false);
    createButton->setFlat(true);
    createButton->setIcon(QPixmap("image/create_button"));
    createButton->setIconSize(QSize(150, 30));
    createButton->setShortcut(QKeySequence(Qt::Key_Return));

    cancelButton = new QPushButton();
    cancelButton->setEnabled(true);
    cancelButton->setFlat(true);
    cancelButton->setIcon(QPixmap("image/cancel_button"));
    cancelButton->setIconSize(QSize(150, 30));

    QVBoxLayout *createButtons = new QVBoxLayout();
    createButtons->addWidget(cancelButton);
    createButtons->addWidget(createButton);

    QFormLayout *labelLayout = new QFormLayout();
    labelLayout->addRow(nameLabel, nameLine);
    labelLayout->setLabelAlignment(Qt::AlignRight);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(labelLayout,1,0);
    mainLayout->addLayout(createButtons,1,1,Qt::AlignRight);

    setLayout(mainLayout);
}

void CreateLobby::enableCreateButton()
{
    createButton->setEnabled(!nameLine->text().isEmpty());
}

CreateLobbyView ::~CreateLobbyView()
{

}
