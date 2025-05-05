#include "dnawindowp.h"
#include "ui_dnawindowp.h"
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QPrinter>
#include <QPainter>
#include <QPixmap>
#include <QPageSize>
#include <QPageLayout>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>

DnaWindow::DnaWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DnaWindow)
    , m_viralLoadChart(new QChart())
    , m_viralLoadChartView(new QChartView(m_viralLoadChart))
    , m_immuneResponseChart(new QChart())
    , m_immuneResponseChartView(new QChartView(m_immuneResponseChart))
{
    ui->setupUi(this);
    // Initialize necessary widgets if not already in UI
    if (!ui->genderComboBox) {
        ui->genderComboBox = new QComboBox(this);
        ui->genderComboBox->addItems({"Male", "Female", "Other"});
        // Add to layout as needed
    }

    if (!ui->ageSpinBox) {
        ui->ageSpinBox = new QSpinBox(this);
        ui->ageSpinBox->setRange(0, 120);
        // Add to layout as needed
    }

    setupCharts();
    setupConnections();
    loadDefaultData();

    setWindowTitle("Viral Response DNA Analyzer");
    setMinimumSize(1024, 768);

    updatePatientDataDisplay();
    statusBar()->showMessage("Ready to analyze DNA and viral responses");
}

DnaWindow::~DnaWindow()
{
    delete m_viralLoadChartView;
    delete m_immuneResponseChartView;
    delete m_viralLoadChart;
    delete m_immuneResponseChart;
    delete ui;
}

void DnaWindow::setupCharts()
{
    m_viralLoadChart->setTitle("Viral Load Over Time");
    m_viralLoadChart->legend()->setVisible(true);
    m_viralLoadChart->legend()->setAlignment(Qt::AlignBottom);

    m_immuneResponseChart->setTitle("Immune Response Profile");
    m_immuneResponseChart->legend()->setVisible(true);
    m_immuneResponseChart->legend()->setAlignment(Qt::AlignBottom);

    m_viralLoadChartView->setRenderHint(QPainter::Antialiasing);
    m_immuneResponseChartView->setRenderHint(QPainter::Antialiasing);

    ui->chartsLayout->addWidget(m_viralLoadChartView, 0, 0);
    ui->chartsLayout->addWidget(m_immuneResponseChartView, 0, 1);
}

void DnaWindow::setupConnections()
{

    connect(ui->ageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &DnaWindow::onAgeChanged);
    connect(ui->genderComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DnaWindow::onGenderChanged);
    connect(ui->runSimulationButtonp, &QPushButton::clicked,
            this, &DnaWindow::on_runSimulationButtonp_clicked);

    connect(ui->simulationDepthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &DnaWindow::validateInputs);

    connect(&m_simulationEngine, &SimulationEngine::progressUpdated,
            ui->simulationProgressBar, &QProgressBar::setValue);

    connect(ui->bloodTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DnaWindow::on_bloodTypeComboBox_currentIndexChanged);

    connect(ui->virusTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DnaWindow::on_virusTypeComboBox_currentIndexChanged);

    connect(ui->parametersSlider, &QSlider::valueChanged,
            this, &DnaWindow::on_parametersSlider_valueChanged);

    connect(ui->simulationDepthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &DnaWindow::on_simulationDepthSpinBox_valueChanged);
    connect(ui->analyzeResponseButtonp, &QPushButton::clicked,
            this, &DnaWindow::on_analyzeResponseButtonp_clicked);

    connect(ui->importPatientDataButtonp, &QPushButton::clicked,
            this, &DnaWindow::on_importPatientDataButtonp_clicked);
    connect(ui->importViralDataButtonp, &QPushButton::clicked,
            this, &DnaWindow::on_importViralDataButtonp_clicked);

    connect(ui->virusTypeComboBox, &QComboBox::currentTextChanged,
            this, [this](){
                if (!m_simulationResults.isEmpty()) {
                    generateViralResponseChart();
                    generateImmuneResponseChart();
                }
            });
    connect(ui->exportPdfButtonp, &QPushButton::clicked, this, &DnaWindow::exportAnalysisToPdfp);
}


void DnaWindow::onAgeChanged(int age)
{
    m_patientData.setAge(age);
    updatePatientDataDisplay();
}

void DnaWindow::onGenderChanged(int index)
{
    if (index >= 0) {
        m_patientData.setGender(ui->genderComboBox->currentText());
        updatePatientDataDisplay();
    }
}

