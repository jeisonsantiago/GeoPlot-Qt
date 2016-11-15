// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GEOSCENE_H
#define GEOSCENE_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>

class GeoScene : public QGraphicsScene
{
public:
    GeoScene(QObject *parent = Q_NULLPTR);

private:
};

#endif // GEOSCENE_H
