#ifndef KCLINFOWIDGET_H
#define KCLINFOWIDGET_H

#include <QWidget>
#include <KTitleWidget>
#include <QLabel>
#include <KTabWidget>
#include <QTreeView>
#include "kcldevicemodel.h"
#include "kclbuttonwidget.h"
class KCLInfoWidget : public QWidget
{
    Q_OBJECT
public:
    KCLInfoWidget(QWidget * parent=0);
    void setupPreview();
    void setupInformation();
    public slots:
    void setAuthorization();
    void detectDevice();
private:
    QWidget * m_information;
    QWidget * m_preview;
   QTreeView * m_treeView;
   KCLDeviceModel * m_model;

};

#endif // KCLINFOWIDGET_H
