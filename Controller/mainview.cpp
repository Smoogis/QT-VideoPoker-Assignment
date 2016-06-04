#include "mainview.h"
#include "ui_mainview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    _deck.shuffle();

    QVBoxLayout* vlMain = new QVBoxLayout(ui->centralWidget);
    QHBoxLayout* hlCards = new QHBoxLayout();


    _lblTitle = new QLabel();
    _lblPaySheet = new QLabel();

    _lblTitle->setStyleSheet("border-image:url(:/media/banner.png)"); // set images
    _lblPaySheet->setStyleSheet("border-image:url(:/media/paysheet1.png)");
    vlMain->addWidget(_lblTitle);
    vlMain->addWidget(_lblPaySheet);

    for (int i = 0; i < 5; i++) // create card buttons
    {
        auto* btn = new QPushButton();
        btn->setStyleSheet("border-image:url(:/media/cardback.png)"); // set card image
        btn->setMinimumSize(128, 192);
        btn->setMaximumSize(128, 192);
        btn->setEnabled(false);

        connect(btn, &QPushButton::clicked, this, &MainView::cardClicked); //connect card to function
        hlCards->addWidget(btn);
        _btnCards.push_back(btn);
    }

    _btnDeal->setText("Deal");
    _btnDraw->setText("Draw");

    connect(_btnDeal, &QPushButton::clicked, this, &MainView::dealCards); //connect deal to btnDeal

    vlMain->addWidget(_btnDeal);
    vlMain->addWidget(_btnDraw);

    vlMain->addLayout(hlCards);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::cardClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());


}

void MainView::dealCards() // deal hand
{
    for (auto e : _btnCards)
    {
        e->setEnabled(true);
    }

    for (int i = 0; i < 5; i++)
    {
        _hand.addCard(_deck.dealCard());
    }

    drawView();
}

void MainView::drawView() // update the view
{
    for (auto e : _btnCards)
    {
        e->setStyleSheet("border-image:url(:/media/cardfrontGray.png)");
        e->setText(QString::fromStdString(_hand.toString()));
    }
}


