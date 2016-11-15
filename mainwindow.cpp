// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // center windows
    this->centerWindow();

    // start geo view
    m_geoview = new GeoGraphicsView(this);
    m_geoview->loadKmz(":Resources/countries.kml",true);
    m_geoview->loadKmz(":Resources/states_low.kml",false,4,1000000,false);

    // put into layout
    QGridLayout *layGrid = new QGridLayout();
    ui->frame->setLayout(layGrid);
    layGrid->addWidget(m_geoview);

    connect(ui->pushButtonSaveSVG,SIGNAL(clicked(bool)),this,SLOT(saveSVG()));
    connect(ui->checkBoxBorderRuler,SIGNAL(toggled(bool)),m_geoview,SLOT(enableBorderRuler(bool)));

    ui->spinBox->setValue(m_geoview->getBorderLenght());
    connect(ui->spinBox,SIGNAL(valueChanged(int)),m_geoview,SLOT(setBorderLenght(int)));

    connect(ui->lineEditTitle,SIGNAL(textChanged(QString)),m_geoview,SLOT(setTitle(QString)));

    ui->checkBoxGrid->setChecked(m_geoview->isGridOn());
    connect(ui->checkBoxGrid,SIGNAL(toggled(bool)),m_geoview,SLOT(enableGrid(bool)));

    ui->doubleSpinBoxFontSize->setValue(m_geoview->fontSize());
    connect(ui->doubleSpinBoxFontSize,SIGNAL(valueChanged(double)),m_geoview,SLOT(setFontSize(qreal)));

    ui->doubleSpinBoxFontSizeTitle->setValue(m_geoview->fontSizeTitle());
    connect(ui->doubleSpinBoxFontSizeTitle,SIGNAL(valueChanged(double)),m_geoview,SLOT(setFontSizeTitle(qreal)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::centerWindow()
{
    int screenWidth = QApplication::desktop()->screen()->width();
    int screenHeight = QApplication::desktop()->screen()->height();
    int WIDTH = screenWidth / 1.5f;
    int HEIGHT = screenHeight / 1.5f;
    int x, y;
    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;
    this->resize(WIDTH, HEIGHT);
    this->move( x, y );
}

void MainWindow::saveSVG()
{
    QString file = qApp->applicationDirPath()+"/teste.svg";
    m_geoview->exportSVG(file);
}
