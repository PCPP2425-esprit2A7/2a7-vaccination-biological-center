#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_deleteb_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_cancelButton_clicked();
    void on_rechb_clicked();
    void on_rech_textChanged(const QString &searchText);
    void on_sortComboBox_changed(const QString &sortType);
    void on_pdfb_clicked();
    void on_statComboBox_changed(const QString &selectedOption);
private:
    Ui::MainWindow *ui;
    bool isEditMode = false;
    int currentEditId = -1;
};
#endif // MAINWINDOW_H
