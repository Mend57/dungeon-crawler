#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <ui_MainWindow.h>

#include "../GraphicalUI.h"

class GraphicalUI;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(GraphicalUI* gui, QWidget *parent = nullptr);
    void addToGridLayout(QLabel* label, int row, int column){ui->gridLayout->addWidget(label, row, column);};
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    GraphicalUI* gui;
};

#endif
