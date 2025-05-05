#include "SimulationDialog.h"
#include "mainwindow.h"
#include "ui_SimulationDialog.h"
#include "DiseaseSpreadModel.h"
#include "AIAssistantWindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QVBoxLayout>

SimulationDialog::SimulationDialog(MainWindow* mainWin, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SimulationDialog),
    model(nullptr),
    chartView(nullptr),
    mainWindow(mainWin)
{
    ui->setupUi(this);

    model = new DiseaseSpreadModel(this);

    setupChart();

    connect(ui->populationDensitySlider, &QSlider::valueChanged, this, &SimulationDialog::on_populationDensitySlider_valueChanged);
    connect(ui->r0Slider, &QSlider::valueChanged, this, &SimulationDialog::on_r0Slider_valueChanged);
    connect(ui->socialDistancingSlider, &QSlider::valueChanged, this, &SimulationDialog::on_socialDistancingSlider_valueChanged);

    on_populationDensitySlider_valueChanged(ui->populationDensitySlider->value());
    on_r0Slider_valueChanged(ui->r0Slider->value());
    on_socialDistancingSlider_valueChanged(ui->socialDistancingSlider->value());

    enableResultControls(false);

    ui->aiInsightsGroupBox->setVisible(false);
}

SimulationDialog::~SimulationDialog()
{
    delete ui;
}

void SimulationDialog::setupChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Disease Spread Simulation");
    chart->legend()->setVisible(true);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chartPlaceholder);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
}

void SimulationDialog::updateChart()
{
    if (!model) return;

    QVector<double> susceptible = model->getSusceptibleCurve();
    QVector<double> infected = model->getInfectedCurve();
    QVector<double> recovered = model->getRecoveredCurve();
    QVector<double> deaths = model->getDeathsCurve();

    QLineSeries *susceptibleSeries = new QLineSeries();
    QLineSeries *infectedSeries = new QLineSeries();
    QLineSeries *recoveredSeries = new QLineSeries();
    QLineSeries *deathsSeries = new QLineSeries();

    susceptibleSeries->setName("Susceptible");
    infectedSeries->setName("Infected");
    recoveredSeries->setName("Recovered");
    deathsSeries->setName("Deaths");

    for (int i = 0; i < susceptible.size(); i++) {
        susceptibleSeries->append(i, susceptible[i]);
        if (i < infected.size()) infectedSeries->append(i, infected[i]);
        if (i < recovered.size()) recoveredSeries->append(i, recovered[i]);
        if (i < deaths.size()) deathsSeries->append(i, deaths[i]);
    }

    QChart *chart = new QChart();
    chart->setTitle("Disease Spread Simulation");
    chart->addSeries(susceptibleSeries);
    chart->addSeries(infectedSeries);
    chart->addSeries(recoveredSeries);
    chart->addSeries(deathsSeries);

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Days");
    chart->axes(Qt::Vertical).first()->setTitleText("Population");

    chartView->setChart(chart);
    chartView->update();
}

void SimulationDialog::updateSummary()
{
    if (!model) return;

    QString bslLevel = model->recommendedBSLLevel();
    if (bslLevel.isEmpty()) bslLevel = "Not determined";


    ui->bslRecommendationLabel->setText("BSL Recommendation: " + bslLevel);


    QString summary = "Region: " + ui->regionNameEdit->text() + "\n\n";
    summary += "Population: " + QString::number(ui->populationSpinBox->value()) + "\n\n";
    summary += "R0 Value: " + QString::number(ui->r0Slider->value() / 10.0, 'f', 1) + "\n\n";
    summary += "Mortality Rate: " + QString::number(ui->mortalityRateSpinBox->value()) + "%\n\n";


    if (!model->getInfectedCurve().isEmpty()) {
        QString modelSummary = model->getAnalysisSummary();
        if (!modelSummary.isEmpty()) {
            summary = modelSummary;
        }
    }
    ui->summaryTextEdit->clear();
    ui->summaryTextEdit->setStyleSheet("color: #030C54; background-color: white;");
    ui->summaryTextEdit->setPlainText(summary);
    ui->summaryTextEdit->update();
}

void SimulationDialog::enableResultControls(bool enable)
{
    ui->saveResultsButton->setEnabled(enable);
    ui->applyRecommendationButton->setEnabled(enable);
    ui->aiEnhanceButton->setEnabled(enable);
}

