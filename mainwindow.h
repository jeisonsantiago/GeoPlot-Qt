// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QGridLayout>
#include <QPolygonF>
#include <QPrinter>
#include <QPicture>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "GeoGraphicsView.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void saveSVG();

private:
    void centerWindow();

    Ui::MainWindow *ui;
    GeoGraphicsView *m_geoview;
};

#endif // MAINWINDOW_H
