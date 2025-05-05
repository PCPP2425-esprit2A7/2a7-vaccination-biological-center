#include "AIAssistantWindow.h"
#include "ui_AIAssistantWindow.h"
#include <QSettings>
#include <QInputDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QApplication>
#include <QRegularExpression>

AIAssistantWindow::AIAssistantWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AIAssistantWindow),
    chatbot(nullptr),
    typingTimer(nullptr),
    currentWordIndex(0),
    isRecording(false),
    audioSource(nullptr),
    audioBuffer(nullptr),
    voiceTypingTimer(nullptr),
    pythonProcess(nullptr),
    voiceAnimationLabel(nullptr),
    voiceAnimation(nullptr),
    isGenerating(false)
{
    ui->setupUi(this);
    setWindowTitle("AI Research Assistant");
    resize(800, 600);
    typingTimer = new QTimer(this);
    connect(typingTimer, &QTimer::timeout, this, &AIAssistantWindow::typeNextWord);
    loadApiKey();
    setupChatbot();
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &AIAssistantWindow::on_sendButton_clicked);
    typingSound = new QSoundEffect(this);
    typingSound->setSource(QUrl("qrc:/new/prefix1/image/typing.wav"));
    typingSound->setLoopCount(QSoundEffect::Infinite);
    typingSound->setVolume(1.0f);
    if (ui->micButton) {
        connect(ui->micButton, &QPushButton::released, this, &AIAssistantWindow::on_micButton_released);
    }
}

AIAssistantWindow::~AIAssistantWindow()
{
    if (chatbot) {
        delete chatbot;
        chatbot = nullptr;
    }
    if (audioSource) {
        audioSource->stop();
        delete audioSource;
    }

    if (audioBuffer) {
        audioBuffer->close();
        delete audioBuffer;
    }

    if (voiceTypingTimer) {
        voiceTypingTimer->stop();
        delete voiceTypingTimer;
    }
    if (pythonProcess) {
        if (pythonProcess->state() == QProcess::Running) {
            pythonProcess->terminate();
            if (!pythonProcess->waitForFinished(1000)) {
                pythonProcess->kill();
                pythonProcess->waitForFinished(500);
            }
        }
        delete pythonProcess;
        pythonProcess = nullptr;
    }
    if (voiceAnimation) {
        voiceAnimation->stop();
        delete voiceAnimation;
    }
    if (voiceAnimationLabel) {
        delete voiceAnimationLabel;
    }
    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
    delete ui;
}

void AIAssistantWindow::prepareForUse()
{
    ui->chatDisplay->clear();
    ui->chatInput->clear();
    ui->descriptionEdit->clear();
    if (pythonProcess && pythonProcess->state() == QProcess::Running) {
        pythonProcess->terminate();
        if (!pythonProcess->waitForFinished(1000)) {
            pythonProcess->kill();
        }
    }
    if (voiceAnimation) {
        voiceAnimation->stop();
    }
    if (voiceAnimationLabel && voiceAnimationLabel->isVisible()) {
        voiceAnimationLabel->hide();
    }
    if (typingTimer && typingTimer->isActive()) {
        typingTimer->stop();
    }

    if (voiceTypingTimer && voiceTypingTimer->isActive()) {
        voiceTypingTimer->stop();
    }
    if (chatbot) {
        QString savedKey = openaiApiKey;
        delete chatbot;
        chatbot = nullptr;
        openaiApiKey = savedKey;
        chatbot = new OpenAIChatBot(openaiApiKey);
        appendToChatDisplay("Assistant", "Hello! I'm your research assistant powered by GPT-4o via Azure. How can I help with your research today?");
    }
    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
}

void AIAssistantWindow::setResearchContext(const QString &title, const QString &classification,
                                           const QString &description, const QString &startDate,
                                           const QString &endDate)
{
    currentTitle = title;
    currentClassification = classification;
    currentDescription = description;
    currentStartDate = startDate;
    currentEndDate = endDate;


    if (!description.isEmpty()) {
        ui->descriptionEdit->setPlainText(description);
    }


    if (chatbot && (!title.isEmpty() || !description.isEmpty())) {
        QString contextMsg = "I'm working on a research project ";

        if (!title.isEmpty()) {
            contextMsg += "titled \"" + title + "\" ";
        }

        if (!classification.isEmpty()) {
            contextMsg += "in the " + classification + " classification ";
        }

        if (!description.isEmpty()) {
            contextMsg += "with the following description: \"" + description + "\"";
        }

        if (!startDate.isEmpty() && !endDate.isEmpty()) {
            contextMsg += ". The project runs from " + startDate + " to " + endDate + ".";
        }

        appendToChatDisplay("System", "Context loaded: Research information has been provided to the assistant.");
    }
}

