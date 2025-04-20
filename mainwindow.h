#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>  // Ajouter cette inclusion
#include "vaccin.h"
#include <QMouseEvent>    // Pour QMouseEvent
#include <QApplication>   // Pour QApplication::widgetAt()
#include <QHeaderView>    // Pour la vérification QHeaderView
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPropertyAnimation>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void on_pushButton_15_clicked();
    void on_drop_clicked();
    void mousePressEvent(QMouseEvent *event);
    void on_pushButton_Modifier_clicked();
    void on_pushButton_Rafraichir_clicked();
    void verifierNom();
    void verifierValidation();
    void verifierDescription();
    void verifierDateFabrication();
    void verifierMaladie();
    void filtrerVaccins(const QString &term);
    /*void on_pushButton_Rechercher_clicked();*/
    void on_pushButton_tri_clicked();
    void chargerDonneesDansTableWidget();
    void on_pushButton_Reinitialiser_clicked();
    void exporterCSV();
    void on_pushButton_PDF_clicked();
    void on_pushButton_Historique_clicked();
    void on_StatButton_clicked();
    void on_btnEtudeConcurrence_clicked();
    QString getSelectedVaccinId();


private:
    Ui::MainWindow *ui;
    vaccin v;
    int currentSelectedId = -1;  // Stocke l'ID de la ligne sélectionnée
    bool isEditMode = false;
    int currentEditId = -1;
    void updateTableWidget();  // Nouvelle méthode pour mettre à jour le QTableWidget
    void afficherHistoriqueVaccin(int idVaccin);


};

class AnimatedBarItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(int barHeight READ barHeight WRITE setBarHeight)

public:
    AnimatedBarItem(int x, int baseY, int width, QColor color)
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

















