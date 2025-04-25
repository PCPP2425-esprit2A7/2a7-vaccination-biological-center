#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QLayout>
#include <QVBoxLayout>
#include "dnawindow.h"  // Ajout de l'inclusion pour DnaWindow
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Button handlers
    void on_ajouter_clicked();
    void on_cancel_clicked();
    void on_browseButton_clicked();
    void on_DNAbutton_clicked();  // Ajout du slot pour le bouton DNAbutton
    void on_StatButton_clicked();
    // UI event handlers
    void on_nom2_textChanged(const QString &text);
    void on_tableWidget_cellClicked(int row, int column);
    void on_sortComboBox_changed(const QString &sortType);




private:
    Ui::MainWindow *ui;
    int selectedPatientId = -1;
    QString currentFilePath;
    QLineEdit *fileLabel;
    DnaWindow *dnaWindow;  // Ajout du pointeur vers DnaWindow
    bool showingStats = false;

    void showPatientTable();
    void showStatistics();
};

#endif // MAINWINDOW_H
