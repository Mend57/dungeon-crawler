#include "StartScreen.h"
#include "ui_StartScreen.h"

StartScreen::StartScreen(GraphicalUI* gui, QWidget *parent) : QDialog(parent), ui(new Ui::StartScreen), gui(gui) {
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    setWindowTitle("Dungeon Crawler");

    setMinimumSize(800, 600);
    resize(1024, 768);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    backgroundLabel = new QLabel(this);
    QPixmap pixmap = this->gui->getTexture("startscreen");
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setAlignment(Qt::AlignCenter);

    newGameButton = new QPushButton(this);
    QPixmap buttonPixmap = this->gui->getTexture("new_game_button");
    QIcon buttonIcon(buttonPixmap);
    newGameButton->setIcon(buttonIcon);
    newGameButton->setIconSize(buttonPixmap.size());
    newGameButton->setFixedSize(buttonPixmap.size());
    newGameButton->setStyleSheet("QPushButton { border: none; background: transparent; padding: 5px; }");
    newGameButton->setCursor(Qt::PointingHandCursor);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(newGameButton);
    buttonLayout->addStretch();

    mainLayout->addWidget(backgroundLabel, 1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(buttonLayout, Qt::AlignBottom);
    mainLayout->setContentsMargins(0, 0, 0, 50);

    connect(newGameButton, &QPushButton::clicked, this, &StartScreen::onNewGameClicked);
}

StartScreen::~StartScreen() {
    delete ui;
}

void StartScreen::onNewGameClicked(){
    gui->switchWindow();
}

void StartScreen::resizeEvent(QResizeEvent *event) {
    QDialog::resizeEvent(event);

    if (backgroundLabel && !backgroundLabel->pixmap().isNull()) {
        QPixmap originalPixmap = gui->getTexture("startscreen");
        QPixmap scaledPixmap = originalPixmap.scaled(
            backgroundLabel->size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
        );
        backgroundLabel->setPixmap(scaledPixmap);
    }
}