void DnaWindow::exportAnalysisToPdfp()
{
    if (m_simulationResults.isEmpty()) {
        QMessageBox::warning(this, "Error", "No analysis results available.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Results",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Analysis_Results.pdf",
        "PDF Files (*.pdf)"
        );
    if (fileName.isEmpty()) return;

    // Create a printer
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    // Create a document to print
    QTextDocument document;
    document.setDocumentMargin(10);

    // Create HTML content with CSS styling
    QString html = R"(
    <html>
    <head>
        <style>
            body {
                font-family: Arial, sans-serif;
                color: #333;
                line-height: 1.5;
                margin: 0;
                padding: 0;
            }
            .header {
                text-align: center;
                margin-bottom: 20px;
            }
            h1 {
                color: #2c3e50;
                font-size: 24px;
                margin: 10px 0;
                text-align: center;
                border-bottom: 2px solid #3498db;
                padding-bottom: 10px;
            }
            h2 {
                color: #3498db;
                font-size: 18px;
                margin-top: 25px;
                border-left: 4px solid #3498db;
                padding-left: 10px;
            }
            .section {
                margin: 15px 0;
                padding: 15px;
                background-color: #f8f9fa;
                border-radius: 5px;
            }
            .label {
                font-weight: bold;
                display: inline-block;
                width: 180px;
                color: #2c3e50;
            }
            .value {
                color: #333;
            }
            .footer {
                margin-top: 50px;
                font-size: 12px;
                color: #7f8c8d;
                text-align: center;
                border-top: 1px solid #ecf0f1;
                padding-top: 10px;
            }
            .response-type {
                font-weight: bold;
            }
            .response-severe {
                color: #e74c3c;
            }
            .response-moderate {
                color: #f39c12;
            }
            .response-mild {
                color: #2ecc71;
            }
        </style>
    </head>
    <body>
    )";

    // Add header (without logo)
    html += "<div class='header'>";
    html += "<h1>ANALYSIS RESULTS</h1>";
    html += "</div>";

    // Patient info section
    html += "<div class='section'>";
    html += "<h2>Patient Information</h2>";
    html += "<p><span class='label'>Age:</span><span class='value'>" + QString::number(m_patientData.getAge()) + "</span></p>";
    html += "<p><span class='label'>Gender:</span><span class='value'>" + m_patientData.getGender() + "</span></p>";
    html += "<p><span class='label'>Blood Type:</span><span class='value'>" + m_patientData.getBloodType() + "</span></p>";
    html += "</div>";

    // Determine response type class for styling
    QString responseClass = "response-mild";
    if (m_responseProfile.responseType.contains("Sévère")) {
        responseClass = "response-severe";
    } else if (m_responseProfile.responseType.contains("Modérée")) {
        responseClass = "response-moderate";
    }

    // Analysis results section
    html += "<div class='section'>";
    html += "<h2>Analysis Results</h2>";
    html += "<p><span class='label'>Virus Type:</span><span class='value'>" + ui->virusTypeComboBox->currentText() + "</span></p>";
    html += "<p><span class='label'>Response Type:</span><span class='value response-type " + responseClass + "'>" +
            m_responseProfile.responseType + "</span></p>";
    html += "<p><span class='label'>Peak Viral Load:</span><span class='value'>" +
            QString::number(m_responseProfile.peakViralLoad, 'f', 2) + " copies/mL</span></p>";
    html += "<p><span class='label'>Clearance Efficiency:</span><span class='value'>" +
            QString::number(m_responseProfile.clearanceEfficiency, 'f', 1) + "%</span></p>";
    html += "<p><span class='label'>Time to Peak:</span><span class='value'>" +
            QString::number(m_responseProfile.timeToPeak) + " days</span></p>";
    html += "<p><span class='label'>Immune Activation Score:</span><span class='value'>" +
            QString::number(m_responseProfile.immuneActivationScore, 'f', 2) + "</span></p>";
    html += "</div>";

    // Footer
    html += "<div class='footer'>";
    html += "Generated on: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    html += "</div>";

    html += "</body></html>";

    // Set the HTML content
    document.setHtml(html);

    // Print to PDF
    document.print(&printer);

    statusBar()->showMessage("Analysis results exported to PDF", 3000);

    // Optionally open the PDF
    if (QMessageBox::question(this, "PDF Created",
                              "Analysis results exported to PDF. Do you want to open it now?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
}

void DnaWindow::loadDefaultData()
{
    ui->bloodTypeComboBox->addItems({"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"});
    ui->virusTypeComboBox->addItems({"SARS-CoV-2", "Influenza A", "HIV", "Hepatitis C", "Epstein-Barr"});
    ui->genderComboBox->setCurrentText(m_patientData.getGender());
    ui->ageSpinBox->setValue(m_patientData.getAge());
    ui->simulationDepthSpinBox->setValue(10);
    ui->parametersSlider->setValue(50);

    m_patientData.setBloodType("O+");
    m_patientData.setAge(35);
    m_patientData.setGender("Male");

    QStringList defaultHLA = {"A*02:01", "B*07:02", "C*07:02", "DRB1*15:01"};
    m_patientData.setHLATypes(defaultHLA);

    QMap<QString, QString> defaultMarkers;
    defaultMarkers["ACE2"] = "Standard";
    defaultMarkers["TLR4"] = "Variant rs4986790";
    defaultMarkers["IFNL3"] = "C/C genotype";
    m_patientData.setGeneticMarkers(defaultMarkers);
}


bool DnaWindow::validateInputs()
{
    bool valid = !m_patientData.getBloodType().isEmpty() &&
                 ui->virusTypeComboBox->currentIndex() >= 0 &&
                 ui->simulationDepthSpinBox->value() > 0;

    ui->runSimulationButtonp->setEnabled(valid);
    return valid;
}

void DnaWindow::on_importPatientDataButtonp_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Import Simulation Results",
                                                    "",
                                                    "CSV Files (*.csv);;Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Import Error",
                             "Could not open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QVector<SimulationResult> importedResults;

    // Skip header line
    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        if (parts.size() >= 3) {
            SimulationResult result;
            result.viralLoad = parts[1].toDouble();
            result.immuneResponse = parts[2].toDouble();
            importedResults.append(result);
        }
    }

    file.close();

    if (!importedResults.isEmpty()) {
        m_simulationResults = importedResults;
        updateSimulationResults();
        generateViralResponseChart();
        generateImmuneResponseChart();
        statusBar()->showMessage("Results imported successfully", 3000);
    } else {
        QMessageBox::warning(this, "Import Error",
                             "No valid data found in the file.");
    }
}


