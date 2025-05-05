/********************************************************************************
** Form generated from reading UI file 'AIAssistantWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIASSISTANTWINDOW_H
#define UI_AIASSISTANTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AIAssistantWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *leftPanel;
    QVBoxLayout *verticalLayout;
    QLabel *logo;
    QLabel *titleLabel;
    QPushButton *analyzeButton;
    QPushButton *generateButton;
    QPushButton *clearChatButton;
    QPushButton *apiKeyButton;
    QPushButton *closeButton;
    QWidget *mainContent;
    QVBoxLayout *verticalLayout_2;
    QLabel *headerLabel;
    QHBoxLayout *contentLayout;
    QGroupBox *chatGroup;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *chatDisplay;
    QHBoxLayout *inputLayout;
    QLineEdit *chatInput;
    QPushButton *micButton;
    QPushButton *sendButton;
    QGroupBox *descriptionGroup;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *descriptionEdit;
    QPushButton *applyButton;

    void setupUi(QDialog *AIAssistantWindow)
    {
        if (AIAssistantWindow->objectName().isEmpty())
            AIAssistantWindow->setObjectName("AIAssistantWindow");
        AIAssistantWindow->resize(1200, 700);
        horizontalLayout = new QHBoxLayout(AIAssistantWindow);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftPanel = new QGroupBox(AIAssistantWindow);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setMaximumSize(QSize(220, 16777215));
        leftPanel->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);"));
        verticalLayout = new QVBoxLayout(leftPanel);
        verticalLayout->setObjectName("verticalLayout");
        logo = new QLabel(leftPanel);
        logo->setObjectName("logo");
        logo->setMinimumSize(QSize(0, 150));
        logo->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/Adobe Express - file (5).png);"));
        logo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(logo);

        titleLabel = new QLabel(leftPanel);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(15);
        font.setWeight(QFont::Black);
        font.setItalic(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);\n"
"font: 900 italic 15pt \"Segoe UI\";"));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        analyzeButton = new QPushButton(leftPanel);
        analyzeButton->setObjectName("analyzeButton");
        analyzeButton->setMinimumSize(QSize(0, 51));
        analyzeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        verticalLayout->addWidget(analyzeButton);

        generateButton = new QPushButton(leftPanel);
        generateButton->setObjectName("generateButton");
        generateButton->setMinimumSize(QSize(0, 51));
        generateButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        verticalLayout->addWidget(generateButton);

        clearChatButton = new QPushButton(leftPanel);
        clearChatButton->setObjectName("clearChatButton");
        clearChatButton->setMinimumSize(QSize(0, 51));
        clearChatButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        verticalLayout->addWidget(clearChatButton);

        apiKeyButton = new QPushButton(leftPanel);
        apiKeyButton->setObjectName("apiKeyButton");
        apiKeyButton->setMinimumSize(QSize(0, 51));
        apiKeyButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        verticalLayout->addWidget(apiKeyButton);

        closeButton = new QPushButton(leftPanel);
        closeButton->setObjectName("closeButton");
        closeButton->setMinimumSize(QSize(0, 51));
        closeButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#226597;\n"
"color:white"));

        verticalLayout->addWidget(closeButton);


        horizontalLayout->addWidget(leftPanel);

        mainContent = new QWidget(AIAssistantWindow);
        mainContent->setObjectName("mainContent");
        mainContent->setStyleSheet(QString::fromUtf8("background-color: rgb(243, 249, 251);"));
        verticalLayout_2 = new QVBoxLayout(mainContent);
        verticalLayout_2->setObjectName("verticalLayout_2");
        headerLabel = new QLabel(mainContent);
        headerLabel->setObjectName("headerLabel");
        headerLabel->setMinimumSize(QSize(0, 100));
        headerLabel->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(true);
        headerLabel->setFont(font1);
        headerLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(17, 60, 103);\n"
"color: rgb(255, 255, 255);"));
        headerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(headerLabel);

        contentLayout = new QHBoxLayout();
        contentLayout->setObjectName("contentLayout");
        chatGroup = new QGroupBox(mainContent);
        chatGroup->setObjectName("chatGroup");
        chatGroup->setFont(font1);
        chatGroup->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        verticalLayout_3 = new QVBoxLayout(chatGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        chatDisplay = new QTextEdit(chatGroup);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));
        chatDisplay->setReadOnly(true);

        verticalLayout_3->addWidget(chatDisplay);

        inputLayout = new QHBoxLayout();
        inputLayout->setObjectName("inputLayout");
        chatInput = new QLineEdit(chatGroup);
        chatInput->setObjectName("chatInput");
        chatInput->setMinimumSize(QSize(0, 40));
        chatInput->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));

        inputLayout->addWidget(chatInput);

        micButton = new QPushButton(chatGroup);
        micButton->setObjectName("micButton");
        micButton->setMaximumSize(QSize(80, 80));
        micButton->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/mic.png);\n"
"background: transparent; \n"
"border: none;"));

        inputLayout->addWidget(micButton);

        sendButton = new QPushButton(chatGroup);
        sendButton->setObjectName("sendButton");
        sendButton->setMinimumSize(QSize(55, 40));
        sendButton->setMaximumSize(QSize(100, 40));
        sendButton->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image/send.png);\n"
"background: transparent; \n"
"border: none;"));

        inputLayout->addWidget(sendButton);


        verticalLayout_3->addLayout(inputLayout);


        contentLayout->addWidget(chatGroup);

        descriptionGroup = new QGroupBox(mainContent);
        descriptionGroup->setObjectName("descriptionGroup");
        descriptionGroup->setMaximumSize(QSize(300, 16777215));
        descriptionGroup->setFont(font1);
        descriptionGroup->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        verticalLayout_4 = new QVBoxLayout(descriptionGroup);
        verticalLayout_4->setObjectName("verticalLayout_4");
        descriptionEdit = new QTextEdit(descriptionGroup);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid black;\n"
"border-radius:10px;"));

        verticalLayout_4->addWidget(descriptionEdit);

        applyButton = new QPushButton(descriptionGroup);
        applyButton->setObjectName("applyButton");
        applyButton->setMinimumSize(QSize(0, 40));
        applyButton->setStyleSheet(QString::fromUtf8("border:1px solid white;\n"
"border-radius:20px;\n"
"background-color:#030C54;\n"
"color:white"));

        verticalLayout_4->addWidget(applyButton);


        contentLayout->addWidget(descriptionGroup);


        verticalLayout_2->addLayout(contentLayout);


        horizontalLayout->addWidget(mainContent);


        retranslateUi(AIAssistantWindow);

        QMetaObject::connectSlotsByName(AIAssistantWindow);
    } // setupUi

    void retranslateUi(QDialog *AIAssistantWindow)
    {
        AIAssistantWindow->setWindowTitle(QCoreApplication::translate("AIAssistantWindow", "AI Research Assistant", nullptr));
        leftPanel->setTitle(QString());
        logo->setText(QString());
        titleLabel->setText(QCoreApplication::translate("AIAssistantWindow", "AI Assistant", nullptr));
        analyzeButton->setText(QCoreApplication::translate("AIAssistantWindow", "Analyze Description", nullptr));
        generateButton->setText(QCoreApplication::translate("AIAssistantWindow", "Generate Description", nullptr));
        clearChatButton->setText(QCoreApplication::translate("AIAssistantWindow", "Clear Chat", nullptr));
        apiKeyButton->setText(QCoreApplication::translate("AIAssistantWindow", "Set API Key", nullptr));
        closeButton->setText(QCoreApplication::translate("AIAssistantWindow", "Close", nullptr));
        headerLabel->setText(QCoreApplication::translate("AIAssistantWindow", "Bio Med AI Research Assistant", nullptr));
        chatGroup->setTitle(QCoreApplication::translate("AIAssistantWindow", "Chat with Research Assistant", nullptr));
        chatInput->setPlaceholderText(QCoreApplication::translate("AIAssistantWindow", "Type your message here...", nullptr));
        micButton->setText(QString());
        sendButton->setText(QString());
        descriptionGroup->setTitle(QCoreApplication::translate("AIAssistantWindow", "Generated Description", nullptr));
        applyButton->setText(QCoreApplication::translate("AIAssistantWindow", "Apply Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AIAssistantWindow: public Ui_AIAssistantWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIASSISTANTWINDOW_H
