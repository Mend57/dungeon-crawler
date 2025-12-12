#ifndef DUNGEONCRAWLER_STARTSCREEN_H
#define DUNGEONCRAWLER_STARTSCREEN_H

#include <QDialog>
#include "../GraphicalUI.h"

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
    std::string backgroundTexture = "startscreen";
};

#endif