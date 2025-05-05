#ifndef PATIENTDETAILSDIALOGP_H
#define PATIENTDETAILSDIALOGP_H

#include <QDialog>
#include <QTableWidget>
#include <QByteArray>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class PatientDetailsDialog; }
QT_END_NAMESPACE

class PatientDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDetailsDialog(int id, QTableWidget *mainTable, QWidget *parent = nullptr);
    ~PatientDetailsDialog();

private slots:
    void loadPatientData(int id);
    void updatePatientDetails();
    void setFieldsReadOnly(bool readOnly);


    void saveDocumentp();
    void exportPDFp();
    void deletePatientp();
    void browseDocumentp();
    void modifyPatientp();
    void enableEditingp();
    void cancelEditingp();

private:
    Ui::PatientDetailsDialog *ui;
    QTableWidget *parentTable;
    bool editMode;
    int patientId;
    QByteArray documentData;
    QString currentFilePath;
    QTextBrowser *documentPreview;
    QString formatPhoneNumber(const QString& phone) const;
    bool validateId(const QString& id);
    bool validateName(const QString& name);
    bool validatePhone(const QString& phone);
    // Constantes
    static const int TELEPHONE_LENGTH = 8;
    static const int MAX_PREVIEW_SIZE = 50000;
};

#endif // PATIENTDETAILSDIALOGP_H