void DnaWindow::on_runSimulationButtonp_clicked()
{
    if (!validateInputs()) {
        QMessageBox::warning(this, "Error", "Invalid inputs");
        return;
    }

    statusBar()->showMessage("Running simulation...");
    ui->simulationProgressBar->setValue(0);

    // Clear previous results
    m_simulationResults.clear();

    // Generate simulated data based on patient and virus type
    int days = ui->simulationDepthSpinBox->value();
    double param = ui->parametersSlider->value() / 100.0;

    // Simulate viral load and immune response
    for (int day = 0; day < days; ++day) {
        SimulationResult result;

        // Simple simulation model - adjust as needed
        double progress = static_cast<double>(day) / days;
        result.viralLoad = 10.0 * param * (1.0 - qAbs(progress - 0.5)) * 2.0;
        result.immuneResponse = 8.0 * param * progress * progress;

        m_simulationResults.append(result);

        // Update progress
        ui->simulationProgressBar->setValue(static_cast<int>((day + 1) * 100 / days));
        QCoreApplication::processEvents(); // Keep UI responsive

        // Clear previous results
        m_simulationResults.clear();
        m_simulationResults.resize(ui->simulationDepthSpinBox->value());

        // Generate new results
        generateViralResponseChart();  // Utilise maintenant le virus sélectionné
        generateImmuneResponseChart();

        // Update UI
        updateSimulationResults();
        statusBar()->showMessage("Simulation complete", 3000);
    }

    // Update charts and results display
    updateSimulationResults();
    generateViralResponseChart();
    generateImmuneResponseChart();
    calculateBasicMetrics();
    updateAnalysisResultsDisplay();

    statusBar()->showMessage("Simulation complete", 3000);
    ui->simulationProgressBar->setValue(100);
}





void DnaWindow::on_clearDataButton_clicked()
{
    // Reset all data
    m_patientData = PatientData();
    m_viralData = ViralData();
    m_simulationResults.clear();

    // Reset UI
    ui->patientInfoTextEdit->clear();
    ui->resultsTextEdit->clear();

    // Clear charts
    m_viralLoadChart->removeAllSeries();
    m_immuneResponseChart->removeAllSeries();

    // Reset progress
    ui->simulationProgressBar->setValue(0);

    // Reload default data for demo purposes
    loadDefaultData();
    updatePatientDataDisplay();

    statusBar()->showMessage("All data cleared", 3000);
}
void DnaWindow::on_actionImportPatientData_triggered()
{
    QString filters = "DNA Files (*.dna *.fasta *.fastq);;"
                      "CSV Files (*.csv);;"
                      "All Files (*.*)";

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Import Patient Data",
                                                    QDir::homePath(),
                                                    filters);

    if (fileName.isEmpty()) {
        statusBar()->showMessage("Import cancelled", 3000);
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error",
                              "Could not open file:\n" + file.errorString());
        return;
    }

    try {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Process the imported data
        m_patientData.setFileName(QFileInfo(fileName).fileName());
        m_patientData.setImportDate(QDateTime::currentDateTime());

        // Extract genetic markers (simplified example)
        QMap<QString, QString> markers;
        if (content.contains("ACE2")) {
            markers["ACE2"] = "Standard"; // Replace with actual extraction
        }
        if (content.contains("TLR4")) {
            markers["TLR4"] = "Variant"; // Replace with actual extraction
        }
        m_patientData.setGeneticMarkers(markers);

        // Update UI
        updatePatientDataDisplay();
        statusBar()->showMessage("Patient data imported successfully", 3000);

    } catch (...) {
        QMessageBox::critical(this, "Error",
                              "An error occurred while processing the file");
    }
}



void DnaWindow::on_importViralDataButtonp_clicked()
{
    QString filters = "Viral Data Files (*.vir *.fasta);;"
                      "CSV Files (*.csv);;"
                      "All Files (*.*)";

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Import Viral Data",
                                                    QDir::homePath(),
                                                    filters);

    if (fileName.isEmpty()) {
        statusBar()->showMessage("Viral data import cancelled", 3000);
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error",
                              "Could not open viral data file:\n" + file.errorString());
        return;
    }

    try {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Process the imported viral data
        m_viralData.setFileName(QFileInfo(fileName).fileName());
        m_viralData.setImportDate(QDateTime::currentDateTime());

        // Detect virus type from content
        QString virusType = detectVirusType(content);
        m_viralData.setVirusType(virusType);

        // Update UI
        ui->virusTypeComboBox->setCurrentText(virusType);
        statusBar()->showMessage("Viral data imported successfully: " + virusType, 3000);

    } catch (...) {
        QMessageBox::critical(this, "Error",
                              "An error occurred while processing the viral data file");
    }
}

