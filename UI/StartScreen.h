#ifndef DUNGEONCRAWLER_STARTSCREEN_H
#define DUNGEONCRAWLER_STARTSCREEN_H
#include <QLabel>
#include <QDialog>
#include "../GraphicalUI.h"
#include <QPushButton>
#include <QVBoxLayout>

class GraphicalUI;

QT_BEGIN_NAMESPACE

namespace Ui {
    class StartScreen;
}

QT_END_NAMESPACE

class StartScreen : public QDialog {
    Q_OBJECT

public:
    explicit StartScreen(GraphicalUI* gui, QWidget *parent = nullptr);

    ~StartScreen() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onNewGameClicked();

private:
    Ui::StartScreen *ui;
    GraphicalUI* gui;
    QLabel* backgroundLabel;
    QPushButton* newGameButton;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;

};


#endif //DUNGEONCRAWLER_STARTSCREEN_H