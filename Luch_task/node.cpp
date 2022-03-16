#include "edge.h"
#include "node.h"
#include "paintscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(PaintScene *scene)
    : my_scene(scene)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    nodeSize = (my_scene->getMaxSize())/80;
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

bool Node::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(mapFromScene(newPos));
    return true;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 5;
    return QRectF( -nodeSize-adjust, -nodeSize-adjust, 2*nodeSize+adjust, 2*nodeSize+adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-nodeSize, -nodeSize, 2*nodeSize, 2*nodeSize);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::red).lighter(220));
        gradient.setColorAt(0, QColor(Qt::darkRed).lighter(220));
    } else {
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, Qt::darkRed);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));

    painter->drawEllipse(-nodeSize, -nodeSize, 2*nodeSize, 2*nodeSize);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QPointF Node::getPos(){
    return this->scenePos();
}

int Node::GetNodeSize(){
    return nodeSize;
}
