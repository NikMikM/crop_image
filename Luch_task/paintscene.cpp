#include "paintscene.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsItem>
#include <QPainter>


PaintScene:: PaintScene() :  pix{nullptr},can_create_poly{false}, prevNode{nullptr},firstNode{nullptr}{
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

PaintScene::~PaintScene(){
    const QList<QGraphicsItem *> items = this->items();
    for (auto i : items){
        this->removeItem(i);
    }
}
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{ if (can_create_poly){

        Node *my_pt = new Node(this);
        this->addItem(my_pt);
        my_pt->setPos(event->scenePos());

        if(i != 0){
            this->addItem(new Edge(prevNode,my_pt));
        }
        if(i == 0){
            firstNode = my_pt;
        }
        prevNode = my_pt;
        i++;

    } else {
        if(can_change){
            QPolygonF current_poly;

            const QList<QGraphicsItem *> items = this->items();
            for (QGraphicsItem *item : items) {
                if (Node *node = qgraphicsitem_cast<Node *>(item))
                    current_poly << node->getPos();
            }
            if(current_poly.containsPoint(QPoint(event->scenePos().x(),event->scenePos().y()),Qt::OddEvenFill)) {//проверяем, что клик попадает в область текущего полигона
                QPainterPath current_path;//создаём QPainterPath, чтобы с помощью него вырезать фрагмент изображения, ограниченный полигоном
                current_path.addPolygon(current_poly);
                current_path.closeSubpath();

                QPixmap result(my_pixmap.size());//Изменяем Pixmap согласно тому пути, который ограничивает выбранный полигон
                QPainter canvas(&result);
                canvas.setCompositionMode(QPainter::CompositionMode_DestinationOver);
                canvas.setBackground(QBrush(QColor(255,0,255,0)));//устанавливаем фон в прозрачный
                canvas.setClipPath(current_path);//вырезаем path

                canvas.drawPixmap(0,0,my_pixmap);//рисуем фрагмент, с пустым фоном

                pix = new QGraphicsPixmapItem(result);//создаём текущий фрагмент, сразу добавляем его на сцену и заходим в событие перетаскивания
                pix->setCacheMode(QGraphicsPixmapItem::DeviceCoordinateCache);
                pix->setAcceptDrops(true);
                pix->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);//MaskShape
                pix->setTransformationMode(Qt::SmoothTransformation);
                pix->setFlags(QGraphicsItem::ItemIsMovable);//::ItemIsDragEnabled |Qt::ItemIsDropEnabled
                this->addItem(pix);
                QGraphicsScene::mousePressEvent(event);


            }
            else {
                QGraphicsScene::mousePressEvent(event);//Если клик вне области полигона, тогда интерапретируем его как елик возможно по уже существующему фрагменту
            }
        }
        QGraphicsScene::mousePressEvent(event);

    }

}
void PaintScene::CanCreatePoly(bool can_create){
    can_create_poly = can_create;
}

void PaintScene::ClearPoly(){

    const QList<QGraphicsItem *> items = this->items();//удаляем все объекты, которые не являются QPixmapItem
    for (QGraphicsItem *item : items) {
        if (QGraphicsItem *current_item = qgraphicsitem_cast<QGraphicsPixmapItem *>(item)){
            continue;
        } else {
            this->removeItem(item);
        }
    }
    can_change = false;//устанавливаем флаг разрешения перетаскивания вершин в 0
    i = 0; //Устанавливаем счётчик вершин в 0;

}

void PaintScene::EnterChangeRegime(){
    if (i != 0)this->addItem(new Edge(prevNode,firstNode));
    can_change = true;
}
void PaintScene::SetPixmap(QPixmap pix){
    my_pixmap = pix;
}

void PaintScene::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    const QList<QGraphicsItem *> items = this->items();//Ищем все узлы на изображении
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    bool itemsMoved = false;
    for (Node *node : qAsConst(nodes)) {//меняем положение граней
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
void PaintScene::itemMoved()
{
    if(!can_create_poly){
        if (!timerId)
            timerId = startTimer(1000 / 25);
    }
}

int PaintScene::getMaxSize(){//метод для получения размеров изображения, позволяющий подстроить размер точек на полигоне
    if (my_pixmap.height() > my_pixmap.width()){
        return my_pixmap.height();
    }else {
        return my_pixmap.width();
    }
}

void PaintScene::ClearScene(){
    const QList<QGraphicsItem *> items = this->items();
    for (auto i : items){
        this->removeItem(i);
    }
    this->addPixmap(my_pixmap);

}
