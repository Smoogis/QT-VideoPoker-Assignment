#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "Model/Hand.h"
#include "Model/Deck.h"


namespace Ui {
    class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    void cardClicked();
    void dealCards();
    void drawView();

private:
    Ui::MainView *ui;
    QLabel* _lblTitle;
    QLabel* _lblPaySheet;
    std::vector<QPushButton*> _btnCards; // card buttons
    QPushButton* _btnDeal;
    QPushButton* _btnDraw;
    Hand _hand;
    Deck _deck;
};

#endif // MAINVIEW_H
