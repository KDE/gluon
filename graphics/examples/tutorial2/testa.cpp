#include "testa.h"
#include <QWidget>
#include <QDebug>
#include <cmath>
Testa::Testa(QWidget * parent)
        : QWidget(parent)
{
    GluonGraphics::CubeMesh * mesh = new GluonGraphics::CubeMesh();
    item = new GluonGraphics::Item(mesh);

    a = 0;

}

void Testa::test()
{
    a++;
    item->setRotation(a, QVector3D(1, 1, 0));
    item->updateTransform();

}

