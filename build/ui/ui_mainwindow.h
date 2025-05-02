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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QLabel *label_12;
    QLabel *label_14;
    QLabel *label;
    QGroupBox *groupBox_2;
    QFrame *frame_8;
    QLineEdit *nom;
    QLineEdit *tel;
    QLineEdit *email;
    QLineEdit *mdp;
    QLineEdit *address;
    QLineEdit *salaire;
    QComboBox *role;
    QLabel *label_9;
    QPushButton *ajouter;
    QLabel *label_10;
    QLineEdit *id;
    QPushButton *cancelButton;
    QLabel *label_18;
    QLabel *label_20;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_21;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_2;
    QLineEdit *rfidUID;
    QFrame *frame;
    QLabel *label_11;
    QTableWidget *tableWidget;
    QPushButton *deleteb;
    QLineEdit *rech;
    QLabel *label_15;
    QComboBox *sortComboBox;
    QPushButton *pdfb;
    QWidget *chartLayout;
    QLabel *label_13;
    QGroupBox *loginGroupBox;
    QFrame *loginFrame;
    QLabel *loginTitle;
    QLineEdit *loginEmail;
    QLineEdit *loginPassword;
    QLabel *emailLabel;
    QLabel *passwordLabel;
    QPushButton *loginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1260, 840);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 181, 801));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 63,103);"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 120, 151, 41));
        pushButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 170, 151, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 270, 151, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 320, 151, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 220, 151, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 370, 151, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(10, 420, 151, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        pushButton_8 = new QPushButton(groupBox);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 470, 151, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 10, 141, 101));
        label_12->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/Adobe Express - file (5).png);"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 90, 121, 16));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 0, 1081, 91));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 63,103);"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(180, 90, 1071, 711));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(true);
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        frame_8 = new QFrame(groupBox_2);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(20, 40, 371, 351));
        frame_8->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        nom = new QLineEdit(frame_8);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(150, 80, 113, 22));
        tel = new QLineEdit(frame_8);
        tel->setObjectName("tel");
        tel->setGeometry(QRect(150, 110, 113, 22));
        email = new QLineEdit(frame_8);
        email->setObjectName("email");
        email->setGeometry(QRect(150, 140, 113, 22));
        mdp = new QLineEdit(frame_8);
        mdp->setObjectName("mdp");
        mdp->setGeometry(QRect(150, 170, 113, 22));
        address = new QLineEdit(frame_8);
        address->setObjectName("address");
        address->setGeometry(QRect(150, 200, 113, 22));
        salaire = new QLineEdit(frame_8);
        salaire->setObjectName("salaire");
        salaire->setGeometry(QRect(150, 260, 113, 22));
        role = new QComboBox(frame_8);
        role->addItem(QString());
        role->addItem(QString());
        role->addItem(QString());
        role->setObjectName("role");
        role->setGeometry(QRect(150, 230, 111, 22));
        label_9 = new QLabel(frame_8);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 0, 181, 31));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setItalic(true);
        label_9->setFont(font2);
        ajouter = new QPushButton(frame_8);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(150, 320, 75, 24));
        label_10 = new QLabel(frame_8);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 50, 49, 16));
        label_10->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        id = new QLineEdit(frame_8);
        id->setObjectName("id");
        id->setGeometry(QRect(150, 50, 111, 22));
        cancelButton = new QPushButton(frame_8);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(230, 320, 75, 24));
        label_18 = new QLabel(frame_8);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 80, 121, 16));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Palatino Linotype")});
        font3.setPointSize(12);
        label_18->setFont(font3);
        label_18->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_20 = new QLabel(frame_8);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 110, 51, 16));
        label_20->setFont(font3);
        label_20->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_22 = new QLabel(frame_8);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 140, 49, 16));
        label_22->setFont(font3);
        label_22->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_23 = new QLabel(frame_8);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 170, 111, 16));
        label_23->setFont(font3);
        label_23->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_21 = new QLabel(frame_8);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 200, 71, 16));
        label_21->setFont(font3);
        label_21->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_24 = new QLabel(frame_8);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(10, 230, 49, 16));
        label_24->setFont(font3);
        label_24->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_25 = new QLabel(frame_8);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 260, 61, 16));
        label_25->setFont(font3);
        label_25->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        label_2 = new QLabel(frame_8);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 290, 71, 16));
        label_2->setStyleSheet(QString::fromUtf8("color:#030C54;\n"
"border:none;"));
        rfidUID = new QLineEdit(frame_8);
        rfidUID->setObjectName("rfidUID");
        rfidUID->setGeometry(QRect(150, 290, 113, 22));
        frame = new QFrame(groupBox_2);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 400, 941, 261));
        frame->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(30, 0, 181, 31));
        label_11->setFont(font2);
        tableWidget = new QTableWidget(frame);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 50, 901, 241));
        deleteb = new QPushButton(frame);
        deleteb->setObjectName("deleteb");
        deleteb->setGeometry(QRect(570, 10, 31, 31));
        deleteb->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/resources/sup.png);"));
        rech = new QLineEdit(frame);
        rech->setObjectName("rech");
        rech->setGeometry(QRect(310, 10, 251, 31));
        label_15 = new QLabel(frame);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(270, 10, 31, 21));
        label_15->setStyleSheet(QString::fromUtf8("border:none;"));
        sortComboBox = new QComboBox(frame);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");
        sortComboBox->setGeometry(QRect(620, 10, 151, 31));
        pdfb = new QPushButton(frame);
        pdfb->setObjectName("pdfb");
        pdfb->setGeometry(QRect(780, 10, 31, 29));
        chartLayout = new QWidget(groupBox_2);
        chartLayout->setObjectName("chartLayout");
        chartLayout->setGeometry(QRect(410, 40, 531, 341));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(380, 10, 601, 61));
        QFont font4;
        font4.setPointSize(50);
        font4.setBold(true);
        font4.setItalic(true);
        label_13->setFont(font4);
        label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        loginGroupBox = new QGroupBox(centralwidget);
        loginGroupBox->setObjectName("loginGroupBox");
        loginGroupBox->setGeometry(QRect(0, 0, 1461, 801));
        loginGroupBox->setFont(font1);
        loginGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        loginFrame = new QFrame(loginGroupBox);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setGeometry(QRect(410, 200, 471, 351));
        loginFrame->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;"));
        loginFrame->setFrameShape(QFrame::Shape::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Shadow::Raised);
        loginTitle = new QLabel(loginFrame);
        loginTitle->setObjectName("loginTitle");
        loginTitle->setGeometry(QRect(30, 20, 411, 41));
        QFont font5;
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setItalic(true);
        loginTitle->setFont(font5);
        loginTitle->setStyleSheet(QString::fromUtf8("border: none;"));
        loginTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginEmail = new QLineEdit(loginFrame);
        loginEmail->setObjectName("loginEmail");
        loginEmail->setGeometry(QRect(150, 120, 251, 31));
        loginPassword = new QLineEdit(loginFrame);
        loginPassword->setObjectName("loginPassword");
        loginPassword->setGeometry(QRect(150, 180, 251, 31));
        loginPassword->setEchoMode(QLineEdit::EchoMode::Password);
        emailLabel = new QLabel(loginFrame);
        emailLabel->setObjectName("emailLabel");
        emailLabel->setGeometry(QRect(70, 120, 71, 31));
        QFont font6;
        font6.setPointSize(12);
        emailLabel->setFont(font6);
        emailLabel->setStyleSheet(QString::fromUtf8("border: none;"));
        passwordLabel = new QLabel(loginFrame);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setGeometry(QRect(20, 180, 121, 31));
        passwordLabel->setFont(font6);
        passwordLabel->setStyleSheet(QString::fromUtf8("border: none;"));
        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(150, 250, 251, 41));
        QFont font7;
        font7.setPointSize(12);
        font7.setBold(true);
        loginButton->setFont(font7);
        loginButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1260, 22));
        MainWindow->setMenuBar(menubar);
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
        pushButton->setText(QCoreApplication::translate("MainWindow", "Acceuil", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Employes", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Vaccins", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PDR", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Rendez-vous", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Equipements", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Patients", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Deconnexion", nullptr));
        label_12->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Bio med center", nullptr));
        label->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Gestion d'employes", nullptr));
        role->setItemText(0, QCoreApplication::translate("MainWindow", "Chercheur ", nullptr));
        role->setItemText(1, QCoreApplication::translate("MainWindow", "Administrateur ", nullptr));
        role->setItemText(2, QCoreApplication::translate("MainWindow", "Technicien ", nullptr));

        label_9->setText(QCoreApplication::translate("MainWindow", "Ajouter un Employe", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter ", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        cancelButton->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Nom et Prenom :", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Tel :", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Email : ", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Mot de Passe : ", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Adresse : ", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Role : ", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Salaire : ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "RFID_UID :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "employ\303\251 existant", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Mot de Passe", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "FaceId", nullptr));
        deleteb->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "A-Z", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Z-A", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Admin > Technicien", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Technicien > Admin", nullptr));

        pdfb->setText(QCoreApplication::translate("MainWindow", "pdf", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "BIO MED CENTER", nullptr));
        loginGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Connexion", nullptr));
        loginTitle->setText(QCoreApplication::translate("MainWindow", "Bienvenue \303\240 BIO MED CENTER", nullptr));
        loginEmail->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre email", nullptr));
        loginPassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre mot de passe", nullptr));
        emailLabel->setText(QCoreApplication::translate("MainWindow", "Email :", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "Mot de passe :", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Se connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