void SimulationDialog::on_runSimulationButton_clicked()
{
    model->setRegion(
        ui->regionNameEdit->text(),
        ui->populationSpinBox->value(),
        ui->populationDensitySlider->value()
        );

    model->setDiseaseParameters(
        ui->r0Slider->value() / 10.0,
        ui->incubationDaysSpinBox->value(),
        ui->infectiousPeriodSpinBox->value(),
        ui->mortalityRateSpinBox->value()
        );

    model->setInitialConditions(
        ui->initialInfectedSpinBox->value()
        );

    model->setInterventionMeasures(
        ui->socialDistancingSlider->value() / 100.0,
        ui->vaccinationRateSpinBox->value(),
        ui->vaccineStartDaySpinBox->value()
        );

    bool success = model->runSimulation(ui->daysToSimulateSpinBox->value());

    if (success) {
        updateChart();
        updateSummary();
        enableResultControls(true);
    } else {
        QMessageBox::warning(this, "Simulation Error", "Failed to run simulation. Please check parameters.");
    }
}

void SimulationDialog::on_saveResultsButton_clicked()
{
    if (!model) return;

    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    int pageWidth = pdfWriter.width();
    int pageHeight = pdfWriter.height();

    QFont titleFont("Arial", 40, QFont::Bold);
    painter.setFont(titleFont);
    QRect titleRect(0, 100, pageWidth, 170);
    painter.drawText(titleRect, Qt::AlignCenter, "Disease Simulation Report");

    QPixmap logo(":/new/prefix1/image/Adobe Express - file (5)");
    if (!logo.isNull()) {
        int logoWidth = 650;
        int logoHeight = 550;
        int logoX = pageWidth - logoWidth - 50;
        int logoY = 50;
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }


    QFont headerFont("Arial", 24, QFont::Bold);
    QFont contentFont("Arial", 18);
    int yPosition = pageHeight / 5;
    int rowHeight = 300;
    int padding = 100;

    QStringList headers = {"Region", "Population", "R0 Value", "Mortality Rate"};
    QStringList data = {
        ui->regionNameEdit->text(),
        QString::number(ui->populationSpinBox->value()),
        QString::number(ui->r0Slider->value() / 10.0, 'f', 1),
        QString::number(ui->mortalityRateSpinBox->value()) + "%"
    };

    for (int i = 0; i < headers.size(); ++i) {
        painter.setFont(headerFont);
        QRect headerRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(headerRect, Qt::AlignLeft, headers[i] + ":");
        yPosition += rowHeight / 2;

        painter.setFont(contentFont);
        QRect dataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
        painter.drawText(dataRect, Qt::AlignLeft, data[i]);
        yPosition += rowHeight / 2;
        yPosition += 50;
    }

    painter.setFont(headerFont);
    QRect bslRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
    painter.drawText(bslRect, Qt::AlignLeft, "BSL Recommendation:");
    yPosition += rowHeight / 2;

    painter.setFont(contentFont);
    QRect bslDataRect(padding, yPosition, pageWidth - 2 * padding, rowHeight / 2);
    painter.drawText(bslDataRect, Qt::AlignLeft, model->recommendedBSLLevel());
    yPosition += rowHeight / 2;

    pdfWriter.newPage();
    yPosition = 200;

    QPixmap chartImage = chartView->grab();
    if (!chartImage.isNull()) {
        int imgWidth = pageWidth - 2 * padding;
        int imgHeight = imgWidth * chartImage.height() / chartImage.width();
        painter.drawPixmap(padding, yPosition, imgWidth, imgHeight, chartImage);
        yPosition += imgHeight + 100;
    }

    QFont descFont("Arial", 16);
    painter.setFont(descFont);
    QString summary = model->getAnalysisSummary();
    QRect summaryRect(padding, yPosition, pageWidth - 2 * padding, pageHeight - yPosition - 100);
    painter.drawText(summaryRect, Qt::AlignLeft | Qt::TextWordWrap, summary);

    painter.end();
}

void SimulationDialog::on_populationDensitySlider_valueChanged(int value)
{
    ui->densityValueLabel->setText(QString::number(value) + "%");
}

void SimulationDialog::on_r0Slider_valueChanged(int value)
{
    double r0 = value / 10.0;
    ui->r0ValueLabel->setText(QString::number(r0, 'f', 1));
}

void SimulationDialog::on_socialDistancingSlider_valueChanged(int value)
{
    ui->socialDistValueLabel->setText(QString::number(value) + "%");
}

void SimulationDialog::on_applyRecommendationButton_clicked()
{
    if (!model) return;

    QString bsl = model->recommendedBSLLevel();
    accept();
}

