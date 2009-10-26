
#ifndef KGLRESOLUTIONPRIVATE_H
#define KGLRESOLUTIONPRIVATE_H

#include <QtCore/QSharedData>

class KGLResolutionPrivate : public QSharedData
{
    public:
        int id;
        int width;
        int height;
        short refreshRate;
};

#endif
