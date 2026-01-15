#include "StartScreen.h"
#include "ui_StartScreen.h"
#include <QResizeEvent>
#include <QPixmap>

StartScreen::StartScreen(GraphicalUI* gui, std::vector<Level*> levels, QWidget *parent) : QDialog(parent), ui(new Ui::StartScreen), gui(gui), levels(levels) {
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
    dungeonCrawler = new DungeonCrawler(gui, levels);
    gui->getMainWindow()->setDungeonCrawler(dungeonCrawler);
    gui->draw(levels.front());
    gui->switchWindow();
}

StartScreen::~StartScreen() {
    delete ui;
}
