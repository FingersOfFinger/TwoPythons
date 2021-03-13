#include "deletelobbyview.h"

DeleteLobbyView::DeleteLobbyView(QWidget *parent) :
    QWidget(parent)
{

}

void DeleteLobby::drowElements()
{
    this->setWindowTitle("Удалить лобби");
    this->setWindowIcon(QIcon("image/about.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    deleteButton = new QPushButton();
    deleteButton->setFlat(true);
    deleteButton->setIcon(QPixmap("image/delete_button"));
    deleteButton->setIconSize(QSize(150, 30));
    deleteButton->setShortcut(QKeySequence(Qt::Key_Return));

    cancelButton = new QPushButton();
    cancelButton->setEnabled(true);
    cancelButton->setFlat(true);
    cancelButton->setIcon(QPixmap("image/cancel_button"));
    cancelButton->setIconSize(QSize(150, 30));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(deleteButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

DeleteLobbyView ::~DeleteLobbyView()
{

}
