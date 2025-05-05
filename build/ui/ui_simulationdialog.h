/********************************************************************************
** Form generated from reading UI file 'simulationdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONDIALOG_H
#define UI_SIMULATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QHBoxLayout *mainLayout;
    QGroupBox *parametersGroupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *regionGroupBox;
    QFormLayout *formLayout;
    QLabel *regionNameLabel;
    QLineEdit *regionNameEdit;
    QLabel *populationLabel;
    QSpinBox *populationSpinBox;
    QLabel *densityLabel;
    QHBoxLayout *horizontalLayout_2;
    QSlider *populationDensitySlider;
    QLabel *densityValueLabel;
    QGroupBox *diseaseGroupBox;
    QFormLayout *formLayout_2;
    QLabel *r0Label;
    QHBoxLayout *horizontalLayout_3;
    QSlider *r0Slider;
    QLabel *r0ValueLabel;
    QLabel *incubationLabel;
    QSpinBox *incubationDaysSpinBox;
    QLabel *infectiousLabel;
    QSpinBox *infectiousPeriodSpinBox;
    QLabel *mortalityLabel;
    QDoubleSpinBox *mortalityRateSpinBox;
    QGroupBox *interventionsGroupBox;
    QFormLayout *formLayout_3;
    QLabel *socialDistLabel;
    QHBoxLayout *horizontalLayout_4;
    QSlider *socialDistancingSlider;
    QLabel *socialDistValueLabel;
    QLabel *vaccinationLabel;
    QDoubleSpinBox *vaccinationRateSpinBox;
    QLabel *vaccineStartLabel;
    QSpinBox *vaccineStartDaySpinBox;
    QGroupBox *simulationGroupBox;
    QFormLayout *formLayout_4;
    QLabel *initialInfectedLabel;
    QSpinBox *initialInfectedSpinBox;
    QLabel *daysToSimulateLabel;
    QSpinBox *daysToSimulateSpinBox;
    QHBoxLayout *buttonLayout;
    QPushButton *runSimulationButton;
    QPushButton *aiEnhanceButton;
    QWidget *resultsWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *chartGroupBox;
    QVBoxLayout *verticalLayout_4;
    QWidget *chartPlaceholder;
    QLabel *bslRecommendationLabel;
    QGroupBox *summaryGroupBox;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *summaryTextEdit;
    QHBoxLayout *resultButtonsLayout;
    QPushButton *saveResultsButton;
    QPushButton *applyRecommendationButton;
    QLabel *statusLabel;
    QGroupBox *aiInsightsGroupBox;
    QVBoxLayout *verticalLayout_6;
    QTextEdit *aiInsightsTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;

    void setupUi(QDialog *SimulationDialog)
    {
        if (SimulationDialog->objectName().isEmpty())
            SimulationDialog->setObjectName("SimulationDialog");
        SimulationDialog->resize(1387, 778);
        SimulationDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        verticalLayout = new QVBoxLayout(SimulationDialog);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(SimulationDialog);
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
        parametersGroupBox = new QGroupBox(SimulationDialog);
        parametersGroupBox->setObjectName("parametersGroupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parametersGroupBox->sizePolicy().hasHeightForWidth());
        parametersGroupBox->setSizePolicy(sizePolicy);
        parametersGroupBox->setMinimumSize(QSize(300, 0));
        parametersGroupBox->setMaximumSize(QSize(350, 16777215));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        parametersGroupBox->setFont(font1);
        parametersGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_2 = new QVBoxLayout(parametersGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        regionGroupBox = new QGroupBox(parametersGroupBox);
        regionGroupBox->setObjectName("regionGroupBox");
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        regionGroupBox->setFont(font2);
        regionGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        formLayout = new QFormLayout(regionGroupBox);
        formLayout->setObjectName("formLayout");
        regionNameLabel = new QLabel(regionGroupBox);
        regionNameLabel->setObjectName("regionNameLabel");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Perpetua")});
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(true);
        regionNameLabel->setFont(font3);
        regionNameLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, regionNameLabel);

        regionNameEdit = new QLineEdit(regionGroupBox);
        regionNameEdit->setObjectName("regionNameEdit");
        regionNameEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, regionNameEdit);

        populationLabel = new QLabel(regionGroupBox);
        populationLabel->setObjectName("populationLabel");
        populationLabel->setFont(font3);
        populationLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, populationLabel);

        populationSpinBox = new QSpinBox(regionGroupBox);
        populationSpinBox->setObjectName("populationSpinBox");
        populationSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        populationSpinBox->setMinimum(1000);
        populationSpinBox->setMaximum(100000000);
        populationSpinBox->setSingleStep(10000);
        populationSpinBox->setValue(1000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, populationSpinBox);

        densityLabel = new QLabel(regionGroupBox);
        densityLabel->setObjectName("densityLabel");
        densityLabel->setFont(font3);
        densityLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, densityLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        populationDensitySlider = new QSlider(regionGroupBox);
        populationDensitySlider->setObjectName("populationDensitySlider");
        populationDensitySlider->setMinimum(1);
        populationDensitySlider->setMaximum(100);
        populationDensitySlider->setValue(50);
        populationDensitySlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(populationDensitySlider);

        densityValueLabel = new QLabel(regionGroupBox);
        densityValueLabel->setObjectName("densityValueLabel");
        densityValueLabel->setMinimumSize(QSize(40, 0));
        densityValueLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        horizontalLayout_2->addWidget(densityValueLabel);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);


        verticalLayout_2->addWidget(regionGroupBox);

        diseaseGroupBox = new QGroupBox(parametersGroupBox);
        diseaseGroupBox->setObjectName("diseaseGroupBox");
        diseaseGroupBox->setFont(font2);
        diseaseGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        formLayout_2 = new QFormLayout(diseaseGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        r0Label = new QLabel(diseaseGroupBox);
        r0Label->setObjectName("r0Label");
        r0Label->setFont(font3);
        r0Label->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, r0Label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        r0Slider = new QSlider(diseaseGroupBox);
        r0Slider->setObjectName("r0Slider");
        r0Slider->setMinimum(10);
        r0Slider->setMaximum(80);
        r0Slider->setValue(30);
        r0Slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(r0Slider);

        r0ValueLabel = new QLabel(diseaseGroupBox);
        r0ValueLabel->setObjectName("r0ValueLabel");
        r0ValueLabel->setMinimumSize(QSize(40, 0));
        r0ValueLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        horizontalLayout_3->addWidget(r0ValueLabel);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_3);

        incubationLabel = new QLabel(diseaseGroupBox);
        incubationLabel->setObjectName("incubationLabel");
        incubationLabel->setFont(font3);
        incubationLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, incubationLabel);

        incubationDaysSpinBox = new QSpinBox(diseaseGroupBox);
        incubationDaysSpinBox->setObjectName("incubationDaysSpinBox");
        incubationDaysSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        incubationDaysSpinBox->setMinimum(1);
        incubationDaysSpinBox->setMaximum(30);
        incubationDaysSpinBox->setValue(5);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, incubationDaysSpinBox);

        infectiousLabel = new QLabel(diseaseGroupBox);
        infectiousLabel->setObjectName("infectiousLabel");
        infectiousLabel->setFont(font3);
        infectiousLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, infectiousLabel);

        infectiousPeriodSpinBox = new QSpinBox(diseaseGroupBox);
        infectiousPeriodSpinBox->setObjectName("infectiousPeriodSpinBox");
        infectiousPeriodSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        infectiousPeriodSpinBox->setMinimum(1);
        infectiousPeriodSpinBox->setMaximum(30);
        infectiousPeriodSpinBox->setValue(10);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, infectiousPeriodSpinBox);

        mortalityLabel = new QLabel(diseaseGroupBox);
        mortalityLabel->setObjectName("mortalityLabel");
        mortalityLabel->setFont(font3);
        mortalityLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, mortalityLabel);

        mortalityRateSpinBox = new QDoubleSpinBox(diseaseGroupBox);
        mortalityRateSpinBox->setObjectName("mortalityRateSpinBox");
        mortalityRateSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        mortalityRateSpinBox->setMaximum(50.000000000000000);
        mortalityRateSpinBox->setValue(2.500000000000000);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, mortalityRateSpinBox);


        verticalLayout_2->addWidget(diseaseGroupBox);

        interventionsGroupBox = new QGroupBox(parametersGroupBox);
        interventionsGroupBox->setObjectName("interventionsGroupBox");
        interventionsGroupBox->setFont(font2);
        interventionsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        formLayout_3 = new QFormLayout(interventionsGroupBox);
        formLayout_3->setObjectName("formLayout_3");
        socialDistLabel = new QLabel(interventionsGroupBox);
        socialDistLabel->setObjectName("socialDistLabel");
        socialDistLabel->setFont(font3);
        socialDistLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, socialDistLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        socialDistancingSlider = new QSlider(interventionsGroupBox);
        socialDistancingSlider->setObjectName("socialDistancingSlider");
        socialDistancingSlider->setMaximum(90);
        socialDistancingSlider->setValue(30);
        socialDistancingSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_4->addWidget(socialDistancingSlider);

        socialDistValueLabel = new QLabel(interventionsGroupBox);
        socialDistValueLabel->setObjectName("socialDistValueLabel");
        socialDistValueLabel->setMinimumSize(QSize(40, 0));
        socialDistValueLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        horizontalLayout_4->addWidget(socialDistValueLabel);


        formLayout_3->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        vaccinationLabel = new QLabel(interventionsGroupBox);
        vaccinationLabel->setObjectName("vaccinationLabel");
        vaccinationLabel->setFont(font3);
        vaccinationLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, vaccinationLabel);

        vaccinationRateSpinBox = new QDoubleSpinBox(interventionsGroupBox);
        vaccinationRateSpinBox->setObjectName("vaccinationRateSpinBox");
        vaccinationRateSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        vaccinationRateSpinBox->setDecimals(2);
        vaccinationRateSpinBox->setMaximum(5.000000000000000);
        vaccinationRateSpinBox->setValue(0.500000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, vaccinationRateSpinBox);

        vaccineStartLabel = new QLabel(interventionsGroupBox);
        vaccineStartLabel->setObjectName("vaccineStartLabel");
        vaccineStartLabel->setFont(font3);
        vaccineStartLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, vaccineStartLabel);

        vaccineStartDaySpinBox = new QSpinBox(interventionsGroupBox);
        vaccineStartDaySpinBox->setObjectName("vaccineStartDaySpinBox");
        vaccineStartDaySpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        vaccineStartDaySpinBox->setMinimum(1);
        vaccineStartDaySpinBox->setMaximum(365);
        vaccineStartDaySpinBox->setValue(30);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, vaccineStartDaySpinBox);


        verticalLayout_2->addWidget(interventionsGroupBox);

        simulationGroupBox = new QGroupBox(parametersGroupBox);
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
        initialInfectedLabel = new QLabel(simulationGroupBox);
        initialInfectedLabel->setObjectName("initialInfectedLabel");
        initialInfectedLabel->setFont(font3);
        initialInfectedLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, initialInfectedLabel);

        initialInfectedSpinBox = new QSpinBox(simulationGroupBox);
        initialInfectedSpinBox->setObjectName("initialInfectedSpinBox");
        initialInfectedSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        initialInfectedSpinBox->setMinimum(1);
        initialInfectedSpinBox->setMaximum(10000);
        initialInfectedSpinBox->setValue(10);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, initialInfectedSpinBox);

        daysToSimulateLabel = new QLabel(simulationGroupBox);
        daysToSimulateLabel->setObjectName("daysToSimulateLabel");
        daysToSimulateLabel->setFont(font3);
        daysToSimulateLabel->setStyleSheet(QString::fromUtf8("color:#030C54;"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, daysToSimulateLabel);

        daysToSimulateSpinBox = new QSpinBox(simulationGroupBox);
        daysToSimulateSpinBox->setObjectName("daysToSimulateSpinBox");
        daysToSimulateSpinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;"));
        daysToSimulateSpinBox->setMinimum(30);
        daysToSimulateSpinBox->setMaximum(1000);
        daysToSimulateSpinBox->setValue(180);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, daysToSimulateSpinBox);


        verticalLayout_2->addWidget(simulationGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        runSimulationButton = new QPushButton(parametersGroupBox);
        runSimulationButton->setObjectName("runSimulationButton");
        runSimulationButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        buttonLayout->addWidget(runSimulationButton);

        aiEnhanceButton = new QPushButton(parametersGroupBox);
        aiEnhanceButton->setObjectName("aiEnhanceButton");
        aiEnhanceButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        buttonLayout->addWidget(aiEnhanceButton);


        verticalLayout_2->addLayout(buttonLayout);


        mainLayout->addWidget(parametersGroupBox);

        resultsWidget = new QWidget(SimulationDialog);
        resultsWidget->setObjectName("resultsWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(resultsWidget->sizePolicy().hasHeightForWidth());
        resultsWidget->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(resultsWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        chartGroupBox = new QGroupBox(resultsWidget);
        chartGroupBox->setObjectName("chartGroupBox");
        chartGroupBox->setFont(font1);
        chartGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_4 = new QVBoxLayout(chartGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        chartPlaceholder = new QWidget(chartGroupBox);
        chartPlaceholder->setObjectName("chartPlaceholder");
        chartPlaceholder->setMinimumSize(QSize(0, 250));
        chartPlaceholder->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));

        verticalLayout_4->addWidget(chartPlaceholder);


        verticalLayout_3->addWidget(chartGroupBox);

        bslRecommendationLabel = new QLabel(resultsWidget);
        bslRecommendationLabel->setObjectName("bslRecommendationLabel");
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setItalic(true);
        bslRecommendationLabel->setFont(font4);
        bslRecommendationLabel->setStyleSheet(QString::fromUtf8("color: rgb(17, 60, 103);"));
        bslRecommendationLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(bslRecommendationLabel);

        summaryGroupBox = new QGroupBox(resultsWidget);
        summaryGroupBox->setObjectName("summaryGroupBox");
        summaryGroupBox->setFont(font1);
        summaryGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_5 = new QVBoxLayout(summaryGroupBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        summaryTextEdit = new QTextEdit(summaryGroupBox);
        summaryTextEdit->setObjectName("summaryTextEdit");
        summaryTextEdit->setEnabled(true);
        summaryTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #030C54;\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        summaryTextEdit->setReadOnly(true);

        verticalLayout_5->addWidget(summaryTextEdit);


        verticalLayout_3->addWidget(summaryGroupBox);

        resultButtonsLayout = new QHBoxLayout();
        resultButtonsLayout->setObjectName("resultButtonsLayout");
        saveResultsButton = new QPushButton(resultsWidget);
        saveResultsButton->setObjectName("saveResultsButton");
        saveResultsButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        resultButtonsLayout->addWidget(saveResultsButton);

        applyRecommendationButton = new QPushButton(resultsWidget);
        applyRecommendationButton->setObjectName("applyRecommendationButton");
        applyRecommendationButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        resultButtonsLayout->addWidget(applyRecommendationButton);


        verticalLayout_3->addLayout(resultButtonsLayout);

        statusLabel = new QLabel(resultsWidget);
        statusLabel->setObjectName("statusLabel");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Perpetua")});
        font5.setPointSize(9);
        font5.setItalic(true);
        statusLabel->setFont(font5);
        statusLabel->setStyleSheet(QString::fromUtf8("color: #030C54;"));

        verticalLayout_3->addWidget(statusLabel);


        mainLayout->addWidget(resultsWidget);

        aiInsightsGroupBox = new QGroupBox(SimulationDialog);
        aiInsightsGroupBox->setObjectName("aiInsightsGroupBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(4);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(aiInsightsGroupBox->sizePolicy().hasHeightForWidth());
        aiInsightsGroupBox->setSizePolicy(sizePolicy2);
        aiInsightsGroupBox->setMinimumSize(QSize(300, 0));
        aiInsightsGroupBox->setFont(font1);
        aiInsightsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_6 = new QVBoxLayout(aiInsightsGroupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        aiInsightsTextEdit = new QTextEdit(aiInsightsGroupBox);
        aiInsightsTextEdit->setObjectName("aiInsightsTextEdit");
        aiInsightsTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"         color: #030C54;\n"
"         border:1px solid black;\n"
"         border-radius:10px;"));
        aiInsightsTextEdit->setReadOnly(true);

        verticalLayout_6->addWidget(aiInsightsTextEdit);


        mainLayout->addWidget(aiInsightsGroupBox);


        verticalLayout->addLayout(mainLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(SimulationDialog);
        closeButton->setObjectName("closeButton");
        closeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"         border-radius:20px;\n"
"         background-color:#030C54;\n"
"         color:white"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SimulationDialog);

        QMetaObject::connectSlotsByName(SimulationDialog);
    } // setupUi

    void retranslateUi(QDialog *SimulationDialog)
    {
        SimulationDialog->setWindowTitle(QCoreApplication::translate("SimulationDialog", "Disease Spread Simulation", nullptr));
        headerLabel->setText(QCoreApplication::translate("SimulationDialog", "Disease Spread Simulation", nullptr));
        parametersGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Simulation Parameters", nullptr));
        regionGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Region Information", nullptr));
        regionNameLabel->setText(QCoreApplication::translate("SimulationDialog", "Region Name:", nullptr));
        regionNameEdit->setText(QCoreApplication::translate("SimulationDialog", "Sample Region", nullptr));
        populationLabel->setText(QCoreApplication::translate("SimulationDialog", "Population:", nullptr));
        densityLabel->setText(QCoreApplication::translate("SimulationDialog", "Population Density:", nullptr));
        densityValueLabel->setText(QCoreApplication::translate("SimulationDialog", "50%", nullptr));
        diseaseGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Disease Parameters", nullptr));
        r0Label->setText(QCoreApplication::translate("SimulationDialog", "Basic Reproduction Number (R0):", nullptr));
        r0ValueLabel->setText(QCoreApplication::translate("SimulationDialog", "3.0", nullptr));
        incubationLabel->setText(QCoreApplication::translate("SimulationDialog", "Incubation Period (days):", nullptr));
        infectiousLabel->setText(QCoreApplication::translate("SimulationDialog", "Infectious Period (days):", nullptr));
        mortalityLabel->setText(QCoreApplication::translate("SimulationDialog", "Mortality Rate (%):", nullptr));
        interventionsGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Interventions", nullptr));
        socialDistLabel->setText(QCoreApplication::translate("SimulationDialog", "Social Distancing Effectiveness:", nullptr));
        socialDistValueLabel->setText(QCoreApplication::translate("SimulationDialog", "30%", nullptr));
        vaccinationLabel->setText(QCoreApplication::translate("SimulationDialog", "Vaccination Rate (% per day):", nullptr));
        vaccineStartLabel->setText(QCoreApplication::translate("SimulationDialog", "Vaccination Start Day:", nullptr));
        simulationGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Simulation Settings", nullptr));
        initialInfectedLabel->setText(QCoreApplication::translate("SimulationDialog", "Initial Infected Cases:", nullptr));
        daysToSimulateLabel->setText(QCoreApplication::translate("SimulationDialog", "Days to Simulate:", nullptr));
        runSimulationButton->setText(QCoreApplication::translate("SimulationDialog", "Run Simulation", nullptr));
        aiEnhanceButton->setText(QCoreApplication::translate("SimulationDialog", "Enhance with AI", nullptr));
        chartGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Simulation Results", nullptr));
        bslRecommendationLabel->setText(QCoreApplication::translate("SimulationDialog", "BSL Recommendation: --", nullptr));
        summaryGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "Analysis Summary", nullptr));
        summaryTextEdit->setPlaceholderText(QCoreApplication::translate("SimulationDialog", "Run a simulation to see results...", nullptr));
        saveResultsButton->setText(QCoreApplication::translate("SimulationDialog", "Export PDF Report", nullptr));
        applyRecommendationButton->setText(QCoreApplication::translate("SimulationDialog", "Apply BSL Recommendation", nullptr));
        statusLabel->setText(QString());
        aiInsightsGroupBox->setTitle(QCoreApplication::translate("SimulationDialog", "AI Insights", nullptr));
        aiInsightsTextEdit->setPlaceholderText(QCoreApplication::translate("SimulationDialog", "Click \"Enhance with AI\" to get AI-powered insights...", nullptr));
        closeButton->setText(QCoreApplication::translate("SimulationDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationDialog: public Ui_SimulationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONDIALOG_H
