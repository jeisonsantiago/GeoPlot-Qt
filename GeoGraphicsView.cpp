// Copyright (c) 2016 Jeison Santiago
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "GeoGraphicsView.h"

GeoGraphicsView::GeoGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    //start geo setup
    this->initSetup();
}


void GeoGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}

void GeoGraphicsView::wheelEvent(QWheelEvent *event)
{
    // Scale the view / do the zoom
    //double scaleFactor = 1.15;
    static const double scaleFactor = 1.05;
    static double currentScale = 1.0;  // stores the current scale value.
    //static const double scaleMin = 1.1; // defines the min scale limit.

    if(event->delta() > 0)
    {
        // Zoom in
        this->scale(scaleFactor, scaleFactor);
        currentScale *= scaleFactor;
        //m_currentScale = scaleFactor;
    }
    //else if (currentScale > scaleMin)
    else
    {
        // Zooming out
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        currentScale /= scaleFactor;
        //m_currentScale /= scaleFactor;
    }

    //qDebug() << currentScale;
    emit sendCurrentScale(currentScale);
    m_currentScale = currentScale;
}

void GeoGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void GeoGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void GeoGraphicsView::paintEvent(QPaintEvent * event)
{
    //qDebug() << "Painter Event";

//    QRect rect(10,10,10,10);
//    QPainter p(this);
//    p.setPen(Qt::blue);
//    p.drawText(QRect(10,10,40,30),"TEXT");
//    QPainter painter;
//    painter.begin(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    paint(painter);
//    painter.end();


    QGraphicsView::paintEvent(event);
}

void GeoGraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->resetTransform();
    //painter->drawText(QRect(10,10,40,30),"TEST");

    if(m_borderRuler)
        this->drawGridTitle(painter);
}

void GeoGraphicsView::initSetup()
{
    this->setAttribute(Qt::WA_Hover );
    this->setAttribute(Qt::WA_MouseTracking);
    this->setMouseTracking(true);
    this->viewport()->setMouseTracking(true);

    // set geoscene
    m_pgeoScene = new GeoScene(this);
    //m_pgeoScene->setSceneRect(-180, -90, 360, 180);
    m_pgeoScene->setSceneRect(-300, -150, 600, 300);
    this->setScene(m_pgeoScene);
    this->scale(2.5f,-2.5f);

    //connect(this, SIGNAL(viewportEvent()),this,SLOT(viewportChanged()));

    //set transformations by input
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::ScrollHandDrag);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setBackgroundBrush(QBrush(QColor("#D1D1D1")));

    this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    // if no OPENGL ON
    //this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);

    //this->update();

    // set internal variables
    m_borderRuler = false;
    m_grid = true;
    m_axisLabel = true;
    m_borderLenght = 60;

    // black pen setup
    m_blackPen.setColor(Qt::black);
    m_blackPen.setWidthF(1.5);

    // grid pen setup
    m_gridPen.setColor(QColor(192,192,192,180));
    //m_gridPen.setColor(Qt::white);
    m_gridPen.setWidthF(1);
    QVector<qreal> dashes;
    qreal space = 4;
    qreal lineLenght = 20;
    dashes << lineLenght << space << lineLenght << space << lineLenght <<
              space << lineLenght << space << lineLenght << space;
    m_gridPen.setDashPattern(dashes);

    //fonts first update flag
    m_firstUpdate = true;


    //m_title = "TITLE";

}

QString GeoGraphicsView::getTitle() const
{
    return m_title;
}

bool GeoGraphicsView::isGridOn() const
{
    return m_grid;
}

qreal GeoGraphicsView::fontSize() const
{
    return m_ticksFont.pointSizeF();
}

qreal GeoGraphicsView::fontSizeTitle() const
{
    return m_titleFont.pointSizeF();
}

void GeoGraphicsView::setTitle(const QString &title)
{
    if(m_title != title){
        m_title = title;
        this->viewport()->update();
    }
}

