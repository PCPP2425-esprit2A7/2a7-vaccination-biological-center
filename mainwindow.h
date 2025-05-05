#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "serialhandler.h"
#include <QMainWindow>
#include <QStyledItemDelegate>
#include <QComboBox>
#include "AIAssistantWindow.h"
#include "arduino.h"
#include "SimulationDialog.h"
#include "AnimatedBarItem.h"
#include "crud.h"
#include "smtp_mailer_secure.h"
#include "PatientDetailsDialog.h"
#include "animatedbaritem.h"
#include "dnawindowp.h"
#include <QTableWidget>  // Ajouter cette inclusion
#include <QMouseEvent>    // Pour QMouseEvent
#include <QApplication>   // Pour QApplication::widgetAt()
#include <QHeaderView>    // Pour la vérification QHeaderView
#include <QGraphicsRectItem>
#include <QObject>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPropertyAnimation>
#include <QTimer>
// haw fi khatrek ya aboud
#include <QWidget>
#include <QStackedWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSerialPort>
#include <QLabel>
#include <QChartView>
#include <QGraphicsView>
#include <QStyledItemDelegate>
#include <QtSvg/QSvgGenerator>
//faresssss
#include <QComboBox>
#include <QDateEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QHBoxLayout>
#include "predictivemaintenancedialog.h"










QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE





class ClassificationDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    ClassificationDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};
class DateDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    DateDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

//faressssss
// Custom delegate for Type field
class TypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TypeDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

// Custom delegate for Status field
class EtatDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit EtatDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openAIWindow(const QString &title,
                      const QString &classification,
                      const QString &description,
                      const QString &startDate,
                      const QString &endDate);
    AIAssistantWindow* getAIInstance();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    //jihedddd
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:
    void envoyerEmailAvecInfos(const QString &email, const QString &body);
    void on_displaybutton_2_clicked();

private slots:
    //taherrrrrrrrrrrrrrrrrrr
    void on_ajouterE_clicked(); // Add user
    void on_deletebE_clicked(); // Delete user
    void on_tableWidgetE_cellDoubleClicked(int row, int column); // Handle table click
    void on_cancelButtonE_clicked();
    void on_rechbE_clicked();
    void on_rechE_textChanged(const QString &searchText);  // Search field
    void on_sortComboBoxE_changed(const QString &sortType);
    void on_loginButton_clicked();
    void on_disconnect_clicked(); // Déconnexion (Logout)
    void on_pdfbE_clicked(); // PDF generation
    void handleRFID(const QString &uid);
    //************************************************************************Amineeeeeeeee***************************************************************************************
    void on_ajouterR_clicked();
    void on_deletebR_clicked();
    void on_tableWidgetR_cellDoubleClicked(int row, int column);
    void on_cancelButtonR_clicked();
    void on_rechbR_clicked();
    void on_rechR_textChanged(const QString &searchText);
    void on_sortComboBoxR_changed(const QString &sortType);
    void on_StatButtonR_clicked();
    void on_pdfbR_clicked();
    void on_tableWidgetR_cellChanged(int row, int column);
    void on_openAIAssistantButton_clicked();
    void on_simulationButton_clicked();
    void updateTemperature();
    void connectArduino();
    void disconnectArduino();
    void on_emp_clicked();
    void on_pdr_clicked();
    void on_pt_clicked();
    void on_eqbtn_clicked();
    //************************************************************************YYouseffffffffffffffff***************************************************************************************
    void on_ajouterp_clicked();
    void on_cancelp_clicked();
    void on_browseButtonp_clicked();
    void on_DNAbutton_clicked();  // Ajout du slot pour le bouton DNAbutton
    void on_StatButtonp_clicked();
    // UI event handlers
    void on_nom2p_textChanged(const QString &text);
    void on_tableWidgetp_cellClicked(int row, int column);
    void on_sortComboBoxp_changed(const QString &sortType);


 //************************************************************************jihedddddddddddddddddddddddddddd***************************************************************************************
    void on_pushButton_15v_2_clicked();
    void on_dropv_2_clicked();
    void mousePressEvent(QMouseEvent *event);
    void on_pushButton_Modifierv_2_clicked();
    void on_pushButton_Rafraichirv_2_clicked();
    void verifierNom();
    void verifierValidation();
    void verifierDescription();
    void verifierDateFabrication();
    void verifierMaladie();
    void filtrerVaccins(const QString &term);
    /*void on_pushButton_Rechercher_clicked();*/
    // void on_pushButton_tri_clicked();
    void chargerDonneesDansTableWidgetv();
    void on_pushButton_Reinitialiserv_2_clicked();
    void exporterCSVv_2();
    void on_pushButton_PDFv_2_clicked();
    void on_pushButton_Historiquev_2_clicked();
    void on_StatButtonv_2_clicked();
    void on_btnEtudeConcurrencev_2_clicked();
    QString getSelectedVaccinIdv();
    void mettreAJourAffichageTriv_2();
    void on_tableWidgetv_2_cellDoubleClicked(int row, int column);

    //ahmed.h
    void on_addbutton_2_clicked();
    void on_deletebutton_2_clicked();
    void on_updatebutton_2_clicked();
    void on_searchbutton_2_clicked();
    void on_sort_clicked();
    void on_qr_clicked();
    void on_statsButton_clicked();
    void on_btnPrioriser_clicked();
    void on_btnGenererAuto_clicked();
    void generateQRCode(int id, const QString &outputPath);
    void envoyerEmailAvecQRCode(const QString &email, const QString &pathFichier);
    void generatePDF(int id, const QString &pdfPath);
    void afficherStatistiques();
    void on_pushButton_18_clicked();
    void on_rdvbtn_clicked();
    void on_rdvRowDoubleClicked(int row, int column);
    void remplirTableAvecQuery(QSqlQuery &query);
    void retournerAuTableau();
    //**************faaaresssssssss***********************************
    void on_ajouter_clicked();
    void on_deleteb_clicked();
    void on_cancelButton_clicked();
    void on_tableWidget_cellChangedfares(int row, int column);
    void on_tableWidget_cellDoubleClickedfares(int row, int column);
    void on_rechb_clicked();
    void on_rech_textChanged(const QString &searchText);
    void on_sortComboBox_changed(const QString &sortType);
    void on_pdfb_clicked();
    void on_StatButton_clicked();
    void on_checkb_clicked();


    void on_vac_clicked();


