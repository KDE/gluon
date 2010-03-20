#include <QWidget>
#include <QObject>
#include <QDebug>
#include <gluon/graphics/item.h>
#include <gluon/graphics/meshes/cubemesh.h>

class Testa : public QWidget
{
        Q_OBJECT
    public:
        Testa(QWidget * parent = 0);
    public slots:
        void test();
    private:
        double a;
        GluonGraphics::Item * item ;




};
