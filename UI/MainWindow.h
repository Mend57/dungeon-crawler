#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <ui_MainWindow.h>
#include <QStatusBar>

#include "../GraphicalUI.h"
#include "../Input.h"

class DungeonCrawler;
class GraphicalUI;
class Input;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(GraphicalUI* gui, QWidget *parent = nullptr);
    void addToGridLayout(QLabel* label, int row, int column){ui->gridLayout->addWidget(label, row, column);}
    void formatArrow(std::pair<QPushButton*, std::string> button);
    void setDungeonCrawler(DungeonCrawler* dungeonCrawler){this->dungeonCrawler = dungeonCrawler;};
    Input getInput(){return lastInput;};
    void updateStatusBar();
    ~MainWindow() override;

private slots:
    void onUpLeftArrowClicked();
    void onUpArrowClicked();
    void onUpRightArrowClicked();
    void onDownLeftArrowClicked();
    void onDownArrowClicked();
    void onDownRightArrowClicked();
    void onLeftArrowClicked();
    void onSkipArrowClicked();
    void onRightArrowClicked();

private:
    Ui::MainWindow *ui;
    GraphicalUI* gui;
    DungeonCrawler* dungeonCrawler;
    Input lastInput = {0,0};
    std::vector<std::pair<QPushButton*, std::string>> buttons;
    void resizeEvent(QResizeEvent* event) override;
};

#endif
