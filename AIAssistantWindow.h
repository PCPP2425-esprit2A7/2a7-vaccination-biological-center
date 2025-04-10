#ifndef AIASSISTANTWINDOW_H
#define AIASSISTANTWINDOW_H

#include <QDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "OpenAIChatBot.h"

namespace Ui {
class AIAssistantWindow;
}

class AIAssistantWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AIAssistantWindow(QWidget *parent = nullptr);
    ~AIAssistantWindow();
    void setResearchContext(const QString &title, const QString &classification,
                            const QString &description, const QString &startDate,
                            const QString &endDate);

    QString getGeneratedDescription() const;

private slots:
    void on_sendButton_clicked();
    void on_analyzeButton_clicked();
    void on_generateButton_clicked();
    void on_clearChatButton_clicked();
    void on_apiKeyButton_clicked();
    void on_applyButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::AIAssistantWindow *ui;
    OpenAIChatBot *chatbot;
    QString openaiApiKey;
    QString currentTitle;
    QString currentClassification;
    QString currentDescription;
    QString currentStartDate;
    QString currentEndDate;
    QString generatedDescription;

    void appendToChatDisplay(const QString &speaker, const QString &message);
    void loadApiKey();
    void saveApiKey(const QString &key);
    void setupChatbot();
    void showWaitingIndicator(bool show);
};

#endif // AIASSISTANTWINDOW_H
