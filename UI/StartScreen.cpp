#include "StartScreen.h"
#include "ui_StartScreen.h"
#include <QResizeEvent>
#include <QPixmap>

StartScreen::StartScreen(GraphicalUI* gui, QWidget *parent) : QDialog(parent), ui(new Ui::StartScreen), gui(gui) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    ui->backgroundLabel->setPixmap(GraphicalUI::getTexture("startscreen"));

    const QPixmap buttonPixmap = GraphicalUI::getTexture("new_game_button");
    ui->newGameButton->setIcon(buttonPixmap);
    ui->newGameButton->setIconSize(buttonPixmap.size());
    ui->newGameButton->setStyleSheet("border:none");

    connect(ui->newGameButton, &QPushButton::clicked, this, &StartScreen::onNewGameClicked);
}

void StartScreen::onNewGameClicked() {
    initializeGame(true);
}

void StartScreen::initializeGame(bool newGame) {
    dungeonCrawler = new DungeonCrawler(gui, newGame);
    std::vector<Level*> levels = dungeonCrawler->getLevels();
    gui->getMainWindow()->setDungeonCrawler(dungeonCrawler);
    gui->drawLevel(dungeonCrawler->getCurrentLevel());
    gui->draw(dungeonCrawler->getCurrentLevel());
    gui->switchWindow();
}

void StartScreen::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_L) initializeGame(false);
}


StartScreen::~StartScreen() {
    delete ui;
}