QString DnaWindow::detectVirusType(const QString& content)
{
    // Détection plus sophistiquée des types de virus
    if (content.contains("SARS-CoV-2") || content.contains("COVID") ||
        content.contains("coronavirus")) {
        return "SARS-CoV-2";
    }
    else if (content.contains("Influenza") || content.contains("grippe") ||
             content.contains("H1N1") || content.contains("H3N2")) {
        return "Influenza A";
    }
    else if (content.contains("HIV") || content.contains("VIH") ||
             content.contains("human immunodeficiency")) {
        return "HIV";
    }
    else if (content.contains("Hepatitis C") || content.contains("hépatite C") ||
             content.contains("HCV") || content.contains("VHC")) {
        return "Hepatitis C";
    }
    else if (content.contains("Epstein-Barr") || content.contains("EBV") ||
             content.contains("mononucleosis")) {
        return "Epstein-Barr";
    }

    return "Unknown Virus";
}

QString DnaWindow::extractGeneVariant(const QString& content, const QString& gene)
{
    // Implémentation simplifiée - à adapter selon votre format de fichier
    QRegularExpression re(gene + ":([A-Za-z0-9-/]+)");
    QRegularExpressionMatch match = re.match(content);
    return match.hasMatch() ? match.captured(1).trimmed() : "Variant standard";
}
void DnaWindow::updateViralLoadChart(const QVector<double>& viralLoadData)
{
    m_viralLoadChart->removeAllSeries();

    QLineSeries *series = new QLineSeries();
    series->setName("Viral Load");

    for (int i = 0; i < viralLoadData.size(); ++i) {
        series->append(i, viralLoadData[i]);
    }

    m_viralLoadChart->addSeries(series);
    m_viralLoadChart->createDefaultAxes();
    m_viralLoadChart->axisX()->setTitleText("Days");
    m_viralLoadChart->axisY()->setTitleText("Viral Load (copies/mL)");

    m_viralLoadChartView->setRenderHint(QPainter::Antialiasing);
}

void DnaWindow::updateImmuneResponseChart(const QVector<double>& immuneResponseData)
{
    m_immuneResponseChart->removeAllSeries();

    QLineSeries *series = new QLineSeries();
    series->setName("Immune Response");

    for (int i = 0; i < immuneResponseData.size(); ++i) {
        series->append(i, immuneResponseData[i]);
    }

    m_immuneResponseChart->addSeries(series);
    m_immuneResponseChart->createDefaultAxes();
    m_immuneResponseChart->axisX()->setTitleText("Days");
    m_immuneResponseChart->axisY()->setTitleText("Response Level");

    m_immuneResponseChartView->setRenderHint(QPainter::Antialiasing);
}


void DnaWindow::on_analyzeResponseButtonp_clicked()
{
    if (m_simulationResults.isEmpty()) {
        QMessageBox::warning(this, "Analysis Error",
                             "No simulation results available.\nPlease run a simulation first.");
        return;
    }

    // Calculate metrics
    calculateBasicMetrics();
    determineResponseType();
    m_responseProfile.recommendations = generateRecommendations(m_responseProfile.responseType);

    // Format the HTML report
    QString reportHtml = "<div style='font-family: Arial;'>";

    // Patient Information section
    reportHtml += "<h2 style='color: #2c3e50;'>Patient Analysis Report</h2>";
    reportHtml += "<h3 style='color: #3498db;'>Patient Information</h3>";
    reportHtml += "<p><b>Blood Type:</b> " + m_patientData.getBloodType() + "</p>";
    reportHtml += "<p><b>Age:</b> " + QString::number(m_patientData.getAge()) + "</p>";
    reportHtml += "<p><b>Gender:</b> " + m_patientData.getGender() + "</p>";

    // Analysis Results section
    reportHtml += "<h3 style='color: #3498db;'>Analysis Results</h3>";

    // Determine color based on response type
    QString responseColor = "#e74c3c"; // red for severe
    if (m_responseProfile.responseType.contains("Modérée")) responseColor = "#f39c12"; // orange
    if (m_responseProfile.responseType.contains("Légère")) responseColor = "#2ecc71"; // green

    reportHtml += "<p><b>Response Type:</b> <span style='color:" + responseColor + ";'>"
                  + m_responseProfile.responseType + "</span></p>";
    reportHtml += "<p><b>Peak Viral Load:</b> "
                  + QString::number(m_responseProfile.peakViralLoad, 'f', 2) + " copies/mL</p>";
    reportHtml += "<p><b>Clearance Efficiency:</b> "
                  + QString::number(m_responseProfile.clearanceEfficiency, 'f', 1) + "%</p>";

    // Medical Recommendations section
    reportHtml += "<h3 style='color: #3498db;'>Medical Recommendations</h3>";
    reportHtml += "<ul>";
    for (const QString &rec : m_responseProfile.recommendations) {
        reportHtml += "<li>" + rec + "</li>";
    }
    reportHtml += "</ul>";

    reportHtml += "</div>";

    // Update the UI directly
    ui->recommendationsTextEdit->setHtml(reportHtml);

    // Also update the immune response chart if needed
    generateImmuneResponseChart();
}