void GeoGraphicsView::enableGrid(bool b)
{
    if(m_grid != b){
        m_grid = b;
        this->viewport()->update();
    }
}

void GeoGraphicsView::setFontSize(qreal size)
{
    if(m_ticksFont.pointSizeF() != size){
        m_ticksFont.setPointSizeF(size);
        this->viewport()->update();
    }
}

void GeoGraphicsView::setFontSizeTitle(qreal size)
{
    if(m_titleFont.pointSizeF() != size){
        m_titleFont.setPointSizeF(size);
        this->viewport()->update();
    }
}

int GeoGraphicsView::getBorderLenght() const
{
    return m_borderLenght;
}

void GeoGraphicsView::setBorderLenght(int borderLenght)
{
    if(m_borderLenght != borderLenght){
        m_borderLenght = borderLenght;
        this->viewport()->update();
    }
}



void GeoGraphicsView::viewportChanged()
{
    qDebug() << "viewport change" << this->viewport()->rect();
    QRectF rect = this->viewport()->rect();
    //this->rmthis->viewport()->rect()
    qDebug() << this->mapToScene(rect.toRect());
}

void GeoGraphicsView::enableBorderRuler(bool b)
{
    m_borderRuler = b;
    this->viewport()->update();
}

QPolygonF GeoGraphicsView::readCoodinates(QString coodinates)
{
    QPolygonF res;

    if(coodinates.isEmpty())
        return res;

    QStringList latlng = coodinates.split(QRegExp("[,\\s]"));

    for (int i = 0; i < latlng.size(); i+=2) {
        res.append(QPointF(latlng[i].toFloat(),latlng[i+1].toFloat()));
    }

    return res;
}

QPainterPath GeoGraphicsView::setPath(QString coodinates){
    QPainterPath res;
    QPolygonF poly;
    if(coodinates.isEmpty())
        return res;

    QStringList latlng = coodinates.split(QRegExp("[,\\s]"));

    for (int i = 0; i < latlng.size(); i+=2) {
        poly.append(QPointF(latlng[i].toFloat(),latlng[i+1].toFloat()));
    }

    res.addPolygon(poly);

    return res;
}

qreal GeoGraphicsView::currentScale() const
{
    return m_currentScale;
}

void GeoGraphicsView::exportSVG(const QString fileName, const QString title, const QString description)
{
    QRectF viewRect = this->mapToScene(this->viewport()->rect()).boundingRect();
    QRect rect = this->viewport()->rect();

    QSvgGenerator generator;

    // TODO: verifi if it has SVG extension
    generator.setFileName(fileName);
    generator.setSize(rect.size());
    //generator.setResolution(200);
    generator.setViewBox(rect);

    if(!title.isEmpty())
        generator.setTitle(title);

    if(!description.isEmpty())
        generator.setDescription(description);

    QPainter *svgPainter = new QPainter(&generator);
    svgPainter->setClipping(true);
    svgPainter->setClipRect(viewRect);

    this->prepareToExportSVG(viewRect);
    this->render(svgPainter,rect,rect);
    svgPainter->end();
    this->posExportSVG();

    qDebug() << "SUCCESS EXPORTED SVG FILE" << fileName;
}

void GeoGraphicsView::drawGridTitle(QPainter *painter)
{
    //get fonts only on first update
    if(m_firstUpdate){
        m_ticksFont = painter->font();
        m_titleFont = painter->font();
        m_firstUpdate = false;
    }

    painter->setFont(m_ticksFont);

    // Pens and Brushes
    QPen noPen(Qt::white);
    noPen.setWidth(0);

    QBrush whiteBackground(Qt::white);

    // TODO: Drawn lines and all
    QRectF viewPort = this->viewport()->rect();

    // rect white background
    painter->setBrush(whiteBackground);
    painter->setPen(noPen);

    QVector<QRectF> rectangles;
    rectangles.append(QRect(0,0,viewPort.width(),m_borderLenght)); // top
    rectangles.append(QRect(0,viewPort.height()-(m_borderLenght),viewPort.width(),m_borderLenght)); // bottom

    rectangles.append(QRect(0,0,m_borderLenght,viewPort.height())); // left

    rectangles.append(QRect(viewPort.width()-(m_borderLenght),0,m_borderLenght,viewPort.height())); // right
    painter->drawRects(rectangles);

    // rect border ruler and title
    painter->setPen(m_blackPen);
    painter->setBrush(QBrush());

    // the rect that divides the image and border
    QRectF borderRect = QRect(viewPort.x() + m_borderLenght,viewPort.y()+m_borderLenght,viewPort.width()-m_borderLenght*2, viewPort.height()-m_borderLenght*2);
    painter->drawRect(borderRect);

    // set ticks vertical and horizontal
    int ticks = 7;
    int tickSize = 10;

    // horizontal
    QPointF start = borderRect.bottomLeft();
    float walkX = start.x();
    float walkY = start.y();

    // set font metrics to get the font dimensions
    QFontMetrics metrics(painter->font());

    //guard text bottom pos;
    float bottomAxisLabel;
    float leftAxisLabel;

    for (int i = 0; i < ticks; ++i) {
        // set tick
        painter->drawLine(QPointF(walkX,start.y()),QPointF(walkX,start.y()+tickSize));

        QString textTick;
        QRect textRect;

        // set text and verify lat lon boundaries
        float longitude = this->mapToScene(walkX,start.y()).x();
        if( longitude >= -180 && longitude <= 180 ){
            textTick = QString::number(longitude,'f',1);
            textRect = metrics.boundingRect(textTick);
            painter->drawText(walkX-(textRect.width()/2),start.y()+textRect.height()+tickSize,textTick);
        }

        // draw Y grid if requested
        painter->setPen(m_gridPen);
        if( (m_grid == true) && ((i != 0) && (i != (ticks-1))) )
            painter->drawLine(QPointF(walkX,start.y()),QPointF(walkX,viewPort.top()+m_borderLenght));

        painter->setPen(m_blackPen);

        // walk through axis X
        walkX += borderRect.width()/(ticks-1);

        // set tick
        painter->drawLine(QPointF(start.x(),walkY),QPointF(start.x()-tickSize,walkY));

        // set text and verify lat lon boundaries
        float latitude = this->mapToScene(start.x(),walkY).y();
        if( latitude >= -90 && latitude <= 90 ) {
            textTick = QString::number(latitude,'f',1);
            textRect = metrics.boundingRect(textTick);
            painter->drawText(start.x()-textRect.width()-tickSize-4,walkY+(textRect.height()/3),textTick);
        }

        // draw X grid if requested
        painter->setPen(m_gridPen);
        if( (m_grid == true) && ((i != 0) && (i != (ticks-1))) )
            painter->drawLine(QPointF(start.x(),walkY),QPointF(viewPort.width()-m_borderLenght,walkY));

        painter->setPen(m_blackPen);

        // walk through axis Y
        walkY -= borderRect.height()/(ticks-1);


    }

    leftAxisLabel = start.x()-(tickSize+metrics.boundingRect("00.0").width());
    bottomAxisLabel = start.y()+(tickSize+metrics.boundingRect("00.0").height());

    // set axis label
    if(m_axisLabel){
        QRect rectTitle = metrics.boundingRect("longitude");
        float centerX = viewPort.center().x();
        painter->drawText(centerX-(rectTitle.width()/2),bottomAxisLabel+(rectTitle.height()*1.5),"longitude");

        rectTitle = metrics.boundingRect("latitude");
        float centerY = viewPort.center().y();

        painter->save();
        painter->rotate(-90);
        painter->drawText(-centerY-(rectTitle.width()/2),leftAxisLabel-(rectTitle.height()),"latitude");
        painter->restore();
    }

    // set title
    if(!m_title.isEmpty()){
        painter->setFont(m_titleFont);
        QFontMetrics titleMetrics(m_titleFont);
        QRect rectTitle = titleMetrics.boundingRect(m_title);
        float centerX = viewPort.center().x();
        painter->drawText(centerX-(rectTitle.width()/2),borderRect.top()-15,m_title);
    }
}

void GeoGraphicsView::prepareToExportSVG(QRectF rectViewport)
{
    for (int g = 0; g < m_group.size(); ++g) {
        qDebug() << "groups" << g;

        QList<QGraphicsItem*> groupIn = m_group[g]->childItems();

        foreach (QGraphicsItem *item, groupIn) {
            //qDebug() << "item:" << item;
            if(!rectViewport.intersects(item->boundingRect()))
                item->setVisible(false);
        }
    }
}

void GeoGraphicsView::posExportSVG()
{
    for (int g = 0; g < m_group.size(); ++g) {
        qDebug() << "groups" << g;

        QList<QGraphicsItem*> groupIn = m_group[g]->childItems();

        foreach (QGraphicsItem *item, groupIn) {
            item->setVisible(true);
        }
    }
}

void GeoGraphicsView::loadKmz(const QString xmlGeoFile, bool fillVector, int visibleRangeMin, int visibleRangeMax, bool startVisible)
{

    QFile filex(xmlGeoFile);
    if (!filex.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug ()<< "Error: Cannot read file " << qPrintable(xmlGeoFile)
                << ": " << qPrintable(filex.errorString());

    }

    QXmlStreamReader reader;
    reader.setDevice(&filex);

    QPen pen;

    //pen.setJoinStyle(Qt::RoundJoin);
    pen.setCosmetic(true);
    if(fillVector){
        pen.setWidthF(1.4);
        //pen.setWidthF(0);
//        pen.setColor(Qt::black);
        pen.setColor(QColor("#999999"));

        //brush.setColor(QColor("#D9D9D9"));
    }else{
        pen.setWidthF(1);
        //pen.setStyle(Qt::DashLine);
        QVector<qreal> dashes;
        qreal space = 4;
        dashes << 6 << space << 6 << space << 6 << space << 6 << space << 6 << space;
        pen.setDashPattern(dashes);

        //pen.setWidthF(0);
        //pen.setColor(QColor("#00394c"));
        pen.setColor(QColor("#BBBBBB"));
    }
    // polygon item end

    ItemGroup *group = new ItemGroup;
    m_group.append(group);

    while(!reader.atEnd() && !reader.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = reader.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
            continue;

        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement) {
            if(reader.name() == "name") {
                //ui->listWidget->addItem("Element: "+reader.name().toString());
                //qDebug() << reader.name().toString() << reader.readElementText();
                continue;
            }

            if(reader.name() == "color") {
                //ui->listWidget->addItem("Element: "+reader.name().toString());
                //qDebug() << reader.name().toString() << reader.readElementText();
                continue;
            }

            if(reader.name() == "coordinates") {
                //ui->listWidget->addItem("Element: "+reader.name().toString());
                //qDebug() << reader.name().toString() << reader.readElementText();
                //readCoodinates(reader.readElementText());

                if(fillVector){
                    //m_pgeoView->scene()->addPolygon(Helper::readCoodinates(reader.readElementText()),pen,blackBrush);
                    QGraphicsPolygonItem *poly = new QGraphicsPolygonItem(readCoodinates(reader.readElementText()));
                    poly->setPen(pen);
                    poly->setBrush(QBrush(QColor("#FAFAFA")));
                    group->addToGroup(poly);

                }else{
                    QGraphicsPathItem *path = new QGraphicsPathItem(setPath(reader.readElementText()));
                    path->setPen(pen);
                    group->addToGroup(path);
                }
                continue;

            }
        }
    }

    if(visibleRangeMin != 0 && visibleRangeMax != 0){
        group->setVisible(startVisible);
        group->setVisibleRange(visibleRangeMin,visibleRangeMax);
        connect(this,SIGNAL(sendCurrentScale(double)),group,SLOT(checkVisibleRange(double)));
    }

    filex.close();
    this->scene()->addItem(group);
}

