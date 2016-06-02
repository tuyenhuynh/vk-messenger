/********************************************************************************
** Form generated from reading UI file 'messenger.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGER_H
#define UI_MESSENGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MessengerClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QFrame *chatFrame;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *peerAvatar;
    QLabel *partnerName;
    QTableWidget *friendList;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *gif;
    QLabel *label;
    QLabel *myAvatar;
    QLabel *myName;
    QLabel *label_2;
    QTextEdit *chatContent;
    QHBoxLayout *horizontalLayout;
    QLineEdit *message;
    QPushButton *btnSend;
    QFrame *loginFrame;
    QFormLayout *formLayout;
    QWebView *webView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MessengerClass)
    {
        if (MessengerClass->objectName().isEmpty())
            MessengerClass->setObjectName(QString::fromUtf8("MessengerClass"));
        MessengerClass->resize(863, 586);
        centralWidget = new QWidget(MessengerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        chatFrame = new QFrame(centralWidget);
        chatFrame->setObjectName(QString::fromUtf8("chatFrame"));
        chatFrame->setEnabled(true);
        chatFrame->setFrameShape(QFrame::StyledPanel);
        chatFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(chatFrame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        peerAvatar = new QLabel(chatFrame);
        peerAvatar->setObjectName(QString::fromUtf8("peerAvatar"));
        peerAvatar->setMinimumSize(QSize(50, 50));
        peerAvatar->setMaximumSize(QSize(50, 50));

        verticalLayout->addWidget(peerAvatar);

        partnerName = new QLabel(chatFrame);
        partnerName->setObjectName(QString::fromUtf8("partnerName"));

        verticalLayout->addWidget(partnerName);

        friendList = new QTableWidget(chatFrame);
        if (friendList->columnCount() < 1)
            friendList->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        friendList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        friendList->setObjectName(QString::fromUtf8("friendList"));
        friendList->setMaximumSize(QSize(300, 16777215));
        friendList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        friendList->horizontalHeader()->setVisible(true);
        friendList->verticalHeader()->setVisible(true);

        verticalLayout->addWidget(friendList);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gif = new QLabel(chatFrame);
        gif->setObjectName(QString::fromUtf8("gif"));
        gif->setMinimumSize(QSize(50, 50));
        gif->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(gif);

        label = new QLabel(chatFrame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        myAvatar = new QLabel(chatFrame);
        myAvatar->setObjectName(QString::fromUtf8("myAvatar"));
        myAvatar->setMinimumSize(QSize(50, 50));
        myAvatar->setMaximumSize(QSize(50, 50));

        horizontalLayout_2->addWidget(myAvatar);

        myName = new QLabel(chatFrame);
        myName->setObjectName(QString::fromUtf8("myName"));

        horizontalLayout_2->addWidget(myName);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_2 = new QLabel(chatFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        chatContent = new QTextEdit(chatFrame);
        chatContent->setObjectName(QString::fromUtf8("chatContent"));

        verticalLayout_2->addWidget(chatContent);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        message = new QLineEdit(chatFrame);
        message->setObjectName(QString::fromUtf8("message"));

        horizontalLayout->addWidget(message);

        btnSend = new QPushButton(chatFrame);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        horizontalLayout->addWidget(btnSend);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(chatFrame, 0, 0, 1, 1);

        loginFrame = new QFrame(centralWidget);
        loginFrame->setObjectName(QString::fromUtf8("loginFrame"));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(loginFrame);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        webView = new QWebView(loginFrame);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        formLayout->setWidget(0, QFormLayout::SpanningRole, webView);


        gridLayout_2->addWidget(loginFrame, 1, 0, 1, 1);

        MessengerClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MessengerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MessengerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MessengerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MessengerClass->setStatusBar(statusBar);

        retranslateUi(MessengerClass);

        QMetaObject::connectSlotsByName(MessengerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MessengerClass)
    {
        MessengerClass->setWindowTitle(QApplication::translate("MessengerClass", "Messenger", 0, QApplication::UnicodeUTF8));
        peerAvatar->setText(QString());
        partnerName->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = friendList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MessengerClass", "Name", 0, QApplication::UnicodeUTF8));
        gif->setText(QApplication::translate("MessengerClass", "gif", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        myAvatar->setText(QString());
        myName->setText(QString());
        label_2->setText(QString());
        btnSend->setText(QApplication::translate("MessengerClass", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MessengerClass: public Ui_MessengerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
