#include "nodegraphicsitem.h"
#include "graphgraphicsscene.h"
#include <QtWidgets>
#include <QDebug>

int NodeGraphicsItem::radius = 50;

NodeGraphicsItem::NodeGraphicsItem(GraphGraphicsScene *scene, Avia::Node *node, QColor color)
{
    this->myScene = scene;
    this->myColor = color;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNode(node);
    isMoving = false;
    selectedColor = defaultOnSelectedColor;
}
void NodeGraphicsItem::setNode(Avia::Node* node)
{
    this->myNode = node;
    this->setPos(myNode->getEuclidePos());
    radius = std::max(radius, 20 + (int)node->getName().length() * 10);
}

Avia::Node* NodeGraphicsItem::node() const
{
    return this->myNode;
}

QRectF NodeGraphicsItem::boundingRect() const
{
    return QRectF(-radius/2 + .5, -radius/2 + .5, radius + 4, radius + 4);
}

const QColor NodeGraphicsItem::colorTable[] = {
    QColor(244,164,96),
    QColor(50,205,50),
    QColor(230,230,250),
    QColor(244,164,96),
    QColor(245,222,179),
    QColor(221,160,221),
    QColor(135,206,235),
    QColor(240,230,140),
    QColor(255,165,0),
    QColor(240,255,255),
    QColor(0,255,255),
    QColor(255,255,0),
    QColor(240,255,255),
    QColor(255,228,225),
    QColor(220,220,220),
    QColor(176,196,222)
};

const QColor NodeGraphicsItem::defaultColor = colorTable[0];
const QColor NodeGraphicsItem::defaultOnSelectedColor = colorTable[1];

void NodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (isSelected())
        myColor = onSelectedColor();
    else
        myColor = defaultColor;
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter->setBrush(QBrush(myColor));
    painter->drawEllipse(- radius/2, - radius/2, radius, radius);

    QFont font; font.setPixelSize(20);
    painter->setFont(font);
    QString txt = QString::fromStdString(this->node()->getName());
    painter->drawText(-4*txt.length(), 5, txt);
}

void NodeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    isMoving = true;
    setCursor(Qt::ClosedHandCursor);
    setPos(event->scenePos());
    this->node()->setEuclidePos(this->pos());
    emit myScene->needRedraw();
    QGraphicsItem::mouseMoveEvent(event);
}

void NodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if (isMoving) {
        setSelected(false);
        isMoving = false;
    }
    emit this->myScene->graphChanged();
    setCursor(Qt::OpenHandCursor);
}

void NodeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsItem::hoverEnterEvent(event);
    setCursor(Qt::PointingHandCursor);
}

void NodeGraphicsItem::setColor(QColor color) {
    this->myColor = color;
}

QColor NodeGraphicsItem::color() const {
    return this->myColor;
}

QColor NodeGraphicsItem::onSelectedColor() const {
    return this->selectedColor;
}

void NodeGraphicsItem::setOnSelectedColor(QColor color) {
   this->selectedColor = color;
}