QStringList DnaWindow::generateRecommendations(const QString& responseType)
{
    QStringList recommendations;
    QString virusType = ui->virusTypeComboBox->currentText();
    QString bloodType = m_patientData.getBloodType();
    int age = m_patientData.getAge();
    QString gender = m_patientData.getGender();
    QMap<QString, QString> geneticMarkers = m_patientData.getGeneticMarkers();

    // 1. Recommandations générales basées sur la sévérité
    if (responseType.contains("Sévère")) {
        recommendations << "[Urgence] Hospitalisation immédiate requise";
        recommendations << "[Urgence] Surveillance continue : fréquence cardiaque, pression artérielle, saturation O2";
        recommendations << "[Médical] Thérapie antivirale intraveineuse à haut dosage";
        recommendations << "[Médical] Évaluation rapide par un spécialiste des maladies infectieuses";

        if (virusType == "SARS-CoV-2" || virusType == "Influenza A") {
            recommendations << "[Respiratoire] Préparation à une intubation si détérioration";
        }
    }
    else if (responseType.contains("Modérée")) {
        recommendations << "[Médical] Traitement antiviral oral selon protocole standard";
        recommendations << "[Surveillance] Consultation de suivi sous 48 heures";
        recommendations << "[Conseil] Repos strict et hydratation (2-3 L/jour)";
        recommendations << "[Surveillance] Journal des symptômes à partager avec le médecin";
    }
    else {
        recommendations << "[Conseil] Traitement symptomatique (paracétamol, hydratation)";
        recommendations << "[Conseil] Repos à domicile pendant 3-5 jours";
        recommendations << "[Surveillance] Reconsulter si fièvre > 48h ou aggravation";
    }

    // 2. Recommandations spécifiques au virus
    if (virusType == "HIV") {
        recommendations << "[Diagnostic] Test de confirmation Western Blot + PCR quantitative";
        recommendations << "[Biologie] Numération CD4/CD8 + charge virale HIV";

        if (!responseType.contains("Légère")) {
            recommendations << "[Traitement] Initiation d'une trithérapie antirétrovirale (ART)";
            recommendations << "[Génétique] Test de résistance aux antirétroviraux";
        }

        recommendations << "[Prévention] Dépistage des co-infections (hépatites, tuberculose)";
        recommendations << "[Education] Counseling sur la prévention de la transmission";
    }
    else if (virusType == "Hepatitis C") {
        recommendations << "[Diagnostic] PCR HCV + quantification virale";
        recommendations << "[Biologie] Bilan hépatique complet (transaminases, bilirubine, TP)";

        if (responseType.contains("Sévère") || responseType.contains("Modérée")) {
            recommendations << "[Traitement] Antiviraux à action directe (AAD) selon génotype";
            recommendations << "[Suivi] Fibroscan ou élastographie hépatique";
        }

        recommendations << "[Prévention] Vaccination contre l'hépatite A et B si non immunisé";
        recommendations << "[Conseil] Abstinence alcoolique stricte pendant le traitement";
    }
    else if (virusType == "Influenza A") {
        if (responseType.contains("Sévère") || responseType.contains("Modérée")) {
            recommendations << "[Traitement] Oseltamivir 75mg x2/j pendant 5 jours";
            recommendations << "[Prévention] Prophylaxie pour les contacts à risque (personnes âgées, immunodéprimés)";
        }

        if (age > 65 || geneticMarkers.contains("IFITM3")) {
            recommendations << "[Prévention] Vaccination annuelle obligatoire + rappel pneumocoque";
        }
    }
    else if (virusType == "SARS-CoV-2") {
        if (responseType.contains("Sévère")) {
            recommendations << "[Urgence] Oxygénothérapie immédiate si SpO2 < 92%";
            recommendations << "[Traitement] Dexaméthasone 6mg/j pendant 10 jours si oxygène requis";
            recommendations << "[Position] Ventilation en décubitus ventral si hypoxémie réfractaire";
        }

        if (geneticMarkers.contains("ACE2")) {
            recommendations << "[Surveillance] Monitoring cardiologique (troponine, ECG)";
        }
    }

    // 3. Recommandations démographiques
    if (age > 60) {
        recommendations << "[Personne âgée] Bilan gériatrique complet";
        recommendations << "[Personne âgée] Adaptation posologique des médicaments";
        recommendations << "[Personne âgée] Évaluation du risque de chutes";
    }

    if (gender == "Female" && age >= 12 && age <= 50) {
        recommendations << "[Femme] Test de grossesse avant tout traitement tératogène";
        recommendations << "[Femme] Conseil contraceptif pendant le traitement";
    }

    // 4. Recommandations génétiques personnalisées
    if (geneticMarkers.contains("IFNL3") && virusType == "Hepatitis C") {
        recommendations << "[Génétique] Excellente réponse attendue aux AAD (génotype favorable CC)";
    }

    if (geneticMarkers.contains("HLA-B*57:01") && virusType == "HIV") {
        recommendations << "[Génétique] Contre-indication formelle à l'abacavir (risque d'hypersensibilité)";
    }

    if (geneticMarkers.contains("TLR4")) {
        recommendations << "[Génétique] Risque accru de réponse inflammatoire excessive";
    }

    // 5. Recommandations finales communes
    recommendations << "[Général] Documentation complète des antécédents médicaux";
    recommendations << "[Général] Mise à jour des vaccinations de routine";
    recommendations << "[Suivi] Plan de suivi personnalisé à établir avec le médecin traitant";

    return recommendations;
}

