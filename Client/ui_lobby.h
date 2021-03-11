/********************************************************************************
** Form generated from reading UI file 'lobby.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOBBY_H
#define UI_LOBBY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lobby
{
public:
    QPushButton *Exit;
    QPushButton *Start_game;
    QPushButton *Refresh_lobby;
    QLabel *Lobby_name;
    QLabel *Nickname;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Enter_lobby;
    QPushButton *Create_lobby;
    QPushButton *Exit_lobby;
    QPushButton *Delete_lobby;
    QPushButton *Stat_game;
    QGridLayout *gridLayout_2;
    QTableView *tableView;

    void setupUi(QWidget *Lobby)
    {
        if (Lobby->objectName().isEmpty())
            Lobby->setObjectName(QString::fromUtf8("Lobby"));
        Lobby->resize(690, 431);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../build-testClient-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/image/window.png"), QSize(), QIcon::Normal, QIcon::Off);
        Lobby->setWindowIcon(icon);
        Exit = new QPushButton(Lobby);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        Exit->setGeometry(QRect(10, 400, 75, 23));
        Start_game = new QPushButton(Lobby);
        Start_game->setObjectName(QString::fromUtf8("Start_game"));
        Start_game->setGeometry(QRect(230, 400, 75, 23));
        Refresh_lobby = new QPushButton(Lobby);
        Refresh_lobby->setObjectName(QString::fromUtf8("Refresh_lobby"));
        Refresh_lobby->setGeometry(QRect(330, 400, 75, 23));
        Lobby_name = new QLabel(Lobby);
        Lobby_name->setObjectName(QString::fromUtf8("Lobby_name"));
        Lobby_name->setGeometry(QRect(290, 10, 61, 21));
        QFont font;
        font.setPointSize(12);
        Lobby_name->setFont(font);
        Nickname = new QLabel(Lobby);
        Nickname->setObjectName(QString::fromUtf8("Nickname"));
        Nickname->setGeometry(QRect(10, 10, 261, 21));
        Nickname->setFont(font);
        gridLayoutWidget = new QWidget(Lobby);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 671, 361));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Enter_lobby = new QPushButton(gridLayoutWidget);
        Enter_lobby->setObjectName(QString::fromUtf8("Enter_lobby"));

        verticalLayout_2->addWidget(Enter_lobby);

        Create_lobby = new QPushButton(gridLayoutWidget);
        Create_lobby->setObjectName(QString::fromUtf8("Create_lobby"));

        verticalLayout_2->addWidget(Create_lobby);

        Exit_lobby = new QPushButton(gridLayoutWidget);
        Exit_lobby->setObjectName(QString::fromUtf8("Exit_lobby"));

        verticalLayout_2->addWidget(Exit_lobby);

        Delete_lobby = new QPushButton(gridLayoutWidget);
        Delete_lobby->setObjectName(QString::fromUtf8("Delete_lobby"));

        verticalLayout_2->addWidget(Delete_lobby);

        Stat_game = new QPushButton(gridLayoutWidget);
        Stat_game->setObjectName(QString::fromUtf8("Stat_game"));

        verticalLayout_2->addWidget(Stat_game);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableView = new QTableView(gridLayoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(Lobby);

        QMetaObject::connectSlotsByName(Lobby);
    } // setupUi

    void retranslateUi(QWidget *Lobby)
    {
        Lobby->setWindowTitle(QCoreApplication::translate("Lobby", "\320\233\320\276\320\261\320\261\320\270", nullptr));
        Exit->setText(QCoreApplication::translate("Lobby", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        Start_game->setText(QCoreApplication::translate("Lobby", "\320\223\320\276\321\202\320\276\320\262", nullptr));
        Refresh_lobby->setText(QCoreApplication::translate("Lobby", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        Lobby_name->setText(QCoreApplication::translate("Lobby", "\320\233\320\236\320\221\320\221\320\230", nullptr));
        Nickname->setText(QString());
        Enter_lobby->setText(QCoreApplication::translate("Lobby", "\320\222\320\276\320\271\321\202\320\270 \320\262 \320\273\320\276\320\261\320\261\320\270", nullptr));
        Create_lobby->setText(QCoreApplication::translate("Lobby", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\273\320\276\320\261\320\261\320\270", nullptr));
        Exit_lobby->setText(QCoreApplication::translate("Lobby", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\273\320\276\320\261\320\261\320\270", nullptr));
        Delete_lobby->setText(QCoreApplication::translate("Lobby", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\273\320\276\320\261\320\261\320\270", nullptr));
        Stat_game->setText(QCoreApplication::translate("Lobby", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lobby: public Ui_Lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOBBY_H
