#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "node.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PaintScene();
    ~PaintScene();
    void CanCreatePoly(bool can_create);
    void ClearPoly();
    void EnterChangeRegime();
    void SetPixmap(QPixmap pix);
    void timerEvent(QTimerEvent *event) override;
    void itemMoved();
    int getMaxSize();
    void ClearScene();
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event)override;
    QPixmap my_pixmap;
    QGraphicsPixmapItem *pix;
    bool can_create_poly;
    bool can_change;
    Node *prevNode;
    Node *firstNode;
    size_t i{0};
    int timerId = 0;
};

#endif // PAINTSCENE_H
