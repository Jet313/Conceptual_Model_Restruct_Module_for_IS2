/********************************************************************************
** Form generated from reading UI file 'module_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULE_FORM_H
#define UI_MODULE_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *specTab;
    QWidget *structTablesTab;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_7;
    QVBoxLayout *tableVLayout;
    QGridLayout *gridLayout_9;
    QPushButton *deleteTablesButt;
    QPushButton *createTablesButt;
    QSpacerItem *horizontalSpacer_2;
    QLabel *notificationLabel;
    QWidget *fullTableTab;
    QGridLayout *gridLayout_16;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_17;
    QTableView *fullTableView;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QLabel *fullLable;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_21;
    QGridLayout *gridLayout_18;
    QPushButton *oneIterButt;
    QLabel *iterationLable;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *allIterButt;
    QLabel *label;
    QWidget *expandedTableTab;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_5;
    QGridLayout *gridLayout_20;
    QLabel *expandedLable;
    QTableView *expandedTableView;
    QSpacerItem *verticalSpacer_24;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QWidget *optimizedTableTab;
    QGridLayout *gridLayout_14;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QGridLayout *gridLayout_19;
    QSpacerItem *horizontalSpacer_6;
    QTableView *optiTableView;
    QSpacerItem *verticalSpacer_23;
    QLabel *optiLable;
    QWidget *tab_4;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QTableView *S1Table;
    QTableView *S1Header;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer;
    QWidget *s2tab;
    QVBoxLayout *verticalLayout_2;
    QTableView *S2Header;
    QTableView *S2Table;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_3;
    QTableView *SHeader;
    QTableView *STable;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_4;
    QTableView *FHeader;
    QTableView *FTable;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(854, 736);
        gridLayout_3 = new QGridLayout(Form);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        specTab = new QTabWidget(Form);
        specTab->setObjectName(QString::fromUtf8("specTab"));
        QFont font;
        font.setPointSize(12);
        specTab->setFont(font);
        structTablesTab = new QWidget();
        structTablesTab->setObjectName(QString::fromUtf8("structTablesTab"));
        gridLayout_4 = new QGridLayout(structTablesTab);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        scrollArea = new QScrollArea(structTablesTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 810, 631));
        gridLayout_7 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        tableVLayout = new QVBoxLayout();
        tableVLayout->setObjectName(QString::fromUtf8("tableVLayout"));

        gridLayout_7->addLayout(tableVLayout, 1, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 1, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        deleteTablesButt = new QPushButton(structTablesTab);
        deleteTablesButt->setObjectName(QString::fromUtf8("deleteTablesButt"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deleteTablesButt->sizePolicy().hasHeightForWidth());
        deleteTablesButt->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(deleteTablesButt, 1, 1, 1, 1);

        createTablesButt = new QPushButton(structTablesTab);
        createTablesButt->setObjectName(QString::fromUtf8("createTablesButt"));

        gridLayout_9->addWidget(createTablesButt, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        notificationLabel = new QLabel(structTablesTab);
        notificationLabel->setObjectName(QString::fromUtf8("notificationLabel"));
        notificationLabel->setEnabled(false);

        gridLayout_9->addWidget(notificationLabel, 1, 4, 1, 1);


        gridLayout_4->addLayout(gridLayout_9, 0, 0, 1, 1);

        specTab->addTab(structTablesTab, QString());
        fullTableTab = new QWidget();
        fullTableTab->setObjectName(QString::fromUtf8("fullTableTab"));
        gridLayout_16 = new QGridLayout(fullTableTab);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        scrollArea_2 = new QScrollArea(fullTableTab);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 810, 631));
        gridLayout_17 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        fullTableView = new QTableView(scrollAreaWidgetContents_2);
        fullTableView->setObjectName(QString::fromUtf8("fullTableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fullTableView->sizePolicy().hasHeightForWidth());
        fullTableView->setSizePolicy(sizePolicy1);
        fullTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fullTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fullTableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        fullTableView->horizontalHeader()->setVisible(false);
        fullTableView->verticalHeader()->setVisible(false);

        gridLayout_17->addWidget(fullTableView, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_17->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_17->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        fullLable = new QLabel(scrollAreaWidgetContents_2);
        fullLable->setObjectName(QString::fromUtf8("fullLable"));

        gridLayout_17->addWidget(fullLable, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_17->addItem(verticalSpacer_5, 0, 2, 1, 1);

        verticalSpacer_21 = new QSpacerItem(20, 185, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_17->addItem(verticalSpacer_21, 2, 2, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_16->addWidget(scrollArea_2, 7, 0, 1, 1);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        oneIterButt = new QPushButton(fullTableTab);
        oneIterButt->setObjectName(QString::fromUtf8("oneIterButt"));

        gridLayout_18->addWidget(oneIterButt, 1, 0, 1, 1);

        iterationLable = new QLabel(fullTableTab);
        iterationLable->setObjectName(QString::fromUtf8("iterationLable"));

        gridLayout_18->addWidget(iterationLable, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        allIterButt = new QPushButton(fullTableTab);
        allIterButt->setObjectName(QString::fromUtf8("allIterButt"));

        gridLayout_18->addWidget(allIterButt, 1, 1, 1, 1);

        label = new QLabel(fullTableTab);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_18->addWidget(label, 1, 4, 1, 1);


        gridLayout_16->addLayout(gridLayout_18, 2, 0, 1, 1);

        specTab->addTab(fullTableTab, QString());
        expandedTableTab = new QWidget();
        expandedTableTab->setObjectName(QString::fromUtf8("expandedTableTab"));
        gridLayout = new QGridLayout(expandedTableTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea_5 = new QScrollArea(expandedTableTab);
        scrollArea_5->setObjectName(QString::fromUtf8("scrollArea_5"));
        scrollArea_5->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_5->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 810, 666));
        gridLayout_20 = new QGridLayout(scrollAreaWidgetContents_5);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        expandedLable = new QLabel(scrollAreaWidgetContents_5);
        expandedLable->setObjectName(QString::fromUtf8("expandedLable"));

        gridLayout_20->addWidget(expandedLable, 1, 1, 1, 1);

        expandedTableView = new QTableView(scrollAreaWidgetContents_5);
        expandedTableView->setObjectName(QString::fromUtf8("expandedTableView"));
        sizePolicy1.setHeightForWidth(expandedTableView->sizePolicy().hasHeightForWidth());
        expandedTableView->setSizePolicy(sizePolicy1);
        expandedTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        expandedTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        expandedTableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        expandedTableView->horizontalHeader()->setVisible(false);
        expandedTableView->verticalHeader()->setVisible(false);

        gridLayout_20->addWidget(expandedTableView, 1, 2, 1, 1);

        verticalSpacer_24 = new QSpacerItem(20, 185, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_20->addItem(verticalSpacer_24, 2, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_8, 1, 3, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_20->addItem(verticalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        scrollArea_5->setWidget(scrollAreaWidgetContents_5);

        gridLayout->addWidget(scrollArea_5, 0, 0, 1, 1);

        specTab->addTab(expandedTableTab, QString());
        optimizedTableTab = new QWidget();
        optimizedTableTab->setObjectName(QString::fromUtf8("optimizedTableTab"));
        gridLayout_14 = new QGridLayout(optimizedTableTab);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        scrollArea_4 = new QScrollArea(optimizedTableTab);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 810, 666));
        gridLayout_19 = new QGridLayout(scrollAreaWidgetContents_4);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_19->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        optiTableView = new QTableView(scrollAreaWidgetContents_4);
        optiTableView->setObjectName(QString::fromUtf8("optiTableView"));
        sizePolicy1.setHeightForWidth(optiTableView->sizePolicy().hasHeightForWidth());
        optiTableView->setSizePolicy(sizePolicy1);
        optiTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        optiTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        optiTableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        optiTableView->horizontalHeader()->setVisible(false);
        optiTableView->verticalHeader()->setVisible(false);

        gridLayout_19->addWidget(optiTableView, 0, 1, 1, 1);

        verticalSpacer_23 = new QSpacerItem(20, 185, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_19->addItem(verticalSpacer_23, 1, 0, 1, 1);

        optiLable = new QLabel(scrollAreaWidgetContents_4);
        optiLable->setObjectName(QString::fromUtf8("optiLable"));

        gridLayout_19->addWidget(optiLable, 0, 0, 1, 1);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        gridLayout_14->addWidget(scrollArea_4, 0, 0, 1, 1);

        specTab->addTab(optimizedTableTab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_2 = new QGridLayout(tab_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget_2 = new QTabWidget(tab_4);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        S1Table = new QTableView(tab);
        S1Table->setObjectName(QString::fromUtf8("S1Table"));
        sizePolicy1.setHeightForWidth(S1Table->sizePolicy().hasHeightForWidth());
        S1Table->setSizePolicy(sizePolicy1);
        S1Table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        S1Table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        S1Table->setCornerButtonEnabled(false);
        S1Table->horizontalHeader()->setVisible(false);
        S1Table->verticalHeader()->setVisible(false);

        gridLayout_5->addWidget(S1Table, 1, 0, 1, 1);

        S1Header = new QTableView(tab);
        S1Header->setObjectName(QString::fromUtf8("S1Header"));
        sizePolicy1.setHeightForWidth(S1Header->sizePolicy().hasHeightForWidth());
        S1Header->setSizePolicy(sizePolicy1);
        S1Header->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        S1Header->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        S1Header->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        S1Header->horizontalHeader()->setVisible(false);
        S1Header->verticalHeader()->setVisible(false);

        gridLayout_5->addWidget(S1Header, 0, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_9, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 461, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 3, 0, 1, 1);

        tabWidget_2->addTab(tab, QString());
        s2tab = new QWidget();
        s2tab->setObjectName(QString::fromUtf8("s2tab"));
        verticalLayout_2 = new QVBoxLayout(s2tab);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        S2Header = new QTableView(s2tab);
        S2Header->setObjectName(QString::fromUtf8("S2Header"));
        sizePolicy1.setHeightForWidth(S2Header->sizePolicy().hasHeightForWidth());
        S2Header->setSizePolicy(sizePolicy1);
        S2Header->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_2->addWidget(S2Header);

        S2Table = new QTableView(s2tab);
        S2Table->setObjectName(QString::fromUtf8("S2Table"));
        sizePolicy1.setHeightForWidth(S2Table->sizePolicy().hasHeightForWidth());
        S2Table->setSizePolicy(sizePolicy1);
        S2Table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        S2Table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        S2Table->setCornerButtonEnabled(false);

        verticalLayout_2->addWidget(S2Table);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabWidget_2->addTab(s2tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_3 = new QVBoxLayout(tab_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        SHeader = new QTableView(tab_5);
        SHeader->setObjectName(QString::fromUtf8("SHeader"));
        sizePolicy1.setHeightForWidth(SHeader->sizePolicy().hasHeightForWidth());
        SHeader->setSizePolicy(sizePolicy1);
        SHeader->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_3->addWidget(SHeader);

        STable = new QTableView(tab_5);
        STable->setObjectName(QString::fromUtf8("STable"));
        sizePolicy1.setHeightForWidth(STable->sizePolicy().hasHeightForWidth());
        STable->setSizePolicy(sizePolicy1);
        STable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        STable->setCornerButtonEnabled(false);

        verticalLayout_3->addWidget(STable);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_4 = new QVBoxLayout(tab_6);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        FHeader = new QTableView(tab_6);
        FHeader->setObjectName(QString::fromUtf8("FHeader"));

        verticalLayout_4->addWidget(FHeader);

        FTable = new QTableView(tab_6);
        FTable->setObjectName(QString::fromUtf8("FTable"));
        FTable->setCornerButtonEnabled(false);

        verticalLayout_4->addWidget(FTable);

        textBrowser = new QTextBrowser(tab_6);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_4->addWidget(textBrowser);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        tabWidget_2->addTab(tab_6, QString());

        gridLayout_2->addWidget(tabWidget_2, 0, 0, 1, 1);

        specTab->addTab(tab_4, QString());

        gridLayout_3->addWidget(specTab, 0, 0, 1, 1);


        retranslateUi(Form);

        specTab->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        deleteTablesButt->setText(QCoreApplication::translate("Form", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", nullptr));
        createTablesButt->setText(QCoreApplication::translate("Form", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", nullptr));
        notificationLabel->setText(QCoreApplication::translate("Form", "\320\222\320\276\320\267\320\274\320\276\320\266\320\275\320\276, \320\277\321\200\320\276\320\265\320\272\321\202 \320\261\321\213\320\273 \320\270\320\267\320\274\320\265\320\275\320\265\320\275. \320\235\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \320\276\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213!", nullptr));
        specTab->setTabText(specTab->indexOf(structTablesTab), QCoreApplication::translate("Form", "\320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\275\320\276\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        fullLable->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        oneIterButt->setText(QCoreApplication::translate("Form", "\320\236\320\264\320\275\320\260 \320\270\321\202\320\265\321\200\320\260\321\206\320\270\321\217", nullptr));
        iterationLable->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        allIterButt->setText(QCoreApplication::translate("Form", "\320\222\321\201\320\265 \320\270\321\202\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        label->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        specTab->setTabText(specTab->indexOf(fullTableTab), QCoreApplication::translate("Form", "\320\237\320\276\320\273\320\275\320\276\320\265 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\275\320\276\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        expandedLable->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        specTab->setTabText(specTab->indexOf(expandedTableTab), QCoreApplication::translate("Form", "\320\240\320\260\321\201\321\210\320\270\321\200\320\265\320\275\320\275\320\276\320\265 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\275\320\276\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        optiLable->setText(QCoreApplication::translate("Form", "TextLabel", nullptr));
        specTab->setTabText(specTab->indexOf(optimizedTableTab), QCoreApplication::translate("Form", "\320\236\320\277\321\202\320\270\320\274\320\260\320\273\321\214\320\275\320\276\320\265 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\275\320\276\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QCoreApplication::translate("Form", "\320\244\320\276\321\200\320\274\320\260 S1", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(s2tab), QCoreApplication::translate("Form", "\320\244\320\276\321\200\320\274\320\260 S2", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("Form", "\320\244\320\276\321\200\320\274\320\260 S", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("Form", "\320\244\320\276\321\200\320\274\320\260 F", nullptr));
        specTab->setTabText(specTab->indexOf(tab_4), QCoreApplication::translate("Form", "\320\241\320\277\320\265\321\206\320\270\321\204\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULE_FORM_H
