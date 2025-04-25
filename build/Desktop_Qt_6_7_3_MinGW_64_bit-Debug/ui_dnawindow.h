/********************************************************************************
** Form generated from reading UI file 'dnawindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DNAWINDOW_H
#define UI_DNAWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DnaWindow
{
public:
    QAction *actionImportPatientData;
    QAction *actionImportViralData;
    QAction *actionExportResults;
    QAction *actionQuit;
    QAction *actionRunSimulation;
    QAction *actionAnalyzeResponse;
    QAction *actionClearData;
    QAction *actionAbout;
    QAction *actionDocumentation;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QHBoxLayout *mainLayout;
    QGroupBox *inputGroupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *patientGroupBox;
    QFormLayout *formLayout;
    QLabel *bloodTypeLabel;
    QComboBox *bloodTypeComboBox;
    QLabel *ageLabel;
    QSpinBox *ageSpinBox;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QGroupBox *geneticGroupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *patientInfoTextEdit;
    QPushButton *importPatientDataButton;
    QGroupBox *viralGroupBox;
    QFormLayout *formLayout_2;
    QLabel *virusTypeLabel;
    QComboBox *virusTypeComboBox;
    QLabel *viralLoadLabel;
    QSlider *viralLoadSlider;
    QPushButton *importViralDataButton;
    QGroupBox *simulationGroupBox;
    QFormLayout *formLayout_4;
    QLabel *simulationDepthLabel;
    QSpinBox *simulationDepthSpinBox;
    QLabel *parametersLabel;
    QHBoxLayout *horizontalLayout;
    QSlider *parametersSlider;
    QLabel *parameterValueLabel;
    QHBoxLayout *buttonLayout;
    QPushButton *runSimulationButton;
    QPushButton *clearDataButton;
    QWidget *resultsWidget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *resultsGroupBox;
    QVBoxLayout *verticalLayout_5;
    QWidget *chartsWidget;
    QGridLayout *chartsLayout;
    QLabel *responseTypeLabel;
    QGroupBox *analysisGroupBox;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *resultsTextEdit;
    QHBoxLayout *resultButtonsLayout;
    QPushButton *analyzeResponseButton;
    QPushButton *exportResultsButton;
    QProgressBar *simulationProgressBar;
    QGroupBox *recommendationsGroupBox;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *recommendationsTextEdit;
    QGroupBox *immuneResponseGroupBox;
    QVBoxLayout *verticalLayout_8;
    QWidget *immuneChartWidget;
    QHBoxLayout *footerLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *statusLabel;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAnalysis;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DnaWindow)
    {
        if (DnaWindow->objectName().isEmpty())
            DnaWindow->setObjectName("DnaWindow");
        DnaWindow->resize(1387, 828);
        DnaWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        actionImportPatientData = new QAction(DnaWindow);
        actionImportPatientData->setObjectName("actionImportPatientData");
        actionImportViralData = new QAction(DnaWindow);
        actionImportViralData->setObjectName("actionImportViralData");
        actionExportResults = new QAction(DnaWindow);
        actionExportResults->setObjectName("actionExportResults");
        actionQuit = new QAction(DnaWindow);
        actionQuit->setObjectName("actionQuit");
        actionRunSimulation = new QAction(DnaWindow);
        actionRunSimulation->setObjectName("actionRunSimulation");
        actionAnalyzeResponse = new QAction(DnaWindow);
        actionAnalyzeResponse->setObjectName("actionAnalyzeResponse");
        actionClearData = new QAction(DnaWindow);
        actionClearData->setObjectName("actionClearData");
        actionAbout = new QAction(DnaWindow);
        actionAbout->setObjectName("actionAbout");
        actionDocumentation = new QAction(DnaWindow);
        actionDocumentation->setObjectName("actionDocumentation");
        centralwidget = new QWidget(DnaWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(centralwidget);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setMinimumSize(QSize(0, 80));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        headerLabel->setFont(font);
        headerLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(headerLabel);

        mainLayout = new QHBoxLayout();
        mainLayout->setObjectName("mainLayout");
        inputGroupBox = new QGroupBox(centralwidget);
        inputGroupBox->setObjectName("inputGroupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputGroupBox->sizePolicy().hasHeightForWidth());
        inputGroupBox->setSizePolicy(sizePolicy);
        inputGroupBox->setMinimumSize(QSize(300, 0));
        inputGroupBox->setMaximumSize(QSize(350, 16777215));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        inputGroupBox->setFont(font1);
        inputGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(inputGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        patientGroupBox = new QGroupBox(inputGroupBox);
        patientGroupBox->setObjectName("patientGroupBox");
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        patientGroupBox->setFont(font2);
        patientGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        formLayout = new QFormLayout(patientGroupBox);
        formLayout->setObjectName("formLayout");
        bloodTypeLabel = new QLabel(patientGroupBox);
        bloodTypeLabel->setObjectName("bloodTypeLabel");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Perpetua")});
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(true);
        bloodTypeLabel->setFont(font3);
        bloodTypeLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, bloodTypeLabel);

        bloodTypeComboBox = new QComboBox(patientGroupBox);
        bloodTypeComboBox->setObjectName("bloodTypeComboBox");
        bloodTypeComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, bloodTypeComboBox);

        ageLabel = new QLabel(patientGroupBox);
        ageLabel->setObjectName("ageLabel");
        ageLabel->setFont(font3);
        ageLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, ageLabel);

        ageSpinBox = new QSpinBox(patientGroupBox);
        ageSpinBox->setObjectName("ageSpinBox");
        ageSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        ageSpinBox->setMinimum(1);
        ageSpinBox->setMaximum(120);
        ageSpinBox->setValue(35);

        formLayout->setWidget(1, QFormLayout::FieldRole, ageSpinBox);

        genderLabel = new QLabel(patientGroupBox);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setFont(font3);
        genderLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(patientGroupBox);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName("genderComboBox");
        genderComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));

        formLayout->setWidget(2, QFormLayout::FieldRole, genderComboBox);


        verticalLayout_2->addWidget(patientGroupBox);

        geneticGroupBox = new QGroupBox(inputGroupBox);
        geneticGroupBox->setObjectName("geneticGroupBox");
        geneticGroupBox->setFont(font2);
        geneticGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(geneticGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        patientInfoTextEdit = new QTextEdit(geneticGroupBox);
        patientInfoTextEdit->setObjectName("patientInfoTextEdit");
        patientInfoTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        patientInfoTextEdit->setReadOnly(true);

        verticalLayout_3->addWidget(patientInfoTextEdit);

        importPatientDataButton = new QPushButton(geneticGroupBox);
        importPatientDataButton->setObjectName("importPatientDataButton");
        importPatientDataButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        verticalLayout_3->addWidget(importPatientDataButton);


        verticalLayout_2->addWidget(geneticGroupBox);

        viralGroupBox = new QGroupBox(inputGroupBox);
        viralGroupBox->setObjectName("viralGroupBox");
        viralGroupBox->setFont(font2);
        viralGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        formLayout_2 = new QFormLayout(viralGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        virusTypeLabel = new QLabel(viralGroupBox);
        virusTypeLabel->setObjectName("virusTypeLabel");
        virusTypeLabel->setFont(font3);
        virusTypeLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, virusTypeLabel);

        virusTypeComboBox = new QComboBox(viralGroupBox);
        virusTypeComboBox->setObjectName("virusTypeComboBox");
        virusTypeComboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, virusTypeComboBox);

        viralLoadLabel = new QLabel(viralGroupBox);
        viralLoadLabel->setObjectName("viralLoadLabel");
        viralLoadLabel->setFont(font3);
        viralLoadLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, viralLoadLabel);

        viralLoadSlider = new QSlider(viralGroupBox);
        viralLoadSlider->setObjectName("viralLoadSlider");
        viralLoadSlider->setStyleSheet(QString::fromUtf8("color: #030C54;"));
        viralLoadSlider->setMinimum(1);
        viralLoadSlider->setMaximum(100);
        viralLoadSlider->setValue(50);
        viralLoadSlider->setOrientation(Qt::Orientation::Horizontal);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, viralLoadSlider);

        importViralDataButton = new QPushButton(viralGroupBox);
        importViralDataButton->setObjectName("importViralDataButton");
        importViralDataButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, importViralDataButton);


        verticalLayout_2->addWidget(viralGroupBox);

        simulationGroupBox = new QGroupBox(inputGroupBox);
        simulationGroupBox->setObjectName("simulationGroupBox");
        simulationGroupBox->setFont(font2);
        simulationGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        formLayout_4 = new QFormLayout(simulationGroupBox);
        formLayout_4->setObjectName("formLayout_4");
        simulationDepthLabel = new QLabel(simulationGroupBox);
        simulationDepthLabel->setObjectName("simulationDepthLabel");
        simulationDepthLabel->setFont(font3);
        simulationDepthLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, simulationDepthLabel);

        simulationDepthSpinBox = new QSpinBox(simulationGroupBox);
        simulationDepthSpinBox->setObjectName("simulationDepthSpinBox");
        simulationDepthSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        simulationDepthSpinBox->setMinimum(1);
        simulationDepthSpinBox->setMaximum(100);
        simulationDepthSpinBox->setValue(30);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, simulationDepthSpinBox);

        parametersLabel = new QLabel(simulationGroupBox);
        parametersLabel->setObjectName("parametersLabel");
        parametersLabel->setFont(font3);
        parametersLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, parametersLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        parametersSlider = new QSlider(simulationGroupBox);
        parametersSlider->setObjectName("parametersSlider");
        parametersSlider->setValue(50);
        parametersSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(parametersSlider);

        parameterValueLabel = new QLabel(simulationGroupBox);
        parameterValueLabel->setObjectName("parameterValueLabel");
        parameterValueLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        horizontalLayout->addWidget(parameterValueLabel);


        formLayout_4->setLayout(1, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout_2->addWidget(simulationGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        runSimulationButton = new QPushButton(inputGroupBox);
        runSimulationButton->setObjectName("runSimulationButton");
        runSimulationButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        buttonLayout->addWidget(runSimulationButton);

        clearDataButton = new QPushButton(inputGroupBox);
        clearDataButton->setObjectName("clearDataButton");
        clearDataButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        buttonLayout->addWidget(clearDataButton);


        verticalLayout_2->addLayout(buttonLayout);


        mainLayout->addWidget(inputGroupBox);

        resultsWidget = new QWidget(centralwidget);
        resultsWidget->setObjectName("resultsWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(resultsWidget->sizePolicy().hasHeightForWidth());
        resultsWidget->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(resultsWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        resultsGroupBox = new QGroupBox(resultsWidget);
        resultsGroupBox->setObjectName("resultsGroupBox");
        resultsGroupBox->setFont(font1);
        resultsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(resultsGroupBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        chartsWidget = new QWidget(resultsGroupBox);
        chartsWidget->setObjectName("chartsWidget");
        chartsWidget->setMinimumSize(QSize(0, 300));
        chartsWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        chartsLayout = new QGridLayout(chartsWidget);
        chartsLayout->setObjectName("chartsLayout");

        verticalLayout_5->addWidget(chartsWidget);


        verticalLayout_4->addWidget(resultsGroupBox);

        responseTypeLabel = new QLabel(resultsWidget);
        responseTypeLabel->setObjectName("responseTypeLabel");
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setItalic(true);
        responseTypeLabel->setFont(font4);
        responseTypeLabel->setStyleSheet(QString::fromUtf8("color: rgb(17, 60, 103);"));
        responseTypeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(responseTypeLabel);

        analysisGroupBox = new QGroupBox(resultsWidget);
        analysisGroupBox->setObjectName("analysisGroupBox");
        analysisGroupBox->setFont(font1);
        analysisGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(analysisGroupBox);
        verticalLayout_7->setObjectName("verticalLayout_7");
        resultsTextEdit = new QTextEdit(analysisGroupBox);
        resultsTextEdit->setObjectName("resultsTextEdit");
        resultsTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        resultsTextEdit->setReadOnly(true);

        verticalLayout_7->addWidget(resultsTextEdit);


        verticalLayout_4->addWidget(analysisGroupBox);

        resultButtonsLayout = new QHBoxLayout();
        resultButtonsLayout->setObjectName("resultButtonsLayout");
        analyzeResponseButton = new QPushButton(resultsWidget);
        analyzeResponseButton->setObjectName("analyzeResponseButton");
        analyzeResponseButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        resultButtonsLayout->addWidget(analyzeResponseButton);

        exportResultsButton = new QPushButton(resultsWidget);
        exportResultsButton->setObjectName("exportResultsButton");
        exportResultsButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        resultButtonsLayout->addWidget(exportResultsButton);


        verticalLayout_4->addLayout(resultButtonsLayout);

        simulationProgressBar = new QProgressBar(resultsWidget);
        simulationProgressBar->setObjectName("simulationProgressBar");
        simulationProgressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 1px solid black;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"    background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: rgb(17, 60, 103);\n"
"}"));
        simulationProgressBar->setValue(0);

        verticalLayout_4->addWidget(simulationProgressBar);


        mainLayout->addWidget(resultsWidget);

        recommendationsGroupBox = new QGroupBox(centralwidget);
        recommendationsGroupBox->setObjectName("recommendationsGroupBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(4);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(recommendationsGroupBox->sizePolicy().hasHeightForWidth());
        recommendationsGroupBox->setSizePolicy(sizePolicy2);
        recommendationsGroupBox->setMinimumSize(QSize(300, 0));
        recommendationsGroupBox->setFont(font1);
        recommendationsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(recommendationsGroupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        recommendationsTextEdit = new QTextEdit(recommendationsGroupBox);
        recommendationsTextEdit->setObjectName("recommendationsTextEdit");
        recommendationsTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        recommendationsTextEdit->setReadOnly(true);

        verticalLayout_6->addWidget(recommendationsTextEdit);

        immuneResponseGroupBox = new QGroupBox(recommendationsGroupBox);
        immuneResponseGroupBox->setObjectName("immuneResponseGroupBox");
        immuneResponseGroupBox->setFont(font2);
        immuneResponseGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid black;\n"
"    border-radius: 10px;\n"
"    margin-top: 20px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: rgb(243, 249, 251);\n"
"    color: #030C54;\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(immuneResponseGroupBox);
        verticalLayout_8->setObjectName("verticalLayout_8");
        immuneChartWidget = new QWidget(immuneResponseGroupBox);
        immuneChartWidget->setObjectName("immuneChartWidget");
        immuneChartWidget->setMinimumSize(QSize(0, 200));
        immuneChartWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));

        verticalLayout_8->addWidget(immuneChartWidget);


        verticalLayout_6->addWidget(immuneResponseGroupBox);


        mainLayout->addWidget(recommendationsGroupBox);


        verticalLayout->addLayout(mainLayout);

        footerLayout = new QHBoxLayout();
        footerLayout->setObjectName("footerLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        footerLayout->addItem(horizontalSpacer);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setStyleSheet(QString::fromUtf8("color: #030C54;"));

        footerLayout->addWidget(statusLabel);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");
        exitButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        footerLayout->addWidget(exitButton);


        verticalLayout->addLayout(footerLayout);

        DnaWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DnaWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1387, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuAnalysis = new QMenu(menubar);
        menuAnalysis->setObjectName("menuAnalysis");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        DnaWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DnaWindow);
        statusbar->setObjectName("statusbar");
        DnaWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAnalysis->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionImportPatientData);
        menuFile->addAction(actionImportViralData);
        menuFile->addSeparator();
        menuFile->addAction(actionExportResults);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAnalysis->addAction(actionRunSimulation);
        menuAnalysis->addAction(actionAnalyzeResponse);
        menuAnalysis->addSeparator();
        menuAnalysis->addAction(actionClearData);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionDocumentation);

        retranslateUi(DnaWindow);

        QMetaObject::connectSlotsByName(DnaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DnaWindow)
    {
        DnaWindow->setWindowTitle(QCoreApplication::translate("DnaWindow", "Viral Response DNA Analyzer", nullptr));
        actionImportPatientData->setText(QCoreApplication::translate("DnaWindow", "Import Patient Data...", nullptr));
        actionImportViralData->setText(QCoreApplication::translate("DnaWindow", "Import Viral Data...", nullptr));
        actionExportResults->setText(QCoreApplication::translate("DnaWindow", "Export Results...", nullptr));
        actionQuit->setText(QCoreApplication::translate("DnaWindow", "Quit", nullptr));
        actionRunSimulation->setText(QCoreApplication::translate("DnaWindow", "Run Simulation", nullptr));
        actionAnalyzeResponse->setText(QCoreApplication::translate("DnaWindow", "Analyze Response", nullptr));
        actionClearData->setText(QCoreApplication::translate("DnaWindow", "Clear Data", nullptr));
        actionAbout->setText(QCoreApplication::translate("DnaWindow", "About", nullptr));
        actionDocumentation->setText(QCoreApplication::translate("DnaWindow", "Documentation", nullptr));
        headerLabel->setText(QCoreApplication::translate("DnaWindow", "Viral Response DNA Analyzer", nullptr));
        inputGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Patient Parameters", nullptr));
        patientGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Patient Information", nullptr));
        bloodTypeLabel->setText(QCoreApplication::translate("DnaWindow", "Blood Type:", nullptr));
        ageLabel->setText(QCoreApplication::translate("DnaWindow", "Age:", nullptr));
        genderLabel->setText(QCoreApplication::translate("DnaWindow", "Gender:", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("DnaWindow", "Male", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("DnaWindow", "Female", nullptr));
        genderComboBox->setItemText(2, QCoreApplication::translate("DnaWindow", "Other", nullptr));

        geneticGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Genetic Parameters", nullptr));
        importPatientDataButton->setText(QCoreApplication::translate("DnaWindow", "Import Patient Data", nullptr));
        viralGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Viral Parameters", nullptr));
        virusTypeLabel->setText(QCoreApplication::translate("DnaWindow", "Virus Type:", nullptr));
        viralLoadLabel->setText(QCoreApplication::translate("DnaWindow", "Initial Viral Load:", nullptr));
        importViralDataButton->setText(QCoreApplication::translate("DnaWindow", "Import Viral Data", nullptr));
        simulationGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Simulation Settings", nullptr));
        simulationDepthLabel->setText(QCoreApplication::translate("DnaWindow", "Simulation Depth (Days):", nullptr));
        parametersLabel->setText(QCoreApplication::translate("DnaWindow", "Parameter Intensity:", nullptr));
        parameterValueLabel->setText(QCoreApplication::translate("DnaWindow", "50%", nullptr));
        runSimulationButton->setText(QCoreApplication::translate("DnaWindow", "Run Simulation", nullptr));
        clearDataButton->setText(QCoreApplication::translate("DnaWindow", "Clear Data", nullptr));
        resultsGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Simulation Results", nullptr));
        responseTypeLabel->setText(QCoreApplication::translate("DnaWindow", "Viral Response Type: --", nullptr));
        analysisGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Analysis Results", nullptr));
        resultsTextEdit->setPlaceholderText(QCoreApplication::translate("DnaWindow", "Run a simulation to see results...", nullptr));
        analyzeResponseButton->setText(QCoreApplication::translate("DnaWindow", "Analyze Response", nullptr));
        exportResultsButton->setText(QCoreApplication::translate("DnaWindow", "Export Results", nullptr));
        recommendationsGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Recommendations", nullptr));
        recommendationsTextEdit->setPlaceholderText(QCoreApplication::translate("DnaWindow", "Click \"Analyze Response\" to get personalized recommendations...", nullptr));
        immuneResponseGroupBox->setTitle(QCoreApplication::translate("DnaWindow", "Immune Response Profile", nullptr));
        statusLabel->setText(QCoreApplication::translate("DnaWindow", "Ready to analyze viral responses", nullptr));
        exitButton->setText(QCoreApplication::translate("DnaWindow", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("DnaWindow", "File", nullptr));
        menuAnalysis->setTitle(QCoreApplication::translate("DnaWindow", "Analysis", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("DnaWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DnaWindow: public Ui_DnaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DNAWINDOW_H
