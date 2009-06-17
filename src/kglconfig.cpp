#include <QLayout>
#include <QLabel>
#include "kglconfig.h"

KGLConfig::KGLConfig(QWidget * parent)
        :QWidget(parent)
{

    QLabel * title = new QLabel("KGL Config");

   QVBoxLayout * layout = new QVBoxLayout;

layout->addWidget(title);

   setLayout(layout);


}
