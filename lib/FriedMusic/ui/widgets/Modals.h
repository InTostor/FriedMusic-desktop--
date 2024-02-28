#pragma once

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include "../../Data.hpp"
#include "../../StandartGlobalUser.hpp"
#include "../../macro.hpp"
#include "../ui.hpp"
#include <iostream>


class TrackActionsModal : public virtual StandartGlobalUser, public QWidget{


public:
    QVBoxLayout *mainLayout;
    QCheckBox *downloadCheckbox;
    QCheckBox *favouriteCheckbox;

    void setup(Track track)
    {
        if (this->objectName().isEmpty())
            this->setObjectName(QString::fromUtf8("this"));
        this->resize(400, 300);
        this->setWindowFlag(Qt::Popup);
        mainLayout = new QVBoxLayout(this);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        downloadCheckbox = new QCheckBox(this);
        downloadCheckbox->setObjectName(QString::fromUtf8("downloadCheckbox"));

        mainLayout->addWidget(downloadCheckbox);

        favouriteCheckbox = new QCheckBox(this);
        favouriteCheckbox->setObjectName(QString::fromUtf8("favouriteCheckbox"));

        mainLayout->addWidget(favouriteCheckbox);

        downloadCheckbox->setText("Download");
        favouriteCheckbox->setText("Favourite");
        
        if (client->isTrackDownloaded(track)){
          downloadCheckbox->setCheckState(Qt::Checked);
        }else{
          downloadCheckbox->setCheckState(Qt::Unchecked);
        }
        if (client->isTrackDownloaded(track)){
          downloadCheckbox->setCheckState(Qt::Checked);
        }else{
          downloadCheckbox->setCheckState(Qt::Unchecked);
        }

        QMetaObject::connectSlotsByName(this);
    } // setupUi

};
