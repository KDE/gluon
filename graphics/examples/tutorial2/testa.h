#include <QWidget>
#include <QObject>
#include <QDebug>
#include <gluon/graphics/item.h>
#include <gluon/graphics/polygonmesh.h>
#include <gluon/graphics/cubemesh.h>
#include <gluon/graphics/gridmesh.h>
#include <gluon/graphics/discmesh.h>
#include <gluon/graphics/conemesh.h>
#include <gluon/graphics/icospheremesh.h>
#include <gluon/graphics/cylindremesh.h>
class Testa : public QWidget
{
    Q_OBJECT
public:
    Testa(QWidget * parent=0);
public slots:
    void test();
private:
    double a;
    GluonGraphics::Item * item ;




};
