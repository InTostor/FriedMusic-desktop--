/********************************************************************************
** Form generated from reading UI file 'statusBar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBar
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *loggedAsLabel;
    QPushButton *settingsButton;

    void setupUi(QWidget *StatusBar)
    {
        if (StatusBar->objectName().isEmpty())
            StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        StatusBar->resize(160, 53);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StatusBar->sizePolicy().hasHeightForWidth());
        StatusBar->setSizePolicy(sizePolicy);
        StatusBar->setMaximumSize(QSize(16777215, 53));
        horizontalLayout = new QHBoxLayout(StatusBar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loggedAsLabel = new QLabel(StatusBar);
        loggedAsLabel->setObjectName(QString::fromUtf8("loggedAsLabel"));
        sizePolicy.setHeightForWidth(loggedAsLabel->sizePolicy().hasHeightForWidth());
        loggedAsLabel->setSizePolicy(sizePolicy);
        loggedAsLabel->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(loggedAsLabel);

        settingsButton = new QPushButton(StatusBar);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        settingsButton->setMinimumSize(QSize(35, 35));
        settingsButton->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(settingsButton);


        retranslateUi(StatusBar);

        QMetaObject::connectSlotsByName(StatusBar);
    } // setupUi

    void retranslateUi(QWidget *StatusBar)
    {
        StatusBar->setWindowTitle(QCoreApplication::translate("StatusBar", "Form", nullptr));
        loggedAsLabel->setText(QCoreApplication::translate("StatusBar", "logged as InTostor", nullptr));
        settingsButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StatusBar: public Ui_StatusBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // STATUSBAR_H
