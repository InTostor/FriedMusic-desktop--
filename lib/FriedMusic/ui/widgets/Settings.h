/********************************************************************************
** Form generated from reading UI file 'Settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QApplication>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "../ui.hpp"

class Settings: public QWidget, public virtual StandartGlobalUser
{
public:
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *accountConf;
    QFormLayout *formLayout_2;
    QWidget *tab;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *pathsConf;
    QGridLayout *gridLayout_3;
    QVBoxLayout *remotePaths;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_6;
    QWidget *aboutPage;
    QVBoxLayout *verticalLayout;
    QLabel *aboutPageHeader;
    QLabel *aboutPageLabel_1;
    QLabel *aboutPageLabel_2;
    QLabel *aboutPageLabel_3;
    QLabel *aboutPageLabel_4;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(756, 422);
        verticalLayout_5 = new QVBoxLayout(Settings);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabWidget = new QTabWidget(Settings);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::West);
        accountConf = new QWidget();
        accountConf->setObjectName(QString::fromUtf8("accountConf"));
        formLayout_2 = new QFormLayout(accountConf);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        tabWidget->addTab(accountConf, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        gridLayout->addLayout(verticalLayout_4, 0, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        pathsConf = new QWidget();
        pathsConf->setObjectName(QString::fromUtf8("pathsConf"));
        gridLayout_3 = new QGridLayout(pathsConf);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        remotePaths = new QVBoxLayout();
        remotePaths->setObjectName(QString::fromUtf8("remotePaths"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(pathsConf);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit = new QLineEdit(pathsConf);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);


        remotePaths->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(pathsConf);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(pathsConf);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);


        remotePaths->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(pathsConf);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_3 = new QLineEdit(pathsConf);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_2->addWidget(lineEdit_3);


        remotePaths->addLayout(horizontalLayout_2);


        gridLayout_3->addLayout(remotePaths, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(pathsConf);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_5 = new QLineEdit(pathsConf);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        horizontalLayout_6->addWidget(lineEdit_5);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(pathsConf);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_4 = new QLineEdit(pathsConf);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_4->addWidget(lineEdit_4);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(pathsConf);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_6 = new QLineEdit(pathsConf);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        horizontalLayout_5->addWidget(lineEdit_6);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout_3->addLayout(verticalLayout_2, 1, 2, 1, 1);

        tabWidget->addTab(pathsConf, QString());
        aboutPage = new QWidget();
        aboutPage->setObjectName(QString::fromUtf8("aboutPage"));
        verticalLayout = new QVBoxLayout(aboutPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        aboutPageHeader = new QLabel(aboutPage);
        aboutPageHeader->setObjectName(QString::fromUtf8("aboutPageHeader"));
        aboutPageHeader->setMaximumSize(QSize(16777215, 70));
        QFont font;
        font.setPointSize(36);
        aboutPageHeader->setFont(font);

        verticalLayout->addWidget(aboutPageHeader);

        aboutPageLabel_1 = new QLabel(aboutPage);
        aboutPageLabel_1->setObjectName(QString::fromUtf8("aboutPageLabel_1"));
        aboutPageLabel_1->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setPointSize(24);
        aboutPageLabel_1->setFont(font1);

        verticalLayout->addWidget(aboutPageLabel_1);

        aboutPageLabel_2 = new QLabel(aboutPage);
        aboutPageLabel_2->setObjectName(QString::fromUtf8("aboutPageLabel_2"));
        aboutPageLabel_2->setMaximumSize(QSize(16777215, 50));
        aboutPageLabel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(aboutPageLabel_2);

        aboutPageLabel_3 = new QLabel(aboutPage);
        aboutPageLabel_3->setObjectName(QString::fromUtf8("aboutPageLabel_3"));

        verticalLayout->addWidget(aboutPageLabel_3);

        aboutPageLabel_4 = new QLabel(aboutPage);
        aboutPageLabel_4->setObjectName(QString::fromUtf8("aboutPageLabel_4"));
        aboutPageLabel_4->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout->addWidget(aboutPageLabel_4);

        tabWidget->addTab(aboutPage, QString());

        verticalLayout_5->addWidget(tabWidget);


        retranslateUi(Settings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(accountConf), QCoreApplication::translate("Settings", "Account", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Settings", "Behaviour", nullptr));
        label_3->setText(QCoreApplication::translate("Settings", "API URl", nullptr));
        label_2->setText(QCoreApplication::translate("Settings", "Remote music storage (http, ftp, rtp etc)", nullptr));
        label->setText(QCoreApplication::translate("Settings", "Remote userdata storage (http,ftp,rtp etc)", nullptr));
        label_6->setText(QCoreApplication::translate("Settings", "Local database path", nullptr));
        label_5->setText(QCoreApplication::translate("Settings", "Local music storage", nullptr));
        label_4->setText(QCoreApplication::translate("Settings", "Local userdata storage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pathsConf), QCoreApplication::translate("Settings", "Paths", nullptr));
        aboutPageHeader->setText(QCoreApplication::translate("Settings", "About", nullptr));
        aboutPageLabel_1->setText(QCoreApplication::translate("Settings", "Fried Music", nullptr));
        aboutPageLabel_2->setText(QCoreApplication::translate("Settings", "Python+Qt+VLC 1.0", nullptr));
        aboutPageLabel_3->setText(QCoreApplication::translate("Settings", "Music player with remote/self hosted library", nullptr));
        aboutPageLabel_4->setText(QCoreApplication::translate("Settings", "2023 InTostor. MIT license", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(aboutPage), QCoreApplication::translate("Settings", "About", nullptr));
    } // retranslateUi

    Settings(){
        Settings::setupUi(this);
    }
};


#endif // SETTINGS_H
