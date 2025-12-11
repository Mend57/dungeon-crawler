#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(GraphicalUI* gui, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), gui(gui) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
