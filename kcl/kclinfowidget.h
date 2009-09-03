#ifndef KCLINFOWIDGET_H
#define KCLINFOWIDGET_H

#include <QWidget>
#include <KTitleWidget>
#include <QLabel>
#include <KTabWidget>
#include "kcldevicemodel.h"
class KCLInfoWidget : public QWidget
{
public:
    KCLInfoWidget(QWidget * parent=0);

private:
    QWidget * m_information;
    QWidget * m_preview;


};

#endif // KCLINFOWIDGET_H
