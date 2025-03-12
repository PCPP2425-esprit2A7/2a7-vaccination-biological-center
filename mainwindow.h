#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_drop_clicked();
    void on_mod_clicked();
    void on_id2_textChanged(const QString &text);
    void on_nom2_textChanged(const QString &text);
    void on_tableWidget_cellClicked(int row, int column);
    void on_pdf_clicked();
    void on_cancel_clicked();
    void updateStatistics();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
