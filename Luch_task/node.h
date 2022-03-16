
#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class PaintScene;


class Node : public QGraphicsItem
{
public:
    Node(PaintScene *scene);
    void addEdge(Edge *edge);
    QList<Edge *> edges() const;
    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    bool advancePosition();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int GetNodeSize();
    QPointF getPos();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    PaintScene *my_scene;
    int nodeSize{0};
};


#endif // NODE_H
