/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    // Retrieve values from UI elements
    QString IDR = ui->IDEQ->text();
    QString TITRER = ui->NOMEQ->text();
    QString CLASSR = ui->TYPEEQ->currentText(); // Get selected value from combobox
    QString DESCR = ui->DESCEQ->toPlainText(); // Get text from QTextEdit
    QString DATEM = ui->TEMPMEQ->date().toString("yyyy-MM-dd"); // Get date from QDateEdit

    // Validate ID input
    bool idConversionSuccess;
    int idint = IDR.toInt(&idConversionSuccess);

    if (!idConversionSuccess) {
        QMessageBox::warning(this, "Invalid Input", "ID must be a valid integer.");
        return;
    }

    // Check if required fields are empty
    if (IDR.isEmpty() || TITRER.isEmpty() || CLASSR.isEmpty() || DESCR.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "All fields except DateF must be filled out.");
        return;
    }

    // Create a Crud object and add the recherche
    Crud add(idint, TITRER, CLASSR, DESCR, DATEM);
    add.add_recherche(ui->tableWidget);

    // Clear input fields
    ui->IDEQ->clear();
    ui->NOMEQ->clear();
    ui->TYPEEQ->setCurrentIndex(0); // Reset combobox
    ui->DESCEQ->clear();
    ui->TEMPMEQ->setDate(QDate::currentDate());

    // Notify the user
    QMessageBox::information(this, "Success", "Recherche added successfully!");
}

void MainWindow::on_deleteb_clicked()
{
    QString id2 = ui->rech->text(); // Keeping ID2 for deletion
    bool idConversionSuccess;
    int id2int = id2.toInt(&idConversionSuccess);

    if (!idConversionSuccess) {
        QMessageBox::warning(this, "Invalid Input", "ID must be a valid integer.");
        return;
    }

    Crud drop;
    drop.delete_recherche(id2int, ui->tableWidget);

    // Clear ID2 input field after deletion
    ui->rech->clear();

    QMessageBox::information(this, "Success", "Recherche deleted successfully!");
}

*/
