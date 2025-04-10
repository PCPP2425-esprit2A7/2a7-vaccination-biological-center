#include "AIAssistantWindow.h"
#include "ui_AIAssistantWindow.h"
#include <QSettings>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QMovie>
#include <QScrollBar>

AIAssistantWindow::AIAssistantWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AIAssistantWindow),
    chatbot(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("AI Research Assistant");
    resize(800, 600);
    loadApiKey();
    setupChatbot();
    connect(ui->chatInput, &QLineEdit::returnPressed, this, &AIAssistantWindow::on_sendButton_clicked);
}

AIAssistantWindow::~AIAssistantWindow()
{
    if (chatbot) {
        delete chatbot;
        chatbot = nullptr;
    }
    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
    delete ui;
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

        appendToChatDisplay("Assistant", response);

        if (response.length() > 150 && (
                userInput.contains("generate", Qt::CaseInsensitive) ||
                userInput.contains("description", Qt::CaseInsensitive) ||
                userInput.contains("create", Qt::CaseInsensitive) ||
                userInput.contains("write", Qt::CaseInsensitive)))
        {
            ui->descriptionEdit->setPlainText(response);
            appendToChatDisplay("System", "The generated text has been added to the description field below.");
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
        appendToChatDisplay("Assistant", "Here's my analysis of your research description:");
        appendToChatDisplay("Analysis", analysis);

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

        appendToChatDisplay("Assistant", "Here's a generated research description based on your information:");
        appendToChatDisplay("Generated", generatedDesc);
        ui->descriptionEdit->setPlainText(generatedDesc);

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

void AIAssistantWindow::showWaitingIndicator(bool show)
{
    static QLabel* waitingLabel = nullptr;
    static QMovie* loadingMovie = nullptr;

    if (show) {
        if (!waitingLabel) {
            waitingLabel = new QLabel(this);
            loadingMovie = new QMovie(":/images/loading.gif");
            waitingLabel->setMovie(loadingMovie);
            waitingLabel->setAlignment(Qt::AlignCenter);
            waitingLabel->setFixedSize(50, 50);
            waitingLabel->setParent(ui->chatDisplay);
            waitingLabel->move(
                (ui->chatDisplay->width() - waitingLabel->width()) / 2,
                (ui->chatDisplay->height() - waitingLabel->height()) / 2
                );
        }

        loadingMovie->start();
        waitingLabel->show();
        QApplication::processEvents();
    } else if (waitingLabel) {
        loadingMovie->stop();
        waitingLabel->hide();
    }
}
