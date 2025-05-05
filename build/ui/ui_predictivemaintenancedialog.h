/********************************************************************************
** Form generated from reading UI file 'predictivemaintenancedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREDICTIVEMAINTENANCEDIALOG_H
#define UI_PREDICTIVEMAINTENANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PredictiveMaintenanceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *headerWidget;
    QLabel *headerTitle;
    QWidget *contentWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebarWidget;
    QLabel *sidebarTitle;
    QFrame *statusFrame;
    QLabel *summaryTitle;
    QLabel *totalLabel;
    QLabel *functionalLabel;
    QLabel *damagedLabel;
    QLabel *atRiskLabel;
    QPushButton *generateOrdersBtn;
    QPushButton *runPredictionsBtn;
    QPushButton *viewMaintenanceHistoryBtn;
    QPushButton *closeBtn;
    QTabWidget *mainTabWidget;
    QWidget *predictionsTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *predictionsGroup;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *filterLayout;
    QLabel *thresholdLabel;
    QComboBox *thresholdComboBox;
    QPushButton *checkPredictionsBtn;
    QSpacerItem *horizontalSpacer;
    QTableWidget *predictionsTable;
    QWidget *maintenanceTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *selectedEquipmentGroup;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *selectedEquipmentLayout;
    QLabel *selectedIdLabel;
    QLabel *selectedIdValue;
    QLabel *selectedNameLabel;
    QLabel *selectedNameValue;
    QLabel *selectedTypeLabel;
    QLabel *selectedTypeValue;
    QFormLayout *selectedStatusLayout;
    QLabel *selectedStatusLabel;
    QLabel *selectedStatusValue;
    QLabel *predFailureLabel;
    QLabel *predFailureValue;
    QGroupBox *maintenanceDetailsGroup;
    QFormLayout *maintenanceLayout;
    QLabel *maintCostLabel;
    QLineEdit *maintenanceCostEdit;
    QLabel *maintDetailsLabel;
    QTextEdit *maintenanceDetailsEdit;
    QPushButton *recordMaintenanceBtn;
    QWidget *historyTab;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *historyGroup;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *historyFilterLayout;
    QLabel *historyFilterLabel;
    QComboBox *equipmentFilterCombo;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *historyTable;
    QWidget *footerWidget;
    QLabel *footerLabel;

    void setupUi(QDialog *PredictiveMaintenanceDialog)
    {
        if (PredictiveMaintenanceDialog->objectName().isEmpty())
            PredictiveMaintenanceDialog->setObjectName("PredictiveMaintenanceDialog");
        PredictiveMaintenanceDialog->resize(1200, 750);
        PredictiveMaintenanceDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        verticalLayout = new QVBoxLayout(PredictiveMaintenanceDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QWidget(PredictiveMaintenanceDialog);
        headerWidget->setObjectName("headerWidget");
        headerWidget->setMinimumSize(QSize(0, 120));
        headerWidget->setMaximumSize(QSize(16777215, 120));
        headerWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);"));
        headerTitle = new QLabel(headerWidget);
        headerTitle->setObjectName("headerTitle");
        headerTitle->setGeometry(QRect(350, 20, 500, 81));
        QFont font;
        font.setPointSize(30);
        font.setBold(true);
        font.setItalic(true);
        headerTitle->setFont(font);
        headerTitle->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        headerTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(headerWidget);

        contentWidget = new QWidget(PredictiveMaintenanceDialog);
        contentWidget->setObjectName("contentWidget");
        contentWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        horizontalLayout = new QHBoxLayout(contentWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarWidget = new QWidget(contentWidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setMinimumSize(QSize(230, 0));
        sidebarWidget->setMaximumSize(QSize(230, 16777215));
        sidebarWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);"));
        sidebarTitle = new QLabel(sidebarWidget);
        sidebarTitle->setObjectName("sidebarTitle");
        sidebarTitle->setGeometry(QRect(10, 20, 211, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(true);
        sidebarTitle->setFont(font1);
        sidebarTitle->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        sidebarTitle->setAlignment(Qt::AlignCenter);
        statusFrame = new QFrame(sidebarWidget);
        statusFrame->setObjectName("statusFrame");
        statusFrame->setGeometry(QRect(10, 80, 211, 171));
        statusFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(34, 101, 151);\n"
"border-radius: 20px;"));
        statusFrame->setFrameShape(QFrame::StyledPanel);
        statusFrame->setFrameShadow(QFrame::Raised);
        summaryTitle = new QLabel(statusFrame);
        summaryTitle->setObjectName("summaryTitle");
        summaryTitle->setGeometry(QRect(0, 10, 211, 31));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setItalic(true);
        summaryTitle->setFont(font2);
        summaryTitle->setStyleSheet(QString::fromUtf8("color: white;"));
        summaryTitle->setAlignment(Qt::AlignCenter);
        totalLabel = new QLabel(statusFrame);
        totalLabel->setObjectName("totalLabel");
        totalLabel->setGeometry(QRect(20, 50, 171, 31));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        totalLabel->setFont(font3);
        totalLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        functionalLabel = new QLabel(statusFrame);
        functionalLabel->setObjectName("functionalLabel");
        functionalLabel->setGeometry(QRect(20, 80, 171, 31));
        QFont font4;
        font4.setPointSize(10);
        functionalLabel->setFont(font4);
        functionalLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        damagedLabel = new QLabel(statusFrame);
        damagedLabel->setObjectName("damagedLabel");
        damagedLabel->setGeometry(QRect(20, 110, 171, 31));
        damagedLabel->setFont(font4);
        damagedLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        atRiskLabel = new QLabel(statusFrame);
        atRiskLabel->setObjectName("atRiskLabel");
        atRiskLabel->setGeometry(QRect(20, 140, 171, 31));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setItalic(false);
        atRiskLabel->setFont(font5);
        atRiskLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        generateOrdersBtn = new QPushButton(sidebarWidget);
        generateOrdersBtn->setObjectName("generateOrdersBtn");
        generateOrdersBtn->setGeometry(QRect(10, 280, 211, 51));
        generateOrdersBtn->setFont(font4);
        generateOrdersBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        runPredictionsBtn = new QPushButton(sidebarWidget);
        runPredictionsBtn->setObjectName("runPredictionsBtn");
        runPredictionsBtn->setGeometry(QRect(10, 340, 211, 51));
        runPredictionsBtn->setFont(font4);
        runPredictionsBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        viewMaintenanceHistoryBtn = new QPushButton(sidebarWidget);
        viewMaintenanceHistoryBtn->setObjectName("viewMaintenanceHistoryBtn");
        viewMaintenanceHistoryBtn->setGeometry(QRect(10, 400, 211, 51));
        viewMaintenanceHistoryBtn->setFont(font4);
        viewMaintenanceHistoryBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));
        closeBtn = new QPushButton(sidebarWidget);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setGeometry(QRect(10, 580, 211, 51));
        closeBtn->setFont(font4);
        closeBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        horizontalLayout->addWidget(sidebarWidget);

        mainTabWidget = new QTabWidget(contentWidget);
        mainTabWidget->setObjectName("mainTabWidget");
        mainTabWidget->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\";"));
        predictionsTab = new QWidget();
        predictionsTab->setObjectName("predictionsTab");
        verticalLayout_2 = new QVBoxLayout(predictionsTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        predictionsGroup = new QGroupBox(predictionsTab);
        predictionsGroup->setObjectName("predictionsGroup");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Segoe UI")});
        font6.setPointSize(20);
        font6.setBold(true);
        font6.setItalic(true);
        font6.setUnderline(false);
        predictionsGroup->setFont(font6);
        verticalLayout_3 = new QVBoxLayout(predictionsGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        filterLayout = new QHBoxLayout();
        filterLayout->setObjectName("filterLayout");
        thresholdLabel = new QLabel(predictionsGroup);
        thresholdLabel->setObjectName("thresholdLabel");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Perpetua")});
        font7.setPointSize(12);
        font7.setBold(true);
        font7.setItalic(true);
        thresholdLabel->setFont(font7);
        thresholdLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        filterLayout->addWidget(thresholdLabel);

        thresholdComboBox = new QComboBox(predictionsGroup);
        thresholdComboBox->addItem(QString());
        thresholdComboBox->addItem(QString());
        thresholdComboBox->addItem(QString());
        thresholdComboBox->addItem(QString());
        thresholdComboBox->addItem(QString());
        thresholdComboBox->setObjectName("thresholdComboBox");
        thresholdComboBox->setMinimumSize(QSize(100, 0));
        thresholdComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        filterLayout->addWidget(thresholdComboBox);

        checkPredictionsBtn = new QPushButton(predictionsGroup);
        checkPredictionsBtn->setObjectName("checkPredictionsBtn");
        checkPredictionsBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        filterLayout->addWidget(checkPredictionsBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        filterLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(filterLayout);

        predictionsTable = new QTableWidget(predictionsGroup);
        if (predictionsTable->columnCount() < 7)
            predictionsTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        predictionsTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        predictionsTable->setObjectName("predictionsTable");
        predictionsTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"  background-color: white;\n"
"  alternate-background-color: rgb(240, 250, 254);\n"
"  selection-background-color: rgb(17, 60, 103);\n"
"  selection-color: white;\n"
"}\n"
"QHeaderView::section {\n"
"  background-color: rgb(17, 60, 103);\n"
"  color: white;\n"
"  padding: 4px;\n"
"  font-size: 10pt;\n"
"  border: 1px solid #6c6c6c;\n"
"}"));
        predictionsTable->setAlternatingRowColors(true);
        predictionsTable->setSelectionMode(QAbstractItemView::SingleSelection);
        predictionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_3->addWidget(predictionsTable);


        verticalLayout_2->addWidget(predictionsGroup);

        mainTabWidget->addTab(predictionsTab, QString());
        maintenanceTab = new QWidget();
        maintenanceTab->setObjectName("maintenanceTab");
        verticalLayout_4 = new QVBoxLayout(maintenanceTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        selectedEquipmentGroup = new QGroupBox(maintenanceTab);
        selectedEquipmentGroup->setObjectName("selectedEquipmentGroup");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Segoe UI")});
        font8.setPointSize(15);
        font8.setBold(true);
        font8.setItalic(true);
        selectedEquipmentGroup->setFont(font8);
        horizontalLayout_2 = new QHBoxLayout(selectedEquipmentGroup);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        selectedEquipmentLayout = new QFormLayout();
        selectedEquipmentLayout->setObjectName("selectedEquipmentLayout");
        selectedIdLabel = new QLabel(selectedEquipmentGroup);
        selectedIdLabel->setObjectName("selectedIdLabel");
        selectedIdLabel->setFont(font7);
        selectedIdLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        selectedEquipmentLayout->setWidget(0, QFormLayout::LabelRole, selectedIdLabel);

        selectedIdValue = new QLabel(selectedEquipmentGroup);
        selectedIdValue->setObjectName("selectedIdValue");

        selectedEquipmentLayout->setWidget(0, QFormLayout::FieldRole, selectedIdValue);

        selectedNameLabel = new QLabel(selectedEquipmentGroup);
        selectedNameLabel->setObjectName("selectedNameLabel");
        selectedNameLabel->setFont(font7);
        selectedNameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        selectedEquipmentLayout->setWidget(1, QFormLayout::LabelRole, selectedNameLabel);

        selectedNameValue = new QLabel(selectedEquipmentGroup);
        selectedNameValue->setObjectName("selectedNameValue");

        selectedEquipmentLayout->setWidget(1, QFormLayout::FieldRole, selectedNameValue);

        selectedTypeLabel = new QLabel(selectedEquipmentGroup);
        selectedTypeLabel->setObjectName("selectedTypeLabel");
        selectedTypeLabel->setFont(font7);
        selectedTypeLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        selectedEquipmentLayout->setWidget(2, QFormLayout::LabelRole, selectedTypeLabel);

        selectedTypeValue = new QLabel(selectedEquipmentGroup);
        selectedTypeValue->setObjectName("selectedTypeValue");

        selectedEquipmentLayout->setWidget(2, QFormLayout::FieldRole, selectedTypeValue);


        horizontalLayout_2->addLayout(selectedEquipmentLayout);

        selectedStatusLayout = new QFormLayout();
        selectedStatusLayout->setObjectName("selectedStatusLayout");
        selectedStatusLabel = new QLabel(selectedEquipmentGroup);
        selectedStatusLabel->setObjectName("selectedStatusLabel");
        selectedStatusLabel->setFont(font7);
        selectedStatusLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        selectedStatusLayout->setWidget(0, QFormLayout::LabelRole, selectedStatusLabel);

        selectedStatusValue = new QLabel(selectedEquipmentGroup);
        selectedStatusValue->setObjectName("selectedStatusValue");

        selectedStatusLayout->setWidget(0, QFormLayout::FieldRole, selectedStatusValue);

        predFailureLabel = new QLabel(selectedEquipmentGroup);
        predFailureLabel->setObjectName("predFailureLabel");
        predFailureLabel->setFont(font7);
        predFailureLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        selectedStatusLayout->setWidget(1, QFormLayout::LabelRole, predFailureLabel);

        predFailureValue = new QLabel(selectedEquipmentGroup);
        predFailureValue->setObjectName("predFailureValue");

        selectedStatusLayout->setWidget(1, QFormLayout::FieldRole, predFailureValue);


        horizontalLayout_2->addLayout(selectedStatusLayout);


        verticalLayout_4->addWidget(selectedEquipmentGroup);

        maintenanceDetailsGroup = new QGroupBox(maintenanceTab);
        maintenanceDetailsGroup->setObjectName("maintenanceDetailsGroup");
        maintenanceDetailsGroup->setFont(font8);
        maintenanceLayout = new QFormLayout(maintenanceDetailsGroup);
        maintenanceLayout->setObjectName("maintenanceLayout");
        maintCostLabel = new QLabel(maintenanceDetailsGroup);
        maintCostLabel->setObjectName("maintCostLabel");
        maintCostLabel->setFont(font7);
        maintCostLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        maintenanceLayout->setWidget(0, QFormLayout::LabelRole, maintCostLabel);

        maintenanceCostEdit = new QLineEdit(maintenanceDetailsGroup);
        maintenanceCostEdit->setObjectName("maintenanceCostEdit");
        maintenanceCostEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        maintenanceLayout->setWidget(0, QFormLayout::FieldRole, maintenanceCostEdit);

        maintDetailsLabel = new QLabel(maintenanceDetailsGroup);
        maintDetailsLabel->setObjectName("maintDetailsLabel");
        maintDetailsLabel->setFont(font7);
        maintDetailsLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));
        maintDetailsLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        maintenanceLayout->setWidget(1, QFormLayout::LabelRole, maintDetailsLabel);

        maintenanceDetailsEdit = new QTextEdit(maintenanceDetailsGroup);
        maintenanceDetailsEdit->setObjectName("maintenanceDetailsEdit");
        maintenanceDetailsEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        maintenanceLayout->setWidget(1, QFormLayout::FieldRole, maintenanceDetailsEdit);

        recordMaintenanceBtn = new QPushButton(maintenanceDetailsGroup);
        recordMaintenanceBtn->setObjectName("recordMaintenanceBtn");
        recordMaintenanceBtn->setMinimumSize(QSize(0, 40));
        recordMaintenanceBtn->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        maintenanceLayout->setWidget(2, QFormLayout::FieldRole, recordMaintenanceBtn);


        verticalLayout_4->addWidget(maintenanceDetailsGroup);

        mainTabWidget->addTab(maintenanceTab, QString());
        historyTab = new QWidget();
        historyTab->setObjectName("historyTab");
        verticalLayout_5 = new QVBoxLayout(historyTab);
        verticalLayout_5->setObjectName("verticalLayout_5");
        historyGroup = new QGroupBox(historyTab);
        historyGroup->setObjectName("historyGroup");
        historyGroup->setFont(font8);
        verticalLayout_6 = new QVBoxLayout(historyGroup);
        verticalLayout_6->setObjectName("verticalLayout_6");
        historyFilterLayout = new QHBoxLayout();
        historyFilterLayout->setObjectName("historyFilterLayout");
        historyFilterLabel = new QLabel(historyGroup);
        historyFilterLabel->setObjectName("historyFilterLabel");
        historyFilterLabel->setFont(font7);
        historyFilterLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        historyFilterLayout->addWidget(historyFilterLabel);

        equipmentFilterCombo = new QComboBox(historyGroup);
        equipmentFilterCombo->addItem(QString());
        equipmentFilterCombo->setObjectName("equipmentFilterCombo");
        equipmentFilterCombo->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        historyFilterLayout->addWidget(equipmentFilterCombo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        historyFilterLayout->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(historyFilterLayout);

        historyTable = new QTableWidget(historyGroup);
        if (historyTable->columnCount() < 7)
            historyTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        historyTable->setObjectName("historyTable");
        historyTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"  background-color: white;\n"
"  alternate-background-color: rgb(240, 250, 254);\n"
"  selection-background-color: rgb(17, 60, 103);\n"
"  selection-color: white;\n"
"}\n"
"QHeaderView::section {\n"
"  background-color: rgb(17, 60, 103);\n"
"  color: white;\n"
"  padding: 4px;\n"
"  font-size: 10pt;\n"
"  border: 1px solid #6c6c6c;\n"
"}"));
        historyTable->setAlternatingRowColors(true);
        historyTable->setSelectionMode(QAbstractItemView::SingleSelection);
        historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_6->addWidget(historyTable);


        verticalLayout_5->addWidget(historyGroup);

        mainTabWidget->addTab(historyTab, QString());

        horizontalLayout->addWidget(mainTabWidget);


        verticalLayout->addWidget(contentWidget);

        footerWidget = new QWidget(PredictiveMaintenanceDialog);
        footerWidget->setObjectName("footerWidget");
        footerWidget->setMinimumSize(QSize(0, 50));
        footerWidget->setMaximumSize(QSize(16777215, 50));
        footerWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);"));
        footerLabel = new QLabel(footerWidget);
        footerLabel->setObjectName("footerLabel");
        footerLabel->setGeometry(QRect(0, 0, 1200, 50));
        footerLabel->setFont(font4);
        footerLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        footerLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(footerWidget);


        retranslateUi(PredictiveMaintenanceDialog);

        mainTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PredictiveMaintenanceDialog);
    } // setupUi

    void retranslateUi(QDialog *PredictiveMaintenanceDialog)
    {
        PredictiveMaintenanceDialog->setWindowTitle(QCoreApplication::translate("PredictiveMaintenanceDialog", "Predictive Maintenance", nullptr));
        headerTitle->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Predictive Maintenance", nullptr));
        sidebarTitle->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Maintenance Hub", nullptr));
        summaryTitle->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Equipment Status", nullptr));
        totalLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Total: 0", nullptr));
        functionalLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Functional: 0", nullptr));
        damagedLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Damaged: 0", nullptr));
        atRiskLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "At Risk: 0", nullptr));
        generateOrdersBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Generate Orders", nullptr));
        runPredictionsBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Run Predictions", nullptr));
        viewMaintenanceHistoryBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "View Maintenance History", nullptr));
        closeBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Return to Equipment List", nullptr));
        predictionsGroup->setTitle(QCoreApplication::translate("PredictiveMaintenanceDialog", "Equipment Failure Predictions", nullptr));
        thresholdLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Show equipment likely to fail within:", nullptr));
        thresholdComboBox->setItemText(0, QCoreApplication::translate("PredictiveMaintenanceDialog", "7 days", nullptr));
        thresholdComboBox->setItemText(1, QCoreApplication::translate("PredictiveMaintenanceDialog", "14 days", nullptr));
        thresholdComboBox->setItemText(2, QCoreApplication::translate("PredictiveMaintenanceDialog", "30 days", nullptr));
        thresholdComboBox->setItemText(3, QCoreApplication::translate("PredictiveMaintenanceDialog", "60 days", nullptr));
        thresholdComboBox->setItemText(4, QCoreApplication::translate("PredictiveMaintenanceDialog", "90 days", nullptr));

        checkPredictionsBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Check Predictions", nullptr));
        QTableWidgetItem *___qtablewidgetitem = predictionsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = predictionsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = predictionsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = predictionsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = predictionsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Predicted Failure", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = predictionsTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Days Remaining", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = predictionsTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Risk Level", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(predictionsTab), QCoreApplication::translate("PredictiveMaintenanceDialog", "Failure Predictions", nullptr));
        selectedEquipmentGroup->setTitle(QCoreApplication::translate("PredictiveMaintenanceDialog", "Selected Equipment", nullptr));
        selectedIdLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "ID:", nullptr));
        selectedIdValue->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "(None selected)", nullptr));
        selectedNameLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Name:", nullptr));
        selectedNameValue->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "(None selected)", nullptr));
        selectedTypeLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Type:", nullptr));
        selectedTypeValue->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "(None selected)", nullptr));
        selectedStatusLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Status:", nullptr));
        selectedStatusValue->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "(None selected)", nullptr));
        predFailureLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Predicted Failure:", nullptr));
        predFailureValue->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "(None selected)", nullptr));
        maintenanceDetailsGroup->setTitle(QCoreApplication::translate("PredictiveMaintenanceDialog", "Maintenance Details", nullptr));
        maintCostLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Maintenance Cost:", nullptr));
        maintenanceCostEdit->setPlaceholderText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Enter cost (numbers only)", nullptr));
        maintDetailsLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Details:", nullptr));
        maintenanceDetailsEdit->setPlaceholderText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Enter details of maintenance performed (repairs, replaced parts, etc.)", nullptr));
        recordMaintenanceBtn->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Record Maintenance", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(maintenanceTab), QCoreApplication::translate("PredictiveMaintenanceDialog", "Record Maintenance", nullptr));
        historyGroup->setTitle(QCoreApplication::translate("PredictiveMaintenanceDialog", "Equipment Maintenance History", nullptr));
        historyFilterLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Filter by Equipment:", nullptr));
        equipmentFilterCombo->setItemText(0, QCoreApplication::translate("PredictiveMaintenanceDialog", "All Equipment", nullptr));

        QTableWidgetItem *___qtablewidgetitem7 = historyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = historyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Equipment", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = historyTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = historyTable->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Old Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = historyTable->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "New Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = historyTable->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Cost", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = historyTable->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "Details", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(historyTab), QCoreApplication::translate("PredictiveMaintenanceDialog", "Maintenance History", nullptr));
        footerLabel->setText(QCoreApplication::translate("PredictiveMaintenanceDialog", "\302\251 2023 Equipment Maintenance System - Predictive Maintenance Module", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PredictiveMaintenanceDialog: public Ui_PredictiveMaintenanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREDICTIVEMAINTENANCEDIALOG_H
