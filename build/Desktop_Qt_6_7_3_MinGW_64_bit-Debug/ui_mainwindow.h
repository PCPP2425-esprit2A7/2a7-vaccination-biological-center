/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QGroupBox *groupBox_2;
    QFrame *frame;
    QLineEdit *ID;
    QLineEdit *titre;
    QDateEdit *dateM;
    QTextEdit *Desc;
    QComboBox *Type;
    QPushButton *ajouter;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QComboBox *Etat;
    QGroupBox *groupBox_3;
    QLabel *label_9;
    QTableWidget *tableWidget;
    QLineEdit *rech;
    QPushButton *rechb;
    QPushButton *deleteb;
    QPushButton *modb;
    QPushButton *pdfb;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_12;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1578, 861);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 231, 751));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 310, 211, 51));
        pushButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 430, 211, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 370, 211, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 490, 211, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 550, 211, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 610, 211, 51));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 670, 211, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 250, 211, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(-40, -30, 281, 191));
        label_10->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/Adobe Express - file (5).png);"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 120, 191, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(15);
        font.setWeight(QFont::Black);
        font.setItalic(true);
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);\n"
"font: 900 italic 15pt \"Segoe UI\";"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 260, 41, 31));
        label_13->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/Adobe Express - file.png);\n"
"background-color:#226597;"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 320, 41, 31));
        label_14->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/employe-Photoroom.png);\n"
"background-color:#226597;"));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(30, 380, 41, 31));
        label_15->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/Remove background project.png);\n"
"background-color:#226597;"));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(30, 440, 41, 31));
        label_16->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/Adobe Express - file (2).png);\n"
"background-color:#226597;"));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(30, 500, 41, 31));
        label_17->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/Adobe Express - file (3).png);\n"
"background-color:#226597;"));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(20, 560, 41, 31));
        label_18->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/equipement.png);\n"
"background-color:#226597;"));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(20, 620, 41, 31));
        label_19->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/patient.png);\n"
"background-color:#226597;"));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(20, 680, 41, 31));
        label_20->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/dec.png);\n"
"background-color:#226597;"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(230, 120, 1321, 631));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(true);
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);\n"
"color: rgb(0, 0, 0);"));
        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(70, 70, 351, 531));
        frame->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setGeometry(QRect(180, 40, 161, 28));
        ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        titre = new QLineEdit(frame);
        titre->setObjectName("titre");
        titre->setGeometry(QRect(180, 90, 161, 28));
        titre->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateM = new QDateEdit(frame);
        dateM->setObjectName("dateM");
        dateM->setGeometry(QRect(170, 400, 161, 29));
        dateM->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Desc = new QTextEdit(frame);
        Desc->setObjectName("Desc");
        Desc->setGeometry(QRect(130, 210, 211, 101));
        Desc->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        Type = new QComboBox(frame);
        Type->addItem(QString());
        Type->addItem(QString());
        Type->setObjectName("Type");
        Type->setGeometry(QRect(180, 140, 161, 28));
        Type->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        ajouter = new QPushButton(frame);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(90, 460, 171, 41));
        ajouter->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 40, 81, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Perpetua")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(true);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 90, 101, 31));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 140, 121, 31));
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 250, 121, 31));
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 400, 141, 31));
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 340, 121, 31));
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        Etat = new QComboBox(frame);
        Etat->addItem(QString());
        Etat->addItem(QString());
        Etat->addItem(QString());
        Etat->setObjectName("Etat");
        Etat->setGeometry(QRect(170, 340, 161, 28));
        Etat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(490, 50, 801, 541));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setItalic(true);
        groupBox_3->setFont(font3);
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 60, 141, 31));
        label_9->setFont(font2);
        label_9->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        tableWidget = new QTableWidget(groupBox_3);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 110, 761, 411));
        rech = new QLineEdit(groupBox_3);
        rech->setObjectName("rech");
        rech->setGeometry(QRect(160, 60, 301, 31));
        rech->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        rechb = new QPushButton(groupBox_3);
        rechb->setObjectName("rechb");
        rechb->setGeometry(QRect(470, 60, 41, 31));
        rechb->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/chercher.png);"));
        deleteb = new QPushButton(groupBox_3);
        deleteb->setObjectName("deleteb");
        deleteb->setGeometry(QRect(530, 60, 41, 31));
        deleteb->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/sup.png);"));
        modb = new QPushButton(groupBox_3);
        modb->setObjectName("modb");
        modb->setGeometry(QRect(590, 60, 41, 31));
        modb->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/mod.jpeg);"));
        pdfb = new QPushButton(groupBox_3);
        pdfb->setObjectName("pdfb");
        pdfb->setGeometry(QRect(650, 60, 41, 29));
        pdfb->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix2/image/pdff.png);"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(160, 50, 151, 31));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setItalic(true);
        label_8->setFont(font4);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 0, 1321, 121));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
""));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(460, 10, 591, 81));
        QFont font5;
        font5.setPointSize(50);
        font5.setBold(true);
        font5.setItalic(true);
        label_12->setFont(font5);
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Employes", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Vaccins", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Rendez-vous", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PDR", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Equipment", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Patients", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Deconnexion", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "acceuil", nullptr));
        label_10->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "Bio Med Centre", nullptr));
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        label_18->setText(QString());
        label_19->setText(QString());
        label_20->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        Type->setItemText(0, QCoreApplication::translate("MainWindow", "Consommables", nullptr));
        Type->setItemText(1, QCoreApplication::translate("MainWindow", "Machine", nullptr));

        ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID    :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Titre       :", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Description  :", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Date Maintenance:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        Etat->setItemText(0, QCoreApplication::translate("MainWindow", "Fonctionnel", nullptr));
        Etat->setItemText(1, QCoreApplication::translate("MainWindow", "D\303\251faillant", nullptr));
        Etat->setItemText(2, QCoreApplication::translate("MainWindow", "Prioritaire", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Liste Des Equipements", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "chercher equipement :", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Titre", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Date Maintenance", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        rechb->setText(QString());
        deleteb->setText(QString());
        modb->setText(QString());
        pdfb->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "Ajouter Equipement", nullptr));
        label->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "Bio Med Centre", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
