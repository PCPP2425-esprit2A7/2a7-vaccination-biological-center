#ifndef AIASSISTANTWINDOW_H
#define AIASSISTANTWINDOW_H
#include <QSoundEffect>
#include <QDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include "OpenAIChatBot.h"
#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QBuffer>
#include <QMovie>
#include <QLabel>
#include <QProcess>

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
    void prepareForUse();

signals:
    void descriptionAccepted(const QString &description);

private slots:
    void on_sendButton_clicked();
    void on_analyzeButton_clicked();
    void on_generateButton_clicked();
    void on_clearChatButton_clicked();
    void on_apiKeyButton_clicked();
    void on_applyButton_clicked();
    void on_closeButton_clicked();
    void typeNextWord();
    void on_micButton_released();
    void addSimulatedWord();

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
    QTimer *typingTimer;
    QStringList currentWords;
    int currentWordIndex;
    QString currentTarget;
    QString fullResponse;
    QSoundEffect *typingSound;
    QAudioSource* audioSource;
    QBuffer* audioBuffer;
    bool isRecording;
    QTimer* voiceTypingTimer;
    QStringList simulatedWords;
    int currentSimulatedWordIndex;
    QProcess* pythonProcess;
    QLabel* voiceAnimationLabel;
    QMovie* voiceAnimation;
    bool isGenerating;


    void appendToChatDisplay(const QString &speaker, const QString &message);
    void loadApiKey();
    void saveApiKey(const QString &key);
    void setupChatbot();
    void showWaitingIndicator(bool show);
    void ensureLoadingIndicator();
    void startTypingEffect(const QString &text, const QString &target, const QString &speaker = "Assistant");
    void runPythonSpeechRecognition();
    void handlePythonOutput();
};

#endif // AIASSISTANTWINDOW_H
