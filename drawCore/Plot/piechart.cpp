﻿#include "piechart.h"
#include "qcustomplot.h"

PieChart::PieChart(QPointF atScenePos, QRectF bounDingRect, QPen pen, QBrush brush) :TItemEx(atScenePos, bounDingRect, pen, brush)
{   
    append(1, tr("北京"));
    append(2, tr("上海"));
    append(3, tr("天津"));

    append(4, tr("设么自己和"));
    append(5, tr("打发斯蒂芬你发送到 副圣诞节"));

}
TItem *PieChart::fCopy()
{
    PieChart *pieChart = new PieChart();
    pieChart->fCopy(this);
    return pieChart;
}

void PieChart::fCopy(PieChart *PieForm)
{
    if(nullptr == PieForm)
        return;
    TItemEx::fCopy(PieForm);

}
void PieChart::append(int perce, QString name)
{
    if(!m_ItemList.contains(perce)) {
        m_ItemList.insert(perce, name);
    } else {
        m_ItemList[perce] = name;
    }  
    m_allNumber = 0;
    for(auto i =  m_ItemList.begin(); i != m_ItemList.end(); i++)
    {
        m_allNumber += i.key();
    }
}

void PieChart::fDraw(QPainter *painter)
{
    painter->drawRect(m_boundingRect);
    double lastAngle = 0, textLeftIndex = 10;
    int colorIndex = Qt::lightGray;
    QFont textFont("宋体", 10);
    QFontMetrics fm(textFont);
    QRectF pieRect= m_boundingRect;


    pieRect.adjust(10 , 40 , -10, -10);
    double RectWidth = pieRect.width() > pieRect.height() ? pieRect.height() : pieRect.width();
    pieRect.setRect(pieRect.x(), pieRect.y(), RectWidth,  RectWidth);

    for(auto i =  m_ItemList.begin(); i != m_ItemList.end(); i++)
    {
        QRectF textRect= m_boundingRect;

        textRect.setRect(textRect.left()  + textLeftIndex, textRect.y() +10 , fm.height(), fm.height());
        textLeftIndex += fm.width(i.value()) + fm.height() + 20;
        painter->fillRect(textRect , (Qt::GlobalColor)(colorIndex++));

        textRect.setLeft(textRect.left() + 20);
        painter->drawText(textRect.x(), textRect.y()+10, i.value());

        painter->setBrush((Qt::GlobalColor)(colorIndex++));
        painter->drawPie(pieRect, lastAngle, 360*16*i.key()/m_allNumber);
        lastAngle += 360*16*i.key()/m_allNumber;
    }
    
}