private:
    Ui::MainWindow *ui;
    //taher
    bool userEditMode = false;
    int currentUserEditId = -1;
    bool isUserLoggedIn = false;
    void showLoginPage();
    void showMainPage();
    // New UI element to capture RFID UID
    void handleRfidInput();
    // Function to manage RFID input
    SerialHandler *serialHandler;
    QString currentRFID;
    //amine
    void researchPage();
    void techPage();
    bool researchEditMode = false;
    int currentResearchEditId = -1;
    bool isTableBeingUpdated = false;
    ClassificationDelegate *classDelegate;
    DateDelegate *dateDelegate;
    AIAssistantWindow* aiWindow = nullptr;
    //youssef
    void showPatientPage();
    void showVaccinPage();
    void updateRoleStatistics();
    int selectedPatientId = -1;
    QString currentFilePath;
    QLineEdit *fileLabel;
    DnaWindow *dnaWindowp;  // Ajout du pointeur vers DnaWindow
    bool showingStats = false;
    void showPatientTablep();
    void showRendezVousPage();
    void showStatisticsp();
    //jiheddddd
    vaccin v;
    int currentSelectedId = -1;  // Stocke l'ID de la ligne sélectionnée
    bool isEditMode = false;
    int currentEditId = -1;
    void updateTableWidget();  // Nouvelle méthode pour mettre à jour le QTableWidget
    void afficherHistoriqueVaccin(int idVaccin);
    QTimer *timerTemperature; // Timer pour surveiller température
    bool alerteEnvoyee = false;
    MainWindow* fenetreSecondaire = nullptr;
    bool interventionEnCours = false;
    bool enModeHistorique = false;
    QTimer *timer;
    Arduino *arduino;
    bool isConnected;
    //commun
    int page;
    int idN;
    QString roleN;
    bool statistiquesAffichees = false;


    //ahmeddddddddddddddddddddddddddddddddddd

    // Champs page_3
    QLineEdit *id_2, *search;
    QPushButton *addbutton_2, *updatebutton_2, *deletebutton_2, *searchbutton_2;
    QPushButton *displaybutton_2, *qr, *sort, *voice, *statsButton;
    QPushButton *btnPrioriser, *btnGenererAuto, *btnConnecterArduino, *pushButton_18;
    QTableView *tableView_2;

    // Champs page_4 (modification)
    QLineEdit *idp_3, *ide_3, *statut_3, *dur_3, *heure_3, *date_3;
    QPushButton *on_saveButton, *on_pushButton_28;

    // Champs page ajout
    QLineEdit *idp_2, *ide_2, *statut_2, *dur_2, *heure_2, *date_2;

    // Statistiques
    QChartView *pieChartView;
    QGraphicsView *barChartView;

    QWidget *page_3, *page_4, *page_statistiques;
    QWidget *statChartLayout;
    QHBoxLayout *layoutStats;

    //faaaaaaaaresssssssssssssssssssss
    equipement e;
    bool isEditModeequipment = false;
    int currentEditIdequipment = -1;
    bool isTableBeingUpdatedequipment = false;
    TypeDelegate *typeDelegate;
    EtatDelegate *etatDelegate;
    //DateDelegate *dateDelegate;


};

//jiheddddddddddddddddddddd
class AnimatedBarItemv : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(int barHeight READ barHeight WRITE setBarHeight)

public:
    AnimatedBarItemv(int x, int baseY, int width, QColor color)
        : baseY(baseY), width(width) {
        setBrush(QBrush(color));
        setPen(QPen(Qt::NoPen));

        setRect(x, baseY, width, 0);
    }

    int barHeight() const { return m_barHeight; }

    void setBarHeight(int height) {
        m_barHeight = height;
        setRect(rect().x(), baseY - height, width, height);
    }

private:
    int m_barHeight = 0;
    int baseY;
    int width;

};

#endif // MAINWINDOW_H
