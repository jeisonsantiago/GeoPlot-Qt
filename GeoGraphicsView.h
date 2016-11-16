// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GEOGRAPHICSVIEW_H
#define GEOGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <QWheelEvent>
#include <QXmlStreamReader>
#include <QGLWidget>
#include <QSvgGenerator>
#include <QTextItem>
#include <QFontMetrics>

#include "GeoScene.h"
#include "ItemGroup.h"

class GeoGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GeoGraphicsView(QWidget *parent = Q_NULLPTR);

    void loadKmz(const QString xmlGeoFile, bool fillVector = false, int visibleRangeMin = 0, int visibleRangeMax = 0, bool startVisible = true);

    void setText(const QString &text);

    qreal currentScale() const;

    void exportSVG(const QString fileName, const QString title = "", const QString description = "");
    void exportPNG(const QString fileName);

    int getBorderLenght() const;

    QString getTitle() const;

    bool isGridOn() const;

    qreal fontSize() const;
    qreal fontSizeTitle() const;

signals:
    void sendCurrentScale(double);

public slots:
    void setBorderLenght(int borderLenght);
    void setTitle(const QString &title);
    void enableGrid(bool b);
    void setFontSize(qreal size);
    void setFontSizeTitle(qreal size);

protected:
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void drawForeground(QPainter *painter, const QRectF &rect);

    void prepareToExportSVG(QRectF rectViewport);
    void posExportSVG();
    QPolygonF readCoodinates(QString coodinates);
    QPainterPath setPath(QString coodinates);
    void drawGridTitle(QPainter *painter);

private slots:
    void viewportChanged();
    void enableBorderRuler(bool b);

private:
    void initSetup();

    GeoScene *m_pgeoScene;
    QGraphicsRectItem *m_rectView;
    QList<ItemGroup*> m_group;

    qreal m_currentScale;
    qreal m_transformScale;
    bool m_borderRuler;
    bool m_grid;
    bool m_axisLabel;
    bool m_firstUpdate;

    QPen m_globePen;

    QPen m_noPen;
    QPen m_blackPen;
    QPen m_gridPen;
    QFont m_ticksFont;
    QFont m_titleFont;
    QFont m_labelFont;
    int m_borderLenght;
    QString m_title;

};

#endif // GEOGRAPHICSVIEW_H
