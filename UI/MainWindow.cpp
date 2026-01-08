#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(GraphicalUI* gui, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), gui(gui) {
    ui->setupUi(this);

    std::vector<std::pair<QPushButton*, std::string>> buttons = {
        {ui->arrow_up_left, "arrow_up_left"},
        {ui->arrow_up, "arrow_up"},
        {ui->arrow_up_right, "arrow_up_right"},
        {ui->arrow_left, "arrow_left"},
        {ui->arrow_skip, "arrow_skip"},
        {ui->arrow_right, "arrow_right"},
        {ui->arrow_down_left, "arrow_down_left"},
        {ui->arrow_down, "arrow_down"},
        {ui->arrow_down_right, "arrow_down_right"}
    };

    for(std::pair<QPushButton*, std::string> button : buttons) formatArrow(button);

    connect(ui->arrow_up_left, &QPushButton::clicked, this, &MainWindow::onUpLeftArrowClicked);
    connect(ui->arrow_up, &QPushButton::clicked, this, &MainWindow::onUpArrowClicked);
    connect(ui->arrow_up_right, &QPushButton::clicked, this, &MainWindow::onUpRightArrowClicked);
    connect(ui->arrow_left, &QPushButton::clicked, this, &MainWindow::onLeftArrowClicked);
    connect(ui->arrow_skip, &QPushButton::clicked, this, &MainWindow::onSkipArrowClicked);
    connect(ui->arrow_right, &QPushButton::clicked, this, &MainWindow::onRightArrowClicked);
    connect(ui->arrow_down_left, &QPushButton::clicked, this, &MainWindow::onDownLeftArrowClicked);
    connect(ui->arrow_down, &QPushButton::clicked, this, &MainWindow::onDownArrowClicked);
    connect(ui->arrow_down_right, &QPushButton::clicked, this, &MainWindow::onDownRightArrowClicked);

}

void MainWindow::formatArrow(std::pair<QPushButton*, std::string> button) {
    button.first->setIcon(this->gui->getTexture(button.second));
    button.first->setIconSize(button.first->size());
    button.first->setCursor(Qt::PointingHandCursor);
    //button.first->setStyleSheet("border:none");
}

void MainWindow::onUpLeftArrowClicked() {
    lastInput = {-1,1};
    dungeonCrawler->turn();
}
void MainWindow::onUpArrowClicked() {
    lastInput = {0,1};
    dungeonCrawler->turn();
}
void MainWindow::onUpRightArrowClicked() {
    lastInput = {1,1};
    dungeonCrawler->turn();
}
void MainWindow::onDownLeftArrowClicked() {
    lastInput = {-1,-1};
    dungeonCrawler->turn();
}
void MainWindow::onDownArrowClicked() {
    lastInput = {0,-1};
    dungeonCrawler->turn();
}
void MainWindow::onDownRightArrowClicked() {
    lastInput = {1,-1};
    dungeonCrawler->turn();
}
void MainWindow::onLeftArrowClicked() {
    lastInput = {-1,0};
    dungeonCrawler->turn();
}
void MainWindow::onSkipArrowClicked() {
    lastInput = {0,0};
    dungeonCrawler->turn();
}
void MainWindow::onRightArrowClicked() {
    lastInput = {1,0};
    dungeonCrawler->turn();
}

MainWindow::~MainWindow() {
    delete ui;
}
