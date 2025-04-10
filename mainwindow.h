#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyledItemDelegate>
#include <QComboBox>
#include "AIAssistantWindow.h"

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
    void on_StatComboBox_changed(const QString &selectedOption);
    void on_pdfb_clicked();
    void on_tableWidget_cellChanged(int row, int column);
    void on_openAIAssistantButton_clicked();
    void on_simulationButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isEditMode = false;
    int currentEditId = -1;
    bool isTableBeingUpdated = false;
    ClassificationDelegate *classDelegate;
    DateDelegate *dateDelegate;
    static AIAssistantWindow* aiAssistantInstance;
};

#endif // MAINWINDOW_H
