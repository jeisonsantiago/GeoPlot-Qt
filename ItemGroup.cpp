// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ItemGroup.h"

ItemGroup::ItemGroup(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{

}

void ItemGroup::setVisibleRange(double min, double max)
{
    m_minVisible = min;
    m_maxVisible = max;
}

void ItemGroup::checkVisibleRange(double v)
{
    if(v >= m_minVisible && v <= m_maxVisible){
        this->setVisible(true);
    }else{
        this->setVisible(false);
    }
}
