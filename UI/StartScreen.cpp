#include "StartScreen.h"
#include "ui_StartScreen.h"
#include <QResizeEvent>
#include <QPixmap>

StartScreen::StartScreen(GraphicalUI* gui, QWidget *parent) : QDialog(parent), ui(new Ui::StartScreen), gui(gui) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    setStyleSheet("background-color: black;");
    ui->backgroundLabel->setPixmap(this->gui->getTexture(backgroundTexture));

    QPixmap buttonPixmap = this->gui->getTexture("new_game_button");
    ui->newGameButton->setIcon(buttonPixmap);
    ui->newGameButton->setIconSize(buttonPixmap.size());

    connect(ui->newGameButton, &QPushButton::clicked, this, &StartScreen::onNewGameClicked);
}

void StartScreen::resizeEvent(QResizeEvent *event) {
    QDialog::resizeEvent(event);
    if (!ui->backgroundLabel->pixmap().isNull()) {
        QPixmap originalPixmap = gui->getTexture(backgroundTexture);
        QPixmap scaledPixmap = originalPixmap.scaled(
            ui->backgroundLabel->size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
        );
        ui->backgroundLabel->setPixmap(scaledPixmap);
    }
}

void StartScreen::onNewGameClicked(){
    gui->switchWindow();
}

StartScreen::~StartScreen() {
    delete ui;
}
