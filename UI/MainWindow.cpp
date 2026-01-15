#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(GraphicalUI* gui, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), gui(gui) {
    ui->setupUi(this);

    this->statusBar()->setStyleSheet("color: white; background-color: #222;");

    buttons = {
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

void MainWindow::updateStatusBar() {
    Character* character = dungeonCrawler->getCurrentLevel()->getMainCharacter();

    QString statusText = QString("HP: %1/%2  |  Strength: %3  |  Stamina: %4")
                        .arg(QString::number(character->getHitpoints()))
                        .arg(QString::number(character->getMaxHP()))
                        .arg(QString::number(character->getStrength()))
                        .arg(QString::number(character->getStamina()));

    this->statusBar()->showMessage(statusText);
}

void MainWindow::onUpLeftArrowClicked() {
    lastInput = {-1,-1};
    dungeonCrawler->turn();
}
void MainWindow::onUpArrowClicked() {
    lastInput = {0,-1};
    dungeonCrawler->turn();
}
void MainWindow::onUpRightArrowClicked() {
    lastInput = {1,-1};
    dungeonCrawler->turn();
}
void MainWindow::onDownLeftArrowClicked() {
    lastInput = {-1,1};
    dungeonCrawler->turn();
}
void MainWindow::onDownArrowClicked() {
    lastInput = {0,1};
    dungeonCrawler->turn();
}
void MainWindow::onDownRightArrowClicked() {
    lastInput = {1,1};
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
void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    int base = qMin(width(), height()) / 10;
    for(std::pair<QPushButton*, std::string> button : buttons){
        button.first->setIcon(this->gui->getTexture(button.second));
        button.first->setFixedSize(base, base);
        button.first->setIconSize(QSize(base, base));
        button.first->setStyleSheet("border:none");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