void DnaWindow::calculateBasicMetrics()
{
    // Find peak viral load and timing
    m_responseProfile.peakViralLoad = 0;
    m_responseProfile.timeToPeak = 0;

    for (int i = 0; i < m_simulationResults.size(); ++i) {
        const auto& result = m_simulationResults[i];
        if (result.viralLoad > m_responseProfile.peakViralLoad) {
            m_responseProfile.peakViralLoad = result.viralLoad;
            m_responseProfile.timeToPeak = i;
        }
    }

    // Calculate clearance efficiency
    const double initialLoad = m_simulationResults.first().viralLoad;
    const double finalLoad = m_simulationResults.last().viralLoad;

    // Ensure we always have a reasonable clearance efficiency value
    // Even with very small viral loads
    if (initialLoad > 0.0001) { // Lower threshold
        if (finalLoad < initialLoad) {
            m_responseProfile.clearanceEfficiency = ((initialLoad - finalLoad) / initialLoad) * 100.0;
        } else {
            // If final load is higher than initial, use a minimum value based on virus type
            m_responseProfile.clearanceEfficiency = 15.0; // Minimum baseline efficiency
        }
    } else {
        // Even with tiny loads, use a minimum efficiency value
        m_responseProfile.clearanceEfficiency = 25.0;
    }

    // Ensure value is between 15% and 100%
    m_responseProfile.clearanceEfficiency = qBound(15.0, m_responseProfile.clearanceEfficiency, 100.0);

    // Calculate immune activation score
    double maxResponse = 0.0;
    for (const auto& result : m_simulationResults) {
        if (result.immuneResponse > maxResponse) {
            maxResponse = result.immuneResponse;
        }
    }
    m_responseProfile.immuneActivationScore = maxResponse;
}

void DnaWindow::determineResponseType()
{
    if (m_responseProfile.peakViralLoad > 50.0 &&
        m_responseProfile.clearanceEfficiency < 30.0) {
        m_responseProfile.responseType = "Réponse Sévère";
    }
    else if (m_responseProfile.peakViralLoad > 30.0 &&
             m_responseProfile.clearanceEfficiency < 60.0) {
        m_responseProfile.responseType = "Réponse Modérée";
    }
    else if (m_responseProfile.peakViralLoad > 0.1) {
        m_responseProfile.responseType = "Réponse Légère";
    }
    else {
        m_responseProfile.responseType = "Pas de réponse détectée";
    }
}
void DnaWindow::updateAnalysisResultsDisplay()
{
    if (!ui->resultsTextEdit || !ui->responseTypeLabel || !ui->recommendationsTextEdit) {
        qWarning() << "Widgets d'affichage non disponibles";
        return;
    }

    // Affichage des résultats principaux
    ui->resultsTextEdit->append("\n=== RÉSULTATS D'ANALYSE ===");
    ui->resultsTextEdit->append(QString("Type de réponse: %1").arg(m_responseProfile.responseType));
    ui->resultsTextEdit->append(QString("Efficacité d'élimination: %1%").arg(m_responseProfile.clearanceEfficiency, 0, 'f', 1));
    ui->resultsTextEdit->append(QString("Charge virale maximale: %1 U/mL").arg(m_responseProfile.peakViralLoad, 0, 'f', 2));
    ui->resultsTextEdit->append(QString("Délai jusqu'au pic: %1 jours").arg(m_responseProfile.timeToPeak));

    // Mise à jour du label avec style conditionnel
    QString styleSheet = "font-weight: bold; padding: 5px;";
    if (m_responseProfile.responseType.contains("Sévère")) {
        styleSheet += "color: #E74C3C; background-color: #FDEDEC;";
    } else if (m_responseProfile.responseType.contains("Modérée")) {
        styleSheet += "color: #F39C12; background-color: #FEF5E7;";
    } else {
        styleSheet += "color: #2ECC71; background-color: #EAFAF1;";
    }
    ui->responseTypeLabel->setStyleSheet(styleSheet);
    ui->responseTypeLabel->setText("Type: " + m_responseProfile.responseType);

    // Affichage des recommandations
    ui->recommendationsTextEdit->clear();
    ui->recommendationsTextEdit->append("=== RECOMMANDATIONS ===");
    for (const QString& rec : m_responseProfile.recommendations) {
        ui->recommendationsTextEdit->append("• " + rec);
    }
}

