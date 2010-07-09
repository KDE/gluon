#include "NodeItem.h"
#include <kstandarddirs.h>
#include <QDir>
#include <KGlobal>
#include <KDebug>
#include <QGraphicsColorizeEffect>
#include <QFont>
#include <QGraphicsScene>
#include <KLocale>

QMap<QString, QSvgRenderer*> NodeItem::_renders;    

NodeItem::NodeItem(Node* n) : QGraphicsSvgItem(0){
    _node = n;
    _name = 0;
    _value = 0;
    _image = new QGraphicsPixmapItem(QPixmap(0,0),this);
    _originalWidth = _node->width();
    _iconPackage = _node->iconPackage();
    _colorizer = new QGraphicsColorizeEffect(this);
    _font = QFont("Helvetica [Cronyx]", 18);
    
    connect(n, SIGNAL(changed()), this, SLOT(setupNode()));
    connect(n, SIGNAL(removed()), this, SLOT(deleteLater()));
    
    setupNode();
    setZValue(1);
    setFlag(ItemIsSelectable, true);
    
    kDebug() << "Visual Node Item Created";
}

void NodeItem::setupNode(){
    updateRenderer();
    updateIcon();
    updateConnectors();
    updateName();
    updateValue();
    updateColor();
    updateSize();
    updatePos();
    updateImage();
    update();
}

//this beast needs some taming
void NodeItem::updateConnectors(){
  QListIterator<QByteArray> plist = _node->dynamicPropertyNames();
  rdown=0;
  ldown=0;
  QRectF bound = boundingRect();
  QGraphicsSvgItem* tSvg;
  QGraphicsSimpleTextItem* tText;
  if((_connectors.count()==0 && _connectorLabels.count()==0)||(_node->dynamicPropertyNames().count()!=previousCount)){
  _connectorLabels.clear();
  _connectors.clear();
    if (!plist.hasNext()){
    return;
  }else{
    while (plist.hasNext()){
      const char* temp= plist.next().data();
      if(_node->property(temp)=="in"){
	tSvg = new QGraphicsSvgItem(KGlobal::dirs()->locate("data", "iconpacks/default.svg"),this);
	tSvg->setElementId("rocs_connector");
	tText = new QGraphicsSimpleTextItem(QString(temp),this);
	tText->setFont(_font);
	if(_node->name()=="if"){
	    tSvg->setPos((bound.height()/2)-7.95,0);
	    tText->setPos((bound.height()/2)-7.95,-40);
	}else{
	    tSvg->setPos(bound.left(),ldown);
	    tText->setPos(bound.left()-(tText->boundingRect().width()+20),ldown);
	    ldown+=50; 
	}
      }else if(_node->property(temp)=="out"){
	tSvg = new QGraphicsSvgItem(KGlobal::dirs()->locate("data", "iconpacks/default.svg"),this);
	tSvg->setElementId("rocs_connector");
	tText = new QGraphicsSimpleTextItem(QString(temp),this);
	tText->setFont(_font);
	if(_node->name()=="if"){
	if(QString(temp)=="true"){
	tSvg->setPos(bound.left()-7.95,(bound.width()/2)-8.25);
	tText->setPos(bound.left()-(tText->boundingRect().width()+20),(bound.width()/2)-8.25);}
	else if(QString(temp)=="false"){
	tSvg->setPos(bound.right()-7.95,(bound.width()/2)-8.25);
	tText->setPos(bound.right()+20,(bound.width()/2)-8.25);
	}
	}else{
	tSvg->setPos(bound.right()-tSvg->boundingRect().width(),rdown);
	tText->setPos(bound.right()+(20-tSvg->boundingRect().width()),rdown);
	rdown+=50;
	}
      }
      _connectors.append(tSvg);
      _connectorLabels.append(tText);
      previousCount=_node->dynamicPropertyNames().count();
    }
  }
  }
}

void NodeItem::updatePos(){
   int fixPos = boundingRect().width()/2;
   setPos(_node->x() - fixPos, _node->y() - fixPos);
}

void NodeItem::updateSize(){
  if (_node->width() == _width) return;
  resetMatrix();
  _width = _node->width();
  setScale(_node->width());
   kDebug() << "Scale" << scale() << "Node Width" << _node->width() << "Shét" <<  _node->width() - 0.5;
}

void NodeItem::updateRenderer(){
  _iconPackage = _node->iconPackage();
  if( _renders.count(_iconPackage) == 0){
        QSvgRenderer *z = new QSvgRenderer(_node->iconPackage());
        _renders.insert(_iconPackage, z);
        setSharedRenderer(z);
  }else{
      setSharedRenderer( _renders.value(_iconPackage) );
  }
}

void NodeItem::updateIcon(){
   if ( elementId().isEmpty() ){
      _element = _node->icon();
      setElementId(_element);
      setTransformOriginPoint(boundingRect().width()/2, boundingRect().width()/2);
   }else if( elementId() != _node->icon()){
      _element = _node->icon();
      setElementId(_element);
      setTransformOriginPoint(boundingRect().width()/2, boundingRect().width()/2);
   }
}

void NodeItem::updateColor(){
   _colorizer->setColor( _node->color());
   setGraphicsEffect(_colorizer);
}

void NodeItem::updateName(){
   if ( !_name ){
    _name = new QGraphicsSimpleTextItem(i18n("Name: %1").arg(_node->name()), this);
    _name->setFont(_font);
   }else if (_name->text() != _node->name()){
    _name->setText(i18n("Name: %1").arg(_node->name()));
   }
   _name->setVisible(_node->showName());
   _name->setPos(0, 75);
}

void NodeItem::updateValue(){
   if ( !_value ){ 
      _value = new QGraphicsSimpleTextItem(i18n("Value: %1").arg(_node->value().toString()), this);
      _value->setFont(_font);
   }else if (_value->text() != _node->value().toString()){
      _value ->setText(i18n("Value: %1").arg(_node->value().toString()));
   }
   _value->setVisible(_node->showValue());
   _value->setPos(0, 100);
}

void NodeItem::updateImage(){
  if(_image->pixmap().isNull()){
    _image->setPixmap(_node->image());
  }else if(!(_image->pixmap().toImage() == _node->image().toImage())){
    _image->setPixmap(_node->image());
  }
  _image->setVisible(_node->showImage());
  _image->setPos(0,125);
}