QString AIAssistantWindow::getGeneratedDescription() const
{
    return ui->descriptionEdit->toPlainText();
}

void AIAssistantWindow::on_sendButton_clicked()
{
    QString userInput = ui->chatInput->text().trimmed();
    if (userInput.isEmpty()) return;

    appendToChatDisplay("You", userInput);
    ui->chatInput->clear();


    if (!chatbot) {
        appendToChatDisplay("System", "Please set your OpenAI API key first to enable AI features.");
        return;
    }
    showWaitingIndicator(true);

    QFuture<QString> future = QtConcurrent::run([=]() {
        return chatbot->getResponse(userInput, currentDescription);
    });

    QFutureWatcher<QString> *watcher = new QFutureWatcher<QString>();
    connect(watcher, &QFutureWatcher<QString>::finished, this, [=]() {
        QString response = watcher->result();

        showWaitingIndicator(false);

        startTypingEffect(response, "chat", "Assistant");

        if (response.length() > 150 && (
                userInput.contains("generate", Qt::CaseInsensitive) ||
                userInput.contains("description", Qt::CaseInsensitive) ||
                userInput.contains("create", Qt::CaseInsensitive) ||
                userInput.contains("write", Qt::CaseInsensitive)))
        {
            QTimer::singleShot(response.length() * 5, this, [=]() {
                startTypingEffect(response, "description");
                appendToChatDisplay("System", "The generated text has been added to the description field below.");
            });
        }
        watcher->deleteLater();
    });

    watcher->setFuture(future);
}

void AIAssistantWindow::on_analyzeButton_clicked()
{
    QString description = ui->descriptionEdit->toPlainText().trimmed();
    if (description.isEmpty()) {
        description = currentDescription;
    }

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Empty Description", "Please enter a description to analyze.");
        return;
    }

    if (!chatbot) {
        QMessageBox::warning(this, "API Key Required", "Please set your OpenAI API key first.");
        return;
    }

    showWaitingIndicator(true);

    QFuture<QString> future = QtConcurrent::run([=]() {
        return chatbot->analyzeDescription(description);
    });

    QFutureWatcher<QString> *watcher = new QFutureWatcher<QString>();
    connect(watcher, &QFutureWatcher<QString>::finished, this, [=]() {
        QString analysis = watcher->result();

        showWaitingIndicator(false);
        startTypingEffect("Here's my analysis of your research description:", "chat", "Assistant");
        startTypingEffect(analysis, "chat", "Analysis");

        watcher->deleteLater();
    });

    watcher->setFuture(future);
}

void AIAssistantWindow::on_generateButton_clicked()
{
    if (currentTitle.isEmpty() && currentClassification.isEmpty()) {
        QMessageBox::warning(this, "Missing Information",
                             "Please provide at least a title or classification for context.");
        return;
    }

    if (!chatbot) {
        QMessageBox::warning(this, "API Key Required", "Please set your OpenAI API key first.");
        return;
    }

    QString context = "I need to write a description for a research project ";

    if (!currentTitle.isEmpty()) {
        context += "titled \"" + currentTitle + "\" ";
    }

    if (!currentClassification.isEmpty()) {
        context += "in the " + currentClassification + " classification ";
    }

    if (!currentStartDate.isEmpty() && !currentEndDate.isEmpty()) {
        context += "running from " + currentStartDate + " to " + currentEndDate + " ";
    }

    context += ". Please generate a comprehensive and professional research description.";

    showWaitingIndicator(true);


    QFuture<QString> future = QtConcurrent::run([=]() {
        return chatbot->generateDescription(context);
    });

    QFutureWatcher<QString> *watcher = new QFutureWatcher<QString>();
    connect(watcher, &QFutureWatcher<QString>::finished, this, [=]() {
        QString generatedDesc = watcher->result();

        showWaitingIndicator(false);

        startTypingEffect("Here's a generated research description based on your information:", "chat", "Assistant");
        QTimer::singleShot(2000, this, [=]() {
            startTypingEffect(generatedDesc, "chat", "Generated");
            QTimer::singleShot(generatedDesc.length() * 1, this, [=]() {
                startTypingEffect(generatedDesc, "description");
            });
        });

        watcher->deleteLater();
    });

    watcher->setFuture(future);
}

void AIAssistantWindow::on_clearChatButton_clicked()
{
    ui->chatDisplay->clear();

    if (chatbot) {
        chatbot->clearConversation();
        appendToChatDisplay("Assistant", "Conversation history cleared. How can I help with your research?");
    } else {
        appendToChatDisplay("System", "Please set your OpenAI API key to enable advanced AI features.");
    }
}

void AIAssistantWindow::on_applyButton_clicked()
{
    generatedDescription = ui->descriptionEdit->toPlainText();
    emit descriptionAccepted(generatedDescription);
    accept();
}

void AIAssistantWindow::on_closeButton_clicked()
{
    accept();
}

void AIAssistantWindow::appendToChatDisplay(const QString &speaker, const QString &message)
{
    QTextCursor cursor = ui->chatDisplay->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->chatDisplay->setTextCursor(cursor);

    QString formattedMessage;

    if (speaker == "You") {
        formattedMessage = "<div style='background-color:#E1F5FE; padding:8px; border-radius:5px; margin:5px;'>";
        formattedMessage += "<b>You:</b> " + message;
        formattedMessage += "</div>";
    } else if (speaker == "Assistant") {
        formattedMessage = "<div style='background-color:#F1F8E9; padding:8px; border-radius:5px; margin:5px;'>";
        formattedMessage += "<b>Research Assistant:</b> " + message;
        formattedMessage += "</div>";
    } else if (speaker == "Analysis" || speaker == "Generated") {
        formattedMessage = "<div style='background-color:#FFF9C4; padding:8px; border-radius:5px; margin:5px; border:1px dashed #FFB300;'>";
        formattedMessage += "<b>" + speaker + ":</b><br>" + message;
        formattedMessage += "</div>";
    } else {
        formattedMessage = "<div style='background-color:#E0E0E0; padding:8px; border-radius:5px; margin:5px;'>";
        formattedMessage += "<b>" + speaker + ":</b> " + message;
        formattedMessage += "</div>";
    }

    ui->chatDisplay->insertHtml(formattedMessage + "<br>");

    ui->chatDisplay->verticalScrollBar()->setValue(ui->chatDisplay->verticalScrollBar()->maximum());
}

void AIAssistantWindow::loadApiKey()
{
    QSettings settings("YourOrganization", "ResearchManagement");
    openaiApiKey = settings.value("openai_api_key", "").toString();
}

void AIAssistantWindow::saveApiKey(const QString &key)
{
    openaiApiKey = key;
    QSettings settings("YourOrganization", "ResearchManagement");
    settings.setValue("openai_api_key", key);
}

void AIAssistantWindow::on_apiKeyButton_clicked()
{
    bool ok;
    QString key = QInputDialog::getText(this, "GitHub Token",
                                        "Enter your GitHub token for Azure Inference API:\n"
                                        "(Create a token at https://github.com/settings/tokens)",
                                        QLineEdit::Normal,
                                        openaiApiKey, &ok);
    if (ok && !key.isEmpty()) {
        saveApiKey(key);
        if (chatbot) {
            delete chatbot;
        }

        setupChatbot();
    }
}

void AIAssistantWindow::setupChatbot()
{
    if (openaiApiKey.isEmpty()) {
        chatbot = nullptr;
        appendToChatDisplay("System", "Please set your GitHub token to enable advanced AI features.");
    } else {
        chatbot = new OpenAIChatBot(openaiApiKey);
        appendToChatDisplay("Assistant", "Hello! I'm your research assistant powered by GPT-4o via Azure. How can I help with your research today?");
    }
}

void AIAssistantWindow::ensureLoadingIndicator()
{
    // Force recreate the loading indicator
    static QLabel* waitingLabel = nullptr;
    static QMovie* loadingMovie = nullptr;

    if (waitingLabel) {
        delete waitingLabel;
        waitingLabel = nullptr;
    }
    if (loadingMovie) {
        loadingMovie->stop();
        delete loadingMovie;
        loadingMovie = nullptr;
    }
    waitingLabel = new QLabel(this);
    loadingMovie = new QMovie(":/new/prefix1/image/loading.gif");
    loadingMovie->setScaledSize(QSize(80, 80));
    waitingLabel->setMovie(loadingMovie);
    waitingLabel->setAlignment(Qt::AlignCenter);
    waitingLabel->setFixedSize(80, 80);
    waitingLabel->setStyleSheet("background: transparent; border: none;");
    waitingLabel->setParent(ui->chatDisplay);
    waitingLabel->move(
        (ui->chatDisplay->width() - waitingLabel->width()) / 2,
        (ui->chatDisplay->height() - waitingLabel->height()) / 2
        );
}

void AIAssistantWindow::showWaitingIndicator(bool show)
{
    static QLabel* waitingLabel = nullptr;
    static QMovie* loadingMovie = nullptr;

    if (show) {
        ensureLoadingIndicator();
        if (!waitingLabel) {
            waitingLabel = new QLabel(this);
            loadingMovie = new QMovie(":/new/prefix1/image/loading.gif");


            loadingMovie->setScaledSize(QSize(80, 80));

            waitingLabel->setMovie(loadingMovie);
            waitingLabel->setAlignment(Qt::AlignCenter);
            waitingLabel->setFixedSize(80, 80);

            waitingLabel->setStyleSheet("background: transparent; border: none;");

            waitingLabel->setParent(ui->chatDisplay);
        }


        waitingLabel->move(
            (ui->chatDisplay->width() - waitingLabel->width()) / 2,
            (ui->chatDisplay->height() - waitingLabel->height()) / 2
            );

        loadingMovie->start();
        waitingLabel->show();
        QScrollBar* scrollBar = ui->chatDisplay->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());

        QApplication::processEvents();
    } else if (waitingLabel) {
        loadingMovie->stop();
        waitingLabel->hide();
    }
}

void AIAssistantWindow::startTypingEffect(const QString &text, const QString &target, const QString &speaker)
{
    if (typingTimer->isActive()) {
        typingTimer->stop();
    }
    fullResponse = text;
    currentWords = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    currentWordIndex = 0;
    currentTarget = target;
    if (target == "chat") {
        QString formattedStart;
        if (speaker == "Assistant") {
            formattedStart = "<div id='current-message' style='background-color:#F1F8E9; padding:8px; border-radius:5px; margin:5px;'>";
            formattedStart += "<b>Research Assistant:</b> ";
        } else if (speaker == "Analysis") {
            formattedStart = "<div id='current-message' style='background-color:#FFF9C4; padding:8px; border-radius:5px; margin:5px; border:1px dashed #FFB300;'>";
            formattedStart += "<b>Analysis:</b><br>";
        } else if (speaker == "Generated") {
            formattedStart = "<div id='current-message' style='background-color:#FFF9C4; padding:8px; border-radius:5px; margin:5px; border:1px dashed #FFB300;'>";
            formattedStart += "<b>Generated:</b><br>";
        } else {
            formattedStart = "<div id='current-message' style='background-color:#E0E0E0; padding:8px; border-radius:5px; margin:5px;'>";
            formattedStart += "<b>" + speaker + ":</b> ";
        }
        QTextCursor cursor = ui->chatDisplay->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->chatDisplay->setTextCursor(cursor);
        ui->chatDisplay->insertHtml(formattedStart);
    } else if (target == "description") {
        ui->descriptionEdit->clear();
    }
    if (!currentWords.isEmpty()) {
        typingTimer->start(50);
    }
}

void AIAssistantWindow::typeNextWord()
{
    if (currentWordIndex < currentWords.size()) {
        QString word = currentWords[currentWordIndex] + " ";
        typingSound->play();

        if (currentTarget == "chat") {
            QTextCursor cursor = ui->chatDisplay->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->chatDisplay->setTextCursor(cursor);
            ui->chatDisplay->insertPlainText(word);
            ui->chatDisplay->verticalScrollBar()->setValue(ui->chatDisplay->verticalScrollBar()->maximum());
        } else if (currentTarget == "description") {
            ui->descriptionEdit->insertPlainText(word);
            QTextCursor cursor = ui->descriptionEdit->textCursor();
            ui->descriptionEdit->setTextCursor(cursor);
        }

        currentWordIndex++;
    } else {
        typingTimer->stop();
        if (typingSound->isPlaying()) {
            typingSound->stop();
        }

        if (currentTarget == "chat") {
            QTextCursor cursor = ui->chatDisplay->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->chatDisplay->setTextCursor(cursor);
            ui->chatDisplay->insertHtml("</div><br>");
            ui->chatDisplay->verticalScrollBar()->setValue(ui->chatDisplay->verticalScrollBar()->maximum());
        }
    }
}

