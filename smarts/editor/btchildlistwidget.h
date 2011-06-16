#ifndef BTCHILDLISTWIDGET_H
#define BTCHILDLISTWIDGET_H

#include <QWidget>
#include <QObject>

class QVBoxLayout;

class btChildListWidget : public QWidget 
{
    Q_OBJECT
public:
    btChildListWidget(QWidget * parent = 0);
    ~btChildListWidget();
    
    void setChildProbabilites(QString propertyName, QObject * object, bool enabled);
    
private:
    QVBoxLayout*        childLayout;    
};

#endif
