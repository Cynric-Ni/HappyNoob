#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusbar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void setCurrentFile(const QString& fileName);
    void updateRecentFileActions();
    QString strippedName(const QString& fullFileName);

    Spreadsheet* spreadsheet;
    FindDialog* findDialog;
    QLabel* locationLabel;
    QLabel* formulaLabel;
    QString curFile;
    QStringList recentFiles;
   
    enum{MaxRecentFiles = 5};
    QAction* recentFileActions[MaxRecentFiles];
    QAction* separatorAction;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* selectSubMenu;
    QMenu* toolsMenu;
    QMenu* optionsMenu;
    QMenu* helpMenu;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* exitAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* selectAllAction;
    QAction* showGridAction;
    QAction* aboutAction;
    QAction* aboutQtAction;
    QAction* cutAction;
    QAction* selectRowAction;
    QAction* selectColumAction;
    QAction* findAction;
    QAction* goToAction;
    QAction* recalculateAction;
    QAction* sortAction;
    QAction* autoRecalcAction;
    QAction* goToCellAction;
};
