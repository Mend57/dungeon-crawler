#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <ui_MainWindow.h>
#include <QStatusBar>
#include <qevent.h>
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
    void addToGridLayout(QLabel* label, const int row, const int column) const {ui->gridLayout->addWidget(label, row, column);}
    void formatArrow(std::pair<QPushButton*, std::string> button);
    void setDungeonCrawler(DungeonCrawler* dungeonCrawler){this->dungeonCrawler = dungeonCrawler;};
    Input getInput() const {return lastInput;};
    void updateStatusBar() const;
    void arrowClicked(Input input);
    void endGame(bool win);
    ~MainWindow() override;
    void clearGridLayout() const {
        QLayoutItem* item;
        while ((item = ui->gridLayout->takeAt(0)) != nullptr) {
            if (item->widget()) item->widget()->setParent(nullptr);
            delete item;
        }
    }

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
    void keyPressEvent(QKeyEvent* event) override;
};

#endif
