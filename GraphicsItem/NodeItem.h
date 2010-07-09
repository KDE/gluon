#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsSvgItem>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsColorizeEffect>
#include <QMap>
#include <QList>
#include <QListIterator>
#include <QByteArray>
#include <QString>
#include <QFont>
#include <QPixmap>
#include "node.h"

class NodeItem : public QGraphicsSvgItem{
  Q_OBJECT
    qreal _originalWidth;
    qreal _width;

  public:
    NodeItem(Node *n);

    Node* node() const { return _node; }
    static QMap<QString, QSvgRenderer*> _renders;
    
  private slots:
    void setupNode();
    void updateRenderer();
    void updateIcon();
    void updateName();
    void updateValue();
    void updateColor();
    void updatePos();
    void updateSize();
    void updateConnectors();
    void updateImage();
  private:
    Node *_node;
    QString _iconPackage;
    QString _element;
    QGraphicsSimpleTextItem *_name;
    QGraphicsSimpleTextItem *_value;
    QGraphicsPixmapItem *_image;
    QList<QGraphicsSvgItem*> _connectors;
    QList<QGraphicsSimpleTextItem*> _connectorLabels;
    QGraphicsColorizeEffect *_colorizer;
    QFont _font;
    int ldown;
    int rdown;
    int previousCount;
};

#include "node.h"

#endif