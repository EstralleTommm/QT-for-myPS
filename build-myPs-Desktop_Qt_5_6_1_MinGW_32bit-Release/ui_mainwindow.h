/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *new_2;
    QAction *open;
    QAction *save;
    QAction *saveAs;
    QAction *close;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_11;
    QAction *action_12;
    QAction *action_13;
    QAction *action_20;
    QAction *action_21;
    QAction *action_22;
    QAction *action_23;
    QAction *action_24;
    QAction *action_25;
    QAction *action_26;
    QAction *action_27;
    QAction *action_28;
    QAction *action_29;
    QAction *action_30;
    QAction *action_32;
    QAction *action_33;
    QAction *action_34;
    QAction *action_35;
    QAction *action_36;
    QAction *action_39;
    QAction *action_40;
    QAction *action_41;
    QAction *actionSobel;
    QAction *actionLaplacian;
    QAction *actionCanny;
    QAction *action_42;
    QAction *action_43;
    QAction *action_44;
    QAction *action_45;
    QAction *action_46;
    QAction *action_47;
    QAction *action_48;
    QAction *actionR;
    QAction *actionG;
    QAction *actionB;
    QAction *actionH;
    QAction *actionS;
    QAction *actionV;
    QAction *actionY;
    QAction *actionU;
    QAction *actionV_2;
    QAction *actionH_2;
    QAction *actionL;
    QAction *actionS_2;
    QAction *action_49;
    QAction *action_50;
    QAction *action_10;
    QAction *action;
    QAction *action_2;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_9;
    QMenu *menu_10;
    QMenu *menu_11;
    QMenu *menu_5;
    QMenu *menu_12;
    QMenu *menu_7;
    QMenu *menuRGB;
    QMenu *menu_8;
    QMenu *menu_13;
    QMenu *menu_14;
    QMenu *menu_15;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1143, 908);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setSizeIncrement(QSize(0, 0));
        MainWindow->setBaseSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/Image/icon/myico.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        new_2 = new QAction(MainWindow);
        new_2->setObjectName(QStringLiteral("new_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/Image/file/New.png"), QSize(), QIcon::Normal, QIcon::Off);
        new_2->setIcon(icon1);
        open = new QAction(MainWindow);
        open->setObjectName(QStringLiteral("open"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/Image/file/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        open->setIcon(icon2);
        save = new QAction(MainWindow);
        save->setObjectName(QStringLiteral("save"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/Image/file/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        save->setIcon(icon3);
        saveAs = new QAction(MainWindow);
        saveAs->setObjectName(QStringLiteral("saveAs"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/Image/file/SaveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveAs->setIcon(icon4);
        close = new QAction(MainWindow);
        close->setObjectName(QStringLiteral("close"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/Image/file/Close.png"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon5);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/Image/edit/Edit_Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_3->setIcon(icon6);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/Image/edit/Edit_Resume.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_4->setIcon(icon7);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/Image/edit/Edit_Full.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_5->setIcon(icon8);
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/Image/edit/Edit_Max.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_6->setIcon(icon9);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/Image/view/Check.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_7->setIcon(icon10);
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QStringLiteral("action_8"));
        action_8->setIcon(icon10);
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QStringLiteral("action_9"));
        action_9->setIcon(icon10);
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QStringLiteral("action_11"));
        action_11->setIcon(icon10);
        action_12 = new QAction(MainWindow);
        action_12->setObjectName(QStringLiteral("action_12"));
        action_12->setIcon(icon10);
        action_13 = new QAction(MainWindow);
        action_13->setObjectName(QStringLiteral("action_13"));
        action_13->setIcon(icon10);
        action_20 = new QAction(MainWindow);
        action_20->setObjectName(QStringLiteral("action_20"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/Image/geom/Geom_Enlarge.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_20->setIcon(icon11);
        action_21 = new QAction(MainWindow);
        action_21->setObjectName(QStringLiteral("action_21"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/Image/geom/Geom_Reduce.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_21->setIcon(icon12);
        action_22 = new QAction(MainWindow);
        action_22->setObjectName(QStringLiteral("action_22"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/new/Image/geom/Geom_RotateRight.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_22->setIcon(icon13);
        action_23 = new QAction(MainWindow);
        action_23->setObjectName(QStringLiteral("action_23"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/new/Image/geom/Geom_RotateLeft.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_23->setIcon(icon14);
        action_24 = new QAction(MainWindow);
        action_24->setObjectName(QStringLiteral("action_24"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/new/Image/geom/Geom_RotateCenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_24->setIcon(icon15);
        action_25 = new QAction(MainWindow);
        action_25->setObjectName(QStringLiteral("action_25"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/new/Image/geom/Geom_FlipX.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_25->setIcon(icon16);
        action_26 = new QAction(MainWindow);
        action_26->setObjectName(QStringLiteral("action_26"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/new/Image/geom/Geom_FlipY.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_26->setIcon(icon17);
        action_27 = new QAction(MainWindow);
        action_27->setObjectName(QStringLiteral("action_27"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/new/Image/gray/Gray_Bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_27->setIcon(icon18);
        action_28 = new QAction(MainWindow);
        action_28->setObjectName(QStringLiteral("action_28"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/new/Image/gray/Gray_Gray.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_28->setIcon(icon19);
        action_29 = new QAction(MainWindow);
        action_29->setObjectName(QStringLiteral("action_29"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/new/Image/gray/Gray_Reverse.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_29->setIcon(icon20);
        action_30 = new QAction(MainWindow);
        action_30->setObjectName(QStringLiteral("action_30"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/new/Image/gray/Gray_Linear.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_30->setIcon(icon21);
        action_32 = new QAction(MainWindow);
        action_32->setObjectName(QStringLiteral("action_32"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/new/Image/gray/Gray_Log.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_32->setIcon(icon22);
        action_33 = new QAction(MainWindow);
        action_33->setObjectName(QStringLiteral("action_33"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/new/Image/gray/Gray_Gamma.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_33->setIcon(icon23);
        action_34 = new QAction(MainWindow);
        action_34->setObjectName(QStringLiteral("action_34"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/new/Image/gray/Gray_Histeq.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_34->setIcon(icon24);
        action_35 = new QAction(MainWindow);
        action_35->setObjectName(QStringLiteral("action_35"));
        action_36 = new QAction(MainWindow);
        action_36->setObjectName(QStringLiteral("action_36"));
        action_39 = new QAction(MainWindow);
        action_39->setObjectName(QStringLiteral("action_39"));
        action_40 = new QAction(MainWindow);
        action_40->setObjectName(QStringLiteral("action_40"));
        action_41 = new QAction(MainWindow);
        action_41->setObjectName(QStringLiteral("action_41"));
        actionSobel = new QAction(MainWindow);
        actionSobel->setObjectName(QStringLiteral("actionSobel"));
        actionLaplacian = new QAction(MainWindow);
        actionLaplacian->setObjectName(QStringLiteral("actionLaplacian"));
        actionCanny = new QAction(MainWindow);
        actionCanny->setObjectName(QStringLiteral("actionCanny"));
        action_42 = new QAction(MainWindow);
        action_42->setObjectName(QStringLiteral("action_42"));
        action_43 = new QAction(MainWindow);
        action_43->setObjectName(QStringLiteral("action_43"));
        action_44 = new QAction(MainWindow);
        action_44->setObjectName(QStringLiteral("action_44"));
        action_45 = new QAction(MainWindow);
        action_45->setObjectName(QStringLiteral("action_45"));
        action_46 = new QAction(MainWindow);
        action_46->setObjectName(QStringLiteral("action_46"));
        action_47 = new QAction(MainWindow);
        action_47->setObjectName(QStringLiteral("action_47"));
        action_48 = new QAction(MainWindow);
        action_48->setObjectName(QStringLiteral("action_48"));
        actionR = new QAction(MainWindow);
        actionR->setObjectName(QStringLiteral("actionR"));
        actionG = new QAction(MainWindow);
        actionG->setObjectName(QStringLiteral("actionG"));
        actionB = new QAction(MainWindow);
        actionB->setObjectName(QStringLiteral("actionB"));
        actionH = new QAction(MainWindow);
        actionH->setObjectName(QStringLiteral("actionH"));
        actionS = new QAction(MainWindow);
        actionS->setObjectName(QStringLiteral("actionS"));
        actionV = new QAction(MainWindow);
        actionV->setObjectName(QStringLiteral("actionV"));
        actionY = new QAction(MainWindow);
        actionY->setObjectName(QStringLiteral("actionY"));
        actionU = new QAction(MainWindow);
        actionU->setObjectName(QStringLiteral("actionU"));
        actionV_2 = new QAction(MainWindow);
        actionV_2->setObjectName(QStringLiteral("actionV_2"));
        actionH_2 = new QAction(MainWindow);
        actionH_2->setObjectName(QStringLiteral("actionH_2"));
        actionL = new QAction(MainWindow);
        actionL->setObjectName(QStringLiteral("actionL"));
        actionS_2 = new QAction(MainWindow);
        actionS_2->setObjectName(QStringLiteral("actionS_2"));
        action_49 = new QAction(MainWindow);
        action_49->setObjectName(QStringLiteral("action_49"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/new/Image/help/Help_Info.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_49->setIcon(icon25);
        action_50 = new QAction(MainWindow);
        action_50->setObjectName(QStringLiteral("action_50"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/new/Image/edit/Edit_Option.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_50->setIcon(icon26);
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QStringLiteral("action_10"));
        action_10->setIcon(icon10);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1143, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_9 = new QMenu(menu_4);
        menu_9->setObjectName(QStringLiteral("menu_9"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/new/Image/geom/Geom_EnlargeReduce.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu_9->setIcon(icon27);
        menu_10 = new QMenu(menu_4);
        menu_10->setObjectName(QStringLiteral("menu_10"));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/new/Image/geom/Geom_Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu_10->setIcon(icon28);
        menu_11 = new QMenu(menu_4);
        menu_11->setObjectName(QStringLiteral("menu_11"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/new/Image/geom/Geom_Flip.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu_11->setIcon(icon29);
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        menu_12 = new QMenu(menu_5);
        menu_12->setObjectName(QStringLiteral("menu_12"));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/new/Image/gray/Gray_Nolinear.png"), QSize(), QIcon::Normal, QIcon::Off);
        menu_12->setIcon(icon30);
        menu_7 = new QMenu(menuBar);
        menu_7->setObjectName(QStringLiteral("menu_7"));
        menuRGB = new QMenu(menu_7);
        menuRGB->setObjectName(QStringLiteral("menuRGB"));
        menu_8 = new QMenu(menuBar);
        menu_8->setObjectName(QStringLiteral("menu_8"));
        menu_13 = new QMenu(menuBar);
        menu_13->setObjectName(QStringLiteral("menu_13"));
        menu_14 = new QMenu(menu_13);
        menu_14->setObjectName(QStringLiteral("menu_14"));
        menu_15 = new QMenu(menu_13);
        menu_15->setObjectName(QStringLiteral("menu_15"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu_13->menuAction());
        menuBar->addAction(menu_7->menuAction());
        menuBar->addAction(menu_8->menuAction());
        menu->addAction(new_2);
        menu->addAction(open);
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(save);
        menu->addAction(saveAs);
        menu->addSeparator();
        menu->addAction(close);
        menu_2->addAction(action_3);
        menu_2->addAction(action_4);
        menu_2->addAction(action_5);
        menu_2->addAction(action_6);
        menu_3->addAction(action_7);
        menu_3->addAction(action_8);
        menu_3->addAction(action_9);
        menu_3->addAction(action_10);
        menu_3->addAction(action_11);
        menu_3->addAction(action_12);
        menu_3->addAction(action_13);
        menu_4->addAction(menu_9->menuAction());
        menu_4->addAction(menu_10->menuAction());
        menu_4->addAction(menu_11->menuAction());
        menu_9->addAction(action_20);
        menu_9->addAction(action_21);
        menu_10->addAction(action_22);
        menu_10->addAction(action_23);
        menu_10->addAction(action_24);
        menu_11->addAction(action_25);
        menu_11->addAction(action_26);
        menu_5->addAction(action_27);
        menu_5->addAction(action_28);
        menu_5->addAction(action_29);
        menu_5->addAction(action_30);
        menu_5->addAction(menu_12->menuAction());
        menu_12->addAction(action_32);
        menu_12->addAction(action_33);
        menu_12->addAction(action_34);
        menu_7->addAction(menuRGB->menuAction());
        menuRGB->addAction(actionR);
        menuRGB->addAction(actionG);
        menuRGB->addAction(actionB);
        menu_8->addAction(action_49);
        menu_8->addAction(action_50);
        menu_13->addAction(menu_14->menuAction());
        menu_13->addAction(menu_15->menuAction());
        menu_14->addAction(action_39);
        menu_14->addAction(action_40);
        menu_14->addAction(action_41);
        menu_15->addAction(actionSobel);
        menu_15->addAction(actionLaplacian);
        menu_15->addAction(actionCanny);
        mainToolBar->addAction(new_2);
        mainToolBar->addAction(open);
        mainToolBar->addAction(save);
        mainToolBar->addAction(saveAs);
        mainToolBar->addAction(action_3);
        mainToolBar->addAction(action_4);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ps by \345\224\220\351\223\203\346\262\220 17905827", 0));
        new_2->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", 0));
        new_2->setIconText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", 0));
#ifndef QT_NO_TOOLTIP
        new_2->setToolTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        new_2->setStatusTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\233\276\345\203\217", 0));
#endif // QT_NO_STATUSTIP
        new_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
#ifndef QT_NO_TOOLTIP
        open->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        open->setStatusTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\345\203\217", 0));
#endif // QT_NO_STATUSTIP
        open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
#ifndef QT_NO_STATUSTIP
        save->setStatusTip(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\345\203\217", 0));
#endif // QT_NO_STATUSTIP
        save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        saveAs->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", 0));
#ifndef QT_NO_STATUSTIP
        saveAs->setStatusTip(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\217\246\345\255\230\344\270\272", 0));
#endif // QT_NO_STATUSTIP
        saveAs->setShortcut(QApplication::translate("MainWindow", "F12", 0));
        close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
#ifndef QT_NO_STATUSTIP
        close->setStatusTip(QApplication::translate("MainWindow", "\345\205\263\351\227\255\350\275\257\344\273\266", 0));
#endif // QT_NO_STATUSTIP
        close->setShortcut(QApplication::translate("MainWindow", "Ctrl+F4", 0));
        action_3->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0));
        action_3->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        action_4->setText(QApplication::translate("MainWindow", "\351\207\215\345\201\232", 0));
        action_4->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        action_5->setText(QApplication::translate("MainWindow", "\345\205\250\345\261\217\346\230\276\347\244\272", 0));
        action_5->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0));
        action_6->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\345\205\250\345\261\217", 0));
        action_6->setShortcut(QApplication::translate("MainWindow", "Esc", 0));
        action_7->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\347\256\261", 0));
        action_8->setText(QApplication::translate("MainWindow", "\345\207\240\344\275\225\345\217\230\346\215\242", 0));
        action_9->setText(QApplication::translate("MainWindow", "\347\201\260\345\272\246\345\217\230\346\215\242", 0));
        action_11->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262\346\250\241\345\236\213", 0));
        action_12->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\347\252\227\345\217\243", 0));
        action_13->setText(QApplication::translate("MainWindow", "\345\261\236\346\200\247\347\252\227\345\217\243", 0));
        action_20->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247\344\270\200\345\200\215", 0));
        action_21->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217\344\270\200\345\200\215", 0));
        action_22->setText(QApplication::translate("MainWindow", "\351\241\272\346\227\266\351\222\210\346\227\213\350\275\254", 0));
        action_23->setText(QApplication::translate("MainWindow", "\351\200\206\346\227\266\351\222\210\346\227\213\350\275\254", 0));
        action_24->setText(QApplication::translate("MainWindow", "\344\270\255\345\277\203\346\227\213\350\275\254", 0));
        action_25->setText(QApplication::translate("MainWindow", "\346\260\264\345\271\263\347\277\273\350\275\254", 0));
        action_26->setText(QApplication::translate("MainWindow", "\345\236\202\347\233\264\347\277\273\350\275\254", 0));
        action_27->setText(QApplication::translate("MainWindow", "\344\272\214\345\200\274\345\233\276", 0));
        action_28->setText(QApplication::translate("MainWindow", "\347\201\260\345\272\246\345\233\276", 0));
        action_29->setText(QApplication::translate("MainWindow", "\345\217\215\350\275\254\345\217\230\346\215\242", 0));
        action_30->setText(QApplication::translate("MainWindow", "\347\272\277\346\200\247\345\217\230\346\215\242", 0));
        action_32->setText(QApplication::translate("MainWindow", "\346\214\207\346\225\260\345\217\230\346\215\242", 0));
#ifndef QT_NO_TOOLTIP
        action_32->setToolTip(QApplication::translate("MainWindow", "\346\214\207\346\225\260\345\217\230\346\215\242", 0));
#endif // QT_NO_TOOLTIP
        action_33->setText(QApplication::translate("MainWindow", "\344\274\275\351\251\254\345\217\230\346\215\242", 0));
        action_34->setText(QApplication::translate("MainWindow", "\347\233\264\346\226\271\345\233\276\345\235\207\350\241\241\345\214\226", 0));
        action_35->setText(QApplication::translate("MainWindow", "\350\205\220\350\232\200", 0));
        action_36->setText(QApplication::translate("MainWindow", "\350\206\250\350\203\200", 0));
        action_39->setText(QApplication::translate("MainWindow", "\345\235\207\345\200\274\346\273\244\346\263\242", 0));
        action_40->setText(QApplication::translate("MainWindow", "\351\253\230\346\226\257\346\273\244\346\263\242", 0));
        action_41->setText(QApplication::translate("MainWindow", "\344\270\255\345\200\274\346\273\244\346\263\242", 0));
        actionSobel->setText(QApplication::translate("MainWindow", "Sobel\347\256\227\345\255\220", 0));
        actionLaplacian->setText(QApplication::translate("MainWindow", "Laplacian\347\256\227\345\255\220", 0));
        actionCanny->setText(QApplication::translate("MainWindow", "Canny\347\256\227\345\255\220", 0));
        action_42->setText(QApplication::translate("MainWindow", "\345\234\206\346\243\200\346\265\213", 0));
        action_43->setText(QApplication::translate("MainWindow", "\347\233\264\347\272\277\346\243\200\346\265\213", 0));
        action_44->setText(QApplication::translate("MainWindow", "\345\274\200\350\277\220\347\256\227", 0));
        action_45->setText(QApplication::translate("MainWindow", "\351\227\255\350\277\220\347\256\227", 0));
        action_46->setText(QApplication::translate("MainWindow", "\351\241\266\345\270\275\346\223\215\344\275\234", 0));
        action_47->setText(QApplication::translate("MainWindow", "\351\273\221\345\270\275\346\223\215\344\275\234", 0));
        action_48->setText(QApplication::translate("MainWindow", "\345\275\242\346\200\201\345\255\246\346\242\257\345\272\246", 0));
        actionR->setText(QApplication::translate("MainWindow", "R\345\210\206\351\207\217\345\233\276", 0));
        actionG->setText(QApplication::translate("MainWindow", "G\345\210\206\351\207\217\345\233\276", 0));
        actionB->setText(QApplication::translate("MainWindow", "B\345\210\206\351\207\217\345\233\276", 0));
        actionH->setText(QApplication::translate("MainWindow", "H\345\210\206\351\207\217\345\233\276", 0));
        actionS->setText(QApplication::translate("MainWindow", "S\345\210\206\351\207\217\345\233\276", 0));
        actionV->setText(QApplication::translate("MainWindow", "V\345\210\206\351\207\217\345\233\276", 0));
        actionY->setText(QApplication::translate("MainWindow", "Y\345\210\206\351\207\217\345\233\276", 0));
        actionU->setText(QApplication::translate("MainWindow", "U\345\210\206\351\207\217\345\233\276", 0));
        actionV_2->setText(QApplication::translate("MainWindow", "V\345\210\206\351\207\217\345\233\276", 0));
        actionH_2->setText(QApplication::translate("MainWindow", "H\345\210\206\351\207\217\345\233\276", 0));
        actionL->setText(QApplication::translate("MainWindow", "L\345\210\206\351\207\217\345\233\276", 0));
        actionS_2->setText(QApplication::translate("MainWindow", "S\345\210\206\351\207\217\345\233\276", 0));
        action_49->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        action_50->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        action_10->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\242\236\345\274\272", 0));
        action->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", 0));
        action_2->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\350\247\206\351\242\221", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("MainWindow", "\350\247\206\345\233\276", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\207\240\344\275\225\345\217\230\346\215\242", 0));
        menu_9->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\347\274\251\346\224\276", 0));
        menu_10->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\346\227\213\350\275\254", 0));
        menu_11->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\347\277\273\350\275\254", 0));
        menu_5->setTitle(QApplication::translate("MainWindow", "\347\201\260\345\272\246\345\217\230\346\215\242", 0));
        menu_12->setTitle(QApplication::translate("MainWindow", "\351\235\236\347\272\277\346\200\247\345\217\230\346\215\242", 0));
        menu_7->setTitle(QApplication::translate("MainWindow", "\351\242\234\350\211\262\346\250\241\345\236\213", 0));
        menuRGB->setTitle(QApplication::translate("MainWindow", "RGB\346\250\241\345\236\213", 0));
        menu_8->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
        menu_13->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\242\236\345\274\272", 0));
        menu_14->setTitle(QApplication::translate("MainWindow", "\345\271\263\346\273\221", 0));
        menu_15->setTitle(QApplication::translate("MainWindow", "\351\224\220\345\214\226", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