void SimulationDialog::on_aiEnhanceButton_clicked()
{
    if (!model) {
        QMessageBox::warning(this, "No Simulation Data", "Please run a simulation first.");
        return;
    }
    AIAssistantWindow* aiWindow = mainWindow->getAIInstance();
    QString prompt = "Please analyze this disease simulation and provide insights:\n\n";
    prompt += "SIMULATION PARAMETERS:\n";
    prompt += QString("- Region: %1\n").arg(ui->regionNameEdit->text());
    prompt += QString("- Population: %1\n").arg(ui->populationSpinBox->value());
    prompt += QString("- Population Density: %1%\n").arg(ui->populationDensitySlider->value());
    prompt += QString("- R0 Value: %1\n").arg(ui->r0Slider->value() / 10.0, 0, 'f', 1);
    prompt += QString("- Incubation Period: %1 days\n").arg(ui->incubationDaysSpinBox->value());
    prompt += QString("- Infectious Period: %1 days\n").arg(ui->infectiousPeriodSpinBox->value());
    prompt += QString("- Mortality Rate: %1%\n").arg(ui->mortalityRateSpinBox->value());
    prompt += QString("- Initial Infected Cases: %1\n").arg(ui->initialInfectedSpinBox->value());
    prompt += QString("- Social Distancing Effectiveness: %1%\n").arg(ui->socialDistancingSlider->value());
    prompt += QString("- Vaccination Rate: %1% per day\n").arg(ui->vaccinationRateSpinBox->value());
    prompt += QString("- Vaccination Start Day: %1\n\n").arg(ui->vaccineStartDaySpinBox->value());

    if (!model->getInfectedCurve().isEmpty()) {
        prompt += "SIMULATION RESULTS:\n";
        prompt += QString("- Peak Day: %1\n").arg(model->getDaysToPeak());
        prompt += QString("- Peak Infections: %1 cases (%2% of population)\n")
                      .arg(int(model->getInfectedCurve()[model->getDaysToPeak()]))
                      .arg((model->getInfectedCurve()[model->getDaysToPeak()] / ui->populationSpinBox->value()) * 100.0, 0, 'f', 2);
        prompt += QString("- Total Infections: %1 (%2% of population)\n")
                      .arg(int(model->getTotalInfections()))
                      .arg((model->getTotalInfections() / ui->populationSpinBox->value()) * 100.0, 0, 'f', 2);
        prompt += QString("- Recommended BSL Level: %1\n\n").arg(model->recommendedBSLLevel());
    }

    prompt += "ANALYSIS REQUESTS:\n";
    prompt += "1. Based on these parameters and results, please provide insights on containment strategies that would be effective for this type of disease.\n";
    prompt += "2. Explain why the recommended biosafety level classification is appropriate for this disease scenario.\n";
    prompt += "3. Discuss the potential societal impact of this disease if it were to spread in the real world.\n";
    prompt += "4. Suggest additional research directions or precautions that should be considered.\n";
    prompt += "5. Compare this disease to any known historical outbreaks with similar characteristics.\n\n";
    prompt += "Please provide a comprehensive but concise analysis that would be helpful for research planning and biosafety protocols.";

    QApplication::setOverrideCursor(Qt::WaitCursor);

    try {
        aiWindow->setResearchContext(
            ui->regionNameEdit->text() + " Simulation",
            model->recommendedBSLLevel().isEmpty() ? "BSL-2" : model->recommendedBSLLevel(),
            prompt,
            QDate::currentDate().toString("yyyy-MM-dd"),
            QDate::currentDate().addDays(90).toString("yyyy-MM-dd")
            );

        QApplication::restoreOverrideCursor();
        if (aiWindow->exec() == QDialog::Accepted) {
            QString aiInsights = aiWindow->getGeneratedDescription();
            if (!aiInsights.isEmpty()) {
                ui->aiInsightsTextEdit->clear();
                ui->aiInsightsTextEdit->setStyleSheet("color: #030C54; background-color: white;");
                ui->aiInsightsTextEdit->setPlainText(aiInsights);
                ui->aiInsightsTextEdit->update();
                ui->aiInsightsGroupBox->setVisible(true);

                ui->statusLabel->setText("AI insights generated successfully");
                ui->statusLabel->setStyleSheet("color: green;");
            } else {
                ui->statusLabel->setText("No insights were generated");
                ui->statusLabel->setStyleSheet("color: #030C54;");
            }
        } else {
            ui->statusLabel->setText("AI analysis cancelled");
            ui->statusLabel->setStyleSheet("color: #030C54;");
        }
    } catch (const std::exception& e) {
        QApplication::restoreOverrideCursor();
        QMessageBox::warning(this, "Error", QString("An error occurred: %1").arg(e.what()));
        ui->statusLabel->setText("Error getting AI insights");
        ui->statusLabel->setStyleSheet("color: red;");
    }

    QApplication::restoreOverrideCursor();
}

void SimulationDialog::on_closeButton_clicked()
{
    reject();
}

QString SimulationDialog::getRecommendedBSL() const
{
    if (!model) return "";
    return model->recommendedBSLLevel();
}

QString SimulationDialog::getSimulationSummary() const
{
    if (!model) return "";
    return model->getAnalysisSummary();
}
