#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "serialhandler.h"

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

public slots:
    void envoyerEmailAvecInfos(const QString &email, const QString &body);

private slots:
    void on_ajouter_clicked(); // Add user
    void on_deleteb_clicked(); // Delete user
    void on_tableWidget_cellDoubleClicked(int row, int column); // Handle table click
    void on_cancelButton_clicked();
    void on_rechb_clicked();
    void on_rech_textChanged(const QString &searchText);  // Search field
    void on_sortComboBox_changed(const QString &sortType);
    void on_loginButton_clicked();
    void on_pushButton_8_clicked(); // Déconnexion (Logout)
    void on_pdfb_clicked(); // PDF generation
    void handleRFID(const QString &uid);

private:
    Ui::MainWindow *ui;
    bool isEditMode = false;
    int currentEditId = -1;
    bool isLoggedIn = false;
    void showLoginPage();
    void showMainPage();
    void updateRoleStatistics();
    QString currentRFID;

    // New UI element to capture RFID UID
    void handleRfidInput();
    // Function to manage RFID input
    SerialHandler *serialHandler;
};

#endif // MAINWINDOW_H
