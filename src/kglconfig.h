#ifndef KGLCONFIG_H
#define KGLCONFIG_H
#include <QWidget>
#include <QTabWidget>
#include <QDesktopWidget>
#include <GL/glew.h>

#include "kgl/kglview.h"


class KGLConfig : public QWidget
{
public:
    KGLConfig(QWidget * parent=0);
void setupInformation();
void setupTest();

    private:
    QTabWidget * m_tab;
    QDesktopWidget * m_desktop;
    KGLView * m_view;
};

#endif // KGLCONFIG_H
