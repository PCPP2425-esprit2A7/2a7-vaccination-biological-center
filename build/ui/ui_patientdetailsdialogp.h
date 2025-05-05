/********************************************************************************
** Form generated from reading UI file 'patientdetailsdialogp.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTDETAILSDIALOGP_H
#define UI_PATIENTDETAILSDIALOGP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientDetailsDialog
{
public:
    QGroupBox *headerGroup;
    QLabel *headerLabel;
    QLabel *logoLabel;
    QFrame *patientInfoFrame;
    QLabel *idLbl;
    QLabel *nomLbl;
    QLabel *prenomLbl;
    QLabel *genreLbl;
    QLabel *dateLbl;
    QLabel *telLbl;
    QLineEdit *idLineEdit;
    QLineEdit *nomLineEdit;
    QLineEdit *prenomLineEdit;
    QLineEdit *telLineEdit;
    QComboBox *genreComboBox;
    QDateEdit *dateEdit;
    QLabel *documentLbl;
    QLabel *documentNameLabel;
    QPushButton *browseButtonp;
    QLabel *documentSizeLabel;
    QLabel *patientInfoTitle;
    QWidget *layoutWidget;
    QHBoxLayout *actionButtonLayout;
    QPushButton *cancelButtonp;
    QPushButton *editButtonp;
    QPushButton *modifyButtonp;
    QPushButton *deleteButtonp;
    QFrame *documentFrame;
    QLabel *documentPreviewTitle;
    QWidget *layoutWidget_3;
    QHBoxLayout *documentButtonLayout;
    QPushButton *saveButtonp;
    QPushButton *pdfButtonp;

    void setupUi(QDialog *PatientDetailsDialog)
    {
        if (PatientDetailsDialog->objectName().isEmpty())
            PatientDetailsDialog->setObjectName("PatientDetailsDialog");
        PatientDetailsDialog->resize(900, 716);
        PatientDetailsDialog->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(243, 249, 251);"));
        headerGroup = new QGroupBox(PatientDetailsDialog);
        headerGroup->setObjectName("headerGroup");
        headerGroup->setGeometry(QRect(10, 10, 881, 91));
        headerGroup->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        headerLabel = new QLabel(headerGroup);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setGeometry(QRect(200, 20, 431, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(24);
        font.setBold(true);
        font.setItalic(true);
        headerLabel->setFont(font);
        headerLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        logoLabel = new QLabel(headerGroup);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(20, 10, 71, 71));
        logoLabel->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/Adobe Express - file (5).png);"));
        patientInfoFrame = new QFrame(PatientDetailsDialog);
        patientInfoFrame->setObjectName("patientInfoFrame");
        patientInfoFrame->setGeometry(QRect(20, 120, 401, 511));
        patientInfoFrame->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;\n"
"color:#030C54"));
        patientInfoFrame->setFrameShape(QFrame::Shape::StyledPanel);
        patientInfoFrame->setFrameShadow(QFrame::Shadow::Raised);
        idLbl = new QLabel(patientInfoFrame);
        idLbl->setObjectName("idLbl");
        idLbl->setGeometry(QRect(20, 50, 41, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Perpetua")});
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        idLbl->setFont(font1);
        idLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        nomLbl = new QLabel(patientInfoFrame);
        nomLbl->setObjectName("nomLbl");
        nomLbl->setGeometry(QRect(20, 100, 61, 31));
        nomLbl->setFont(font1);
        nomLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        prenomLbl = new QLabel(patientInfoFrame);
        prenomLbl->setObjectName("prenomLbl");
        prenomLbl->setGeometry(QRect(20, 150, 81, 31));
        prenomLbl->setFont(font1);
        prenomLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        genreLbl = new QLabel(patientInfoFrame);
        genreLbl->setObjectName("genreLbl");
        genreLbl->setGeometry(QRect(20, 200, 71, 31));
        genreLbl->setFont(font1);
        genreLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        dateLbl = new QLabel(patientInfoFrame);
        dateLbl->setObjectName("dateLbl");
        dateLbl->setGeometry(QRect(20, 250, 141, 31));
        dateLbl->setFont(font1);
        dateLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        telLbl = new QLabel(patientInfoFrame);
        telLbl->setObjectName("telLbl");
        telLbl->setGeometry(QRect(20, 300, 71, 31));
        telLbl->setFont(font1);
        telLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        idLineEdit = new QLineEdit(patientInfoFrame);
        idLineEdit->setObjectName("idLineEdit");
        idLineEdit->setGeometry(QRect(170, 50, 211, 31));
        idLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        idLineEdit->setReadOnly(true);
        nomLineEdit = new QLineEdit(patientInfoFrame);
        nomLineEdit->setObjectName("nomLineEdit");
        nomLineEdit->setGeometry(QRect(170, 100, 211, 31));
        nomLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        nomLineEdit->setReadOnly(true);
        prenomLineEdit = new QLineEdit(patientInfoFrame);
        prenomLineEdit->setObjectName("prenomLineEdit");
        prenomLineEdit->setGeometry(QRect(170, 150, 211, 31));
        prenomLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        prenomLineEdit->setReadOnly(true);
        telLineEdit = new QLineEdit(patientInfoFrame);
        telLineEdit->setObjectName("telLineEdit");
        telLineEdit->setGeometry(QRect(170, 300, 211, 31));
        telLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        telLineEdit->setReadOnly(true);
        genreComboBox = new QComboBox(patientInfoFrame);
        genreComboBox->addItem(QString());
        genreComboBox->addItem(QString());
        genreComboBox->setObjectName("genreComboBox");
        genreComboBox->setEnabled(false);
        genreComboBox->setGeometry(QRect(170, 200, 211, 31));
        genreComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        dateEdit = new QDateEdit(patientInfoFrame);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(170, 250, 211, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        dateEdit->setReadOnly(true);
        dateEdit->setCalendarPopup(true);
        documentLbl = new QLabel(patientInfoFrame);
        documentLbl->setObjectName("documentLbl");
        documentLbl->setGeometry(QRect(20, 350, 141, 31));
        documentLbl->setFont(font1);
        documentLbl->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        documentNameLabel = new QLabel(patientInfoFrame);
        documentNameLabel->setObjectName("documentNameLabel");
        documentNameLabel->setGeometry(QRect(170, 350, 211, 31));
        documentNameLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border: 1px solid gray;"));
        documentNameLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        browseButtonp = new QPushButton(patientInfoFrame);
        browseButtonp->setObjectName("browseButtonp");
        browseButtonp->setEnabled(false);
        browseButtonp->setGeometry(QRect(290, 390, 91, 31));
        browseButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));
        documentSizeLabel = new QLabel(patientInfoFrame);
        documentSizeLabel->setObjectName("documentSizeLabel");
        documentSizeLabel->setGeometry(QRect(20, 390, 241, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Perpetua")});
        font2.setPointSize(10);
        font2.setItalic(true);
        documentSizeLabel->setFont(font2);
        documentSizeLabel->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        patientInfoTitle = new QLabel(patientInfoFrame);
        patientInfoTitle->setObjectName("patientInfoTitle");
        patientInfoTitle->setGeometry(QRect(110, 10, 261, 31));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setUnderline(true);
        patientInfoTitle->setFont(font3);
        patientInfoTitle->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        layoutWidget = new QWidget(patientInfoFrame);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 440, 361, 61));
        actionButtonLayout = new QHBoxLayout(layoutWidget);
        actionButtonLayout->setObjectName("actionButtonLayout");
        actionButtonLayout->setContentsMargins(0, 0, 0, 0);
        cancelButtonp = new QPushButton(layoutWidget);
        cancelButtonp->setObjectName("cancelButtonp");
        cancelButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        actionButtonLayout->addWidget(cancelButtonp);

        editButtonp = new QPushButton(layoutWidget);
        editButtonp->setObjectName("editButtonp");
        editButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));

        actionButtonLayout->addWidget(editButtonp);

        modifyButtonp = new QPushButton(layoutWidget);
        modifyButtonp->setObjectName("modifyButtonp");
        modifyButtonp->setEnabled(false);
        modifyButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));

        actionButtonLayout->addWidget(modifyButtonp);

        deleteButtonp = new QPushButton(layoutWidget);
        deleteButtonp->setObjectName("deleteButtonp");
        deleteButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));

        actionButtonLayout->addWidget(deleteButtonp);

        documentFrame = new QFrame(PatientDetailsDialog);
        documentFrame->setObjectName("documentFrame");
        documentFrame->setGeometry(QRect(440, 120, 441, 441));
        documentFrame->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:30px;\n"
"background-color: none;\n"
"color:#030C54"));
        documentFrame->setFrameShape(QFrame::Shape::StyledPanel);
        documentFrame->setFrameShadow(QFrame::Shadow::Raised);
        documentPreviewTitle = new QLabel(documentFrame);
        documentPreviewTitle->setObjectName("documentPreviewTitle");
        documentPreviewTitle->setGeometry(QRect(120, 10, 261, 31));
        documentPreviewTitle->setFont(font3);
        documentPreviewTitle->setStyleSheet(QString::fromUtf8("border: none;\n"
"color:#030C54"));
        layoutWidget_3 = new QWidget(PatientDetailsDialog);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(440, 580, 441, 51));
        documentButtonLayout = new QHBoxLayout(layoutWidget_3);
        documentButtonLayout->setObjectName("documentButtonLayout");
        documentButtonLayout->setContentsMargins(0, 0, 0, 0);
        saveButtonp = new QPushButton(layoutWidget_3);
        saveButtonp->setObjectName("saveButtonp");
        saveButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));

        documentButtonLayout->addWidget(saveButtonp);

        pdfButtonp = new QPushButton(layoutWidget_3);
        pdfButtonp->setObjectName("pdfButtonp");
        pdfButtonp->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:15px;\n"
"background-color:#030C54;\n"
"color:white"));

        documentButtonLayout->addWidget(pdfButtonp);


        retranslateUi(PatientDetailsDialog);

        QMetaObject::connectSlotsByName(PatientDetailsDialog);
    } // setupUi

    void retranslateUi(QDialog *PatientDetailsDialog)
    {
        PatientDetailsDialog->setWindowTitle(QCoreApplication::translate("PatientDetailsDialog", "D\303\251tails du Patient", nullptr));
        headerGroup->setTitle(QString());
        headerLabel->setText(QCoreApplication::translate("PatientDetailsDialog", "D\303\251tails du Patient", nullptr));
        logoLabel->setText(QString());
        idLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "ID :", nullptr));
        nomLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Nom :", nullptr));
        prenomLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Pr\303\251nom :", nullptr));
        genreLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Genre :", nullptr));
        dateLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Date naissance :", nullptr));
        telLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Tel :", nullptr));
        genreComboBox->setItemText(0, QCoreApplication::translate("PatientDetailsDialog", "Homme", nullptr));
        genreComboBox->setItemText(1, QCoreApplication::translate("PatientDetailsDialog", "Femme", nullptr));

        documentLbl->setText(QCoreApplication::translate("PatientDetailsDialog", "Document :", nullptr));
        documentNameLabel->setText(QCoreApplication::translate("PatientDetailsDialog", "Aucun document", nullptr));
        browseButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Parcourir...", nullptr));
        documentSizeLabel->setText(QCoreApplication::translate("PatientDetailsDialog", "Taille du document : -- KB", nullptr));
        patientInfoTitle->setText(QCoreApplication::translate("PatientDetailsDialog", "Informations Patient", nullptr));
        cancelButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Fermer", nullptr));
        editButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Modifier", nullptr));
        modifyButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Enregistrer", nullptr));
        deleteButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Supprimer", nullptr));
        documentPreviewTitle->setText(QCoreApplication::translate("PatientDetailsDialog", "Aper\303\247u du Document", nullptr));
        saveButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Enregistrer Document", nullptr));
        pdfButtonp->setText(QCoreApplication::translate("PatientDetailsDialog", "Exporter PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientDetailsDialog: public Ui_PatientDetailsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTDETAILSDIALOGP_H