void DnaWindow::updatePatientDataDisplay()
{
    ui->patientInfoTextEdit->clear();

    ui->patientInfoTextEdit->append("--- Patient Information ---");
    ui->patientInfoTextEdit->append("Blood Type: " + m_patientData.getBloodType());
    ui->patientInfoTextEdit->append("Age: " + QString::number(m_patientData.getAge()));
    ui->patientInfoTextEdit->append("Gender: " + m_patientData.getGender());

    if (!m_patientData.getFileName().isEmpty()) {
        ui->patientInfoTextEdit->append("Data File: " + m_patientData.getFileName());
        ui->patientInfoTextEdit->append("Import Date: " + m_patientData.getImportDate().toString("yyyy-MM-dd hh:mm:ss"));
    }

    ui->patientInfoTextEdit->append("\n--- Genetic Information ---");
    ui->patientInfoTextEdit->append("HLA Types:");
    for (const QString& hla : m_patientData.getHLATypes()) {
        ui->patientInfoTextEdit->append("- " + hla);
    }

    ui->patientInfoTextEdit->append("\nGenetic Markers:");
    QMap<QString, QString> markers = m_patientData.getGeneticMarkers();
    for (auto it = markers.begin(); it != markers.end(); ++it) {
        ui->patientInfoTextEdit->append("- " + it.key() + ": " + it.value());
    }

    validateInputs();
}

void DnaWindow::updateSimulationResults()
{
    ui->resultsTextEdit->clear();

    if (m_simulationResults.isEmpty()) {
        ui->resultsTextEdit->append("No simulation results available.");
        return;
    }

    ui->resultsTextEdit->append("--- Simulation Results ---");
    ui->resultsTextEdit->append("Patient Blood Type: " + m_patientData.getBloodType());
    ui->resultsTextEdit->append("Virus Type: " + ui->virusTypeComboBox->currentText());
    ui->resultsTextEdit->append("Simulation Depth: " + QString::number(ui->simulationDepthSpinBox->value()));
    ui->resultsTextEdit->append("Parameter Intensity: " + QString::number(ui->parametersSlider->value()) + "%");

    ui->resultsTextEdit->append("\nTimeline:");
    for (int i = 0; i < m_simulationResults.size(); ++i) {
        const SimulationResult& result = m_simulationResults[i];
        ui->resultsTextEdit->append(QString("Day %1: Viral Load = %2, Immune Response = %3")
                                        .arg(i)
                                        .arg(result.viralLoad, 0, 'f', 2)
                                        .arg(result.immuneResponse, 0, 'f', 2));
    }
}

void DnaWindow::generateViralResponseChart()
{
    m_viralLoadChart->removeAllSeries();

    QString virusType = ui->virusTypeComboBox->currentText();
    QLineSeries *viralSeries = new QLineSeries();
    viralSeries->setName("Charge virale - " + virusType);

    // Paramètres de simulation spécifiques au virus
    double peakDay = 10.0, peakLoad = 10.0, clearanceRate = 0.5;
    bool persistentInfection = false;

    if (virusType == "HIV") {
        peakDay = 21.0;  // Pic plus tardif pour le VIH
        peakLoad = 8.0;  // Charge virale initiale
        clearanceRate = 0.1;  // Clairance très lente
        persistentInfection = true;
    }
    else if (virusType == "Hepatitis C") {
        peakDay = 14.0;
        peakLoad = 7.0;
        clearanceRate = 0.2;
        persistentInfection = true;
    }
    else if (virusType == "SARS-CoV-2") {
        peakDay = 7.0;
        peakLoad = 15.0;
        clearanceRate = 0.4;
    }
    else if (virusType == "Influenza A") {
        peakDay = 3.0;
        peakLoad = 12.0;
        clearanceRate = 0.8;
    }
    else if (virusType == "Epstein-Barr") {
        peakDay = 14.0;
        peakLoad = 6.0;
        clearanceRate = 0.3;
    }

    // Générer des données simulées réalistes
    for (int day = 0; day < m_simulationResults.size(); ++day) {
        double value;

        // Modèle pour le VIH (charge virale persistante)
        if (virusType == "HIV") {
            value = peakLoad * exp(-0.02 * day) + 1.0 * (1 - exp(-0.02 * day));
        }
        // Modèle pour l'hépatite C (évolution plus lente)
        else if (virusType == "Hepatitis C") {
            value = peakLoad * exp(-0.05 * day) + 0.5 * (1 - exp(-0.05 * day));
        }
        // Modèle pour les infections aiguës (grippe, COVID)
        else {
            double progress = (double)day / peakDay;
            if (day <= peakDay) {
                value = peakLoad * (1 - exp(-progress * 3));
            } else {
                value = peakLoad * exp(-clearanceRate * (day - peakDay));
            }
        }

        m_simulationResults[day].viralLoad = value;
        viralSeries->append(day, value);
    }

    m_viralLoadChart->addSeries(viralSeries);
    m_viralLoadChart->createDefaultAxes();
    m_viralLoadChart->axisX()->setTitleText("Jours");
    m_viralLoadChart->axisY()->setTitleText("Charge virale (log copies/mL)");
    m_viralLoadChart->axisY()->setMin(0);

    // Ajuster l'échelle Y pour les infections persistantes
    if (persistentInfection) {
        m_viralLoadChart->axisY()->setMax(peakLoad * 1.2);
    }
}

