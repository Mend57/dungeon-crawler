#include "StartScreen.h"
#include "ui_StartScreen.h"
#include <QResizeEvent>
#include <QPixmap>

StartScreen::StartScreen(GraphicalUI* gui, QWidget *parent) : QDialog(parent), ui(new Ui::StartScreen), gui(gui) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    ui->backgroundLabel->setPixmap(this->gui->getTexture("startscreen"));

    QPixmap buttonPixmap = this->gui->getTexture("new_game_button");
    ui->newGameButton->setIcon(buttonPixmap);
    ui->newGameButton->setIconSize(buttonPixmap.size());
    ui->newGameButton->setStyleSheet("border:none");

    connect(ui->newGameButton, &QPushButton::clicked, this, &StartScreen::onNewGameClicked);
}

void StartScreen::onNewGameClicked() {
    Level* level = new Level(10, 10, gui);
    dungeonCrawler = new DungeonCrawler(gui, level);
    dungeonCrawler->turn();
    gui->getMainWindow()->setDungeonCrawler(dungeonCrawler);
    gui->switchWindow();
}

StartScreen::~StartScreen() {
    delete ui;
}
