#ifndef GRENDERVOUS_H
#define GRENDERVOUS_H

#include <QMainWindow>
#include <QtSvg/QSvgGenerator>



QT_BEGIN_NAMESPACE
namespace Ui {
class grendervous;
}
QT_END_NAMESPACE

class grendervous : public QMainWindow
{
    Q_OBJECT

public:
    grendervous(QWidget *parent = nullptr);
    ~grendervous();
    void onpage4();

public slots:
    void on_displaybutton_2_clicked();
    void generateQRCode(int id, const QString &outputPath);
    void envoyerEmailAvecQRCode(const QString &email, const QString &pathFichierSVG);
    void afficherStatistiques();
    void generatePDF(int id, const QString &pdfPath);





private slots:
    void on_addbutton_2_clicked();

    void on_deletebutton_2_clicked();

    void on_updatebutton_2_clicked();

    void on_save_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_16_clicked();

    void on_searchbutton_2_clicked();

    void on_sort_clicked();

    void on_qr_clicked();

    void on_voice_clicked();

    void on_btnPrioriser_clicked();

    void on_btnGenererAuto_clicked();

    void on_statsButton_clicked();

    void on_btnFermerStats_clicked();




private:
    Ui::grendervous *ui;
     int currentEditId;


};
#endif // GRENDERVOUS_H