void DnaWindow::generateImmuneResponseChart()
{
    m_immuneResponseChart->removeAllSeries();

    QString virusType = ui->virusTypeComboBox->currentText();
    QLineSeries *series = new QLineSeries();
    series->setName("Réponse immunitaire - " + virusType);

    // Paramètres de réponse immunitaire spécifiques au virus
    double peakDay = 10.0, peakResponse = 10.0, declineRate = 0.5;
    bool persistentResponse = false;
    bool memoryResponse = false;

    // Configuration spécifique pour chaque type de virus
    if (virusType == "HIV") {
        peakDay = 21.0;  // Réponse plus tardive
        peakResponse = 6.0;  // Réponse affaiblie
        declineRate = 0.1;  // Décroissance lente
        persistentResponse = true;
    }
    else if (virusType == "Hepatitis C") {
        peakDay = 14.0;
        peakResponse = 7.0;
        declineRate = 0.2;
        persistentResponse = true;
    }
    else if (virusType == "SARS-CoV-2") {
        peakDay = 7.0;
        peakResponse = 12.0;
        declineRate = 0.3;
        memoryResponse = true;
    }
    else if (virusType == "Influenza A") {
        peakDay = 5.0;
        peakResponse = 15.0;
        declineRate = 0.6;
        memoryResponse = true;
    }
    else if (virusType == "Epstein-Barr") {
        peakDay = 14.0;
        peakResponse = 8.0;
        declineRate = 0.4;
        persistentResponse = true;
    }

    // Générer une courbe de réponse immunitaire réaliste
    for (int day = 0; day < m_simulationResults.size(); ++day) {
        double value;

        if (day <= peakDay) {
            // Phase de montée de la réponse immunitaire
            value = peakResponse * (1 - exp(-0.5 * day / peakDay));
        } else {
            // Phase de déclin
            if (persistentResponse) {
                // Pour les infections persistantes, la réponse reste élevée
                value = peakResponse * 0.8 * exp(-0.01 * (day - peakDay));
            } else if (memoryResponse) {
                // Pour les infections aiguës avec mémoire immunologique
                value = peakResponse * exp(-declineRate * (day - peakDay)) + 2.0;
            } else {
                // Déclin normal
                value = peakResponse * exp(-declineRate * (day - peakDay));
            }
        }

        // Ajuster selon les marqueurs génétiques du patient
        if (m_patientData.getGeneticMarkers().contains("IFITM3")) {
            value *= 1.2;  // Meilleure réponse antivirale
        }
        if (m_patientData.getGeneticMarkers().contains("TLR4")) {
            value *= 0.8;  // Réponse inflammatoire réduite
        }

        m_simulationResults[day].immuneResponse = value;
        series->append(day, value);
    }

    m_immuneResponseChart->addSeries(series);
    m_immuneResponseChart->createDefaultAxes();
    m_immuneResponseChart->axisX()->setTitleText("Jours après infection");
    m_immuneResponseChart->axisY()->setTitleText("Niveau de réponse immunitaire");
    m_immuneResponseChart->axisY()->setMin(0);

    // Personnalisation de l'apparence
    series->setColor(QColor(0, 100, 0));  // Vert foncé pour la réponse immunitaire
    series->setPen(QPen(series->color(), 2));

    // Ajouter une série pour montrer la charge virale en comparaison
    if (!m_simulationResults.isEmpty()) {
        QLineSeries *viralSeries = new QLineSeries();
        viralSeries->setName("Charge virale (comparaison)");
        viralSeries->setColor(QColor(139, 0, 0));  // Rouge foncé

        for (int day = 0; day < m_simulationResults.size(); ++day) {
            viralSeries->append(day, m_simulationResults[day].viralLoad);
        }

        m_immuneResponseChart->addSeries(viralSeries);
        m_immuneResponseChart->createDefaultAxes();  // Recréer les axes pour inclure les deux séries
    }
}


void DnaWindow::on_bloodTypeComboBox_currentIndexChanged(int index)
{
    if (index >= 0) {
        m_patientData.setBloodType(ui->bloodTypeComboBox->currentText());
        updatePatientDataDisplay();
    }
}

void DnaWindow::on_virusTypeComboBox_currentIndexChanged(int index)
{
    validateInputs();
}

void DnaWindow::on_parametersSlider_valueChanged(int value)
{
    ui->parameterValueLabel->setText(QString::number(value) + "%");
}

void DnaWindow::on_simulationDepthSpinBox_valueChanged(int value)
{
    validateInputs();
}

void DnaWindow::on_actionExportResults_triggered()
{
    if (m_simulationResults.isEmpty()) {
        displayErrorMessage("Export Error", "No simulation results to export.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Export Simulation Results", "", "CSV Files (*.csv);;Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        displayErrorMessage("Export Error", "Could not open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write header
    out << "Day,ViralLoad,ImmuneResponse" << Qt::endl;

    // Write data
    for (int i = 0; i < m_simulationResults.size(); ++i) {
        out << i << ","
            << m_simulationResults[i].viralLoad << ","
            << m_simulationResults[i].immuneResponse
            << Qt::endl;
    }

    file.close();
    statusBar()->showMessage("Results exported to " + fileName, 3000);
}

void DnaWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void DnaWindow::displayErrorMessage(const QString &title, const QString &message)
{
    QMessageBox::warning(this, title, message);
}

void DnaWindow::on_virusParametersChanged()
{
    if (!m_simulationResults.isEmpty()) {
        generateViralResponseChart();
        generateImmuneResponseChart();
    }
}
