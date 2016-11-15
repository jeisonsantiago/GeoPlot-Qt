// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QGraphicsItemGroup>
#include <QObject>

class ItemGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    ItemGroup(QGraphicsItem *parent = 0);
    void setVisibleRange(double min = 0, double max = 100000.0f);

public slots:
    void checkVisibleRange(double);

private:

    float m_minVisible;
    float m_maxVisible;
};

#endif // ITEMGROUP_H