void AIAssistantWindow::on_micButton_released()
{
    ui->chatInput->clear();
    ui->chatInput->setPlaceholderText("Starting speech recognition...");
    runPythonSpeechRecognition();
}


void AIAssistantWindow::addSimulatedWord()
{
    if (currentSimulatedWordIndex < simulatedWords.size()) {
        QString currentText = ui->chatInput->text();
        if (!currentText.isEmpty()) {
            currentText += " ";
        }
        currentText += simulatedWords[currentSimulatedWordIndex];
        ui->chatInput->setText(currentText);

        currentSimulatedWordIndex++;
    } else {
        voiceTypingTimer->stop();
    }
}

void AIAssistantWindow::runPythonSpeechRecognition()
{
    if (pythonProcess) {
        if (pythonProcess->state() == QProcess::Running) {
            pythonProcess->terminate();
            pythonProcess->waitForFinished(1000);
        }
        delete pythonProcess;
    }

    pythonProcess = new QProcess(this);
    connect(pythonProcess, &QProcess::readyReadStandardOutput, this, &AIAssistantWindow::handlePythonOutput);
    connect(pythonProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        qDebug() << "Python process error:" << error;
        ui->chatInput->setText("Error running speech recognition");
    });

    connect(pythonProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
                if (exitCode != 0 || exitStatus != QProcess::NormalExit) {
                    qDebug() << "Python process exited with code:" << exitCode;
                    ui->chatInput->clear();
                    ui->chatInput->setText("Speech recognition failed");
                }
            });
    pythonProcess->setWorkingDirectory("C:/Users/abida/Downloads/c++/projetRecherche");
    QStringList arguments;
    arguments << "speech_to_text.py";

    pythonProcess->start("python", arguments);

    if (!pythonProcess->waitForStarted(3000)) {
        qDebug() << "Failed to start Python process";
        ui->chatInput->clear();
        ui->chatInput->setText("Failed to start speech recognition");
    }
}

void AIAssistantWindow::handlePythonOutput()
{
    static QLabel* voiceAnimationLabel = nullptr;
    static QMovie* voiceAnimation = nullptr;
    if (!voiceAnimationLabel) {
        voiceAnimationLabel = new QLabel(this);
        voiceAnimation = new QMovie(":/new/prefix1/image/voice.gif");
        voiceAnimation->setScaledSize(QSize(80, 80));
        voiceAnimationLabel->setMovie(voiceAnimation);
        voiceAnimationLabel->setAlignment(Qt::AlignCenter);
        voiceAnimationLabel->setFixedSize(80, 80);
        voiceAnimationLabel->setStyleSheet("background: transparent; border: none;");
        voiceAnimationLabel->setParent(ui->chatDisplay);
    }
    voiceAnimationLabel->move(
        (ui->chatDisplay->width() - voiceAnimationLabel->width()) / 2,
        (ui->chatDisplay->height() - voiceAnimationLabel->height()) / 2
        );
    voiceAnimation->start();
    voiceAnimationLabel->show();
    QScrollBar* scrollBar = ui->chatDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
    QApplication::processEvents();
    if (!pythonProcess) return;
    QByteArray output = pythonProcess->readAllStandardOutput();
    QString recognizedText = QString::fromUtf8(output).trimmed();

    qDebug() << "Python output:" << recognizedText;

    if (recognizedText.startsWith("Listening...")) {
        ui->chatInput->clear();
        ui->chatInput->setPlaceholderText("Listening...");
    }
    else if (recognizedText.startsWith("Sorry,") ||
             recognizedText.startsWith("Listening timed out") ||
             recognizedText.startsWith("Could not request")) {
        ui->chatInput->clear();
        ui->chatInput->setPlaceholderText(recognizedText);
    } else {
        ui->chatInput->clear();
        simulatedWords = recognizedText.split(' ', Qt::SkipEmptyParts);
        currentSimulatedWordIndex = 0;

        if (voiceTypingTimer) {
            delete voiceTypingTimer;
        }

        voiceTypingTimer = new QTimer(this);
        connect(voiceTypingTimer, &QTimer::timeout, this, &AIAssistantWindow::addSimulatedWord);
        voiceTypingTimer->start(100);
    }
    if (voiceAnimation) {
        voiceAnimation->stop();
    }
    if (voiceAnimationLabel) {
        voiceAnimationLabel->hide();
    }
}
