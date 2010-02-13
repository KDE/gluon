/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <QApplication>
#include <gluon/graphics/glwidget.h>
#include <gluon/graphics/engine.h>
#include <gluon/graphics/item.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Create an Engine. This class contains all items that will be shown in the view. 
    // to add item, call : addItem(KGLItem *) or addItems(KGLItemList *)
//    GluonGraphics::Engine * engine = new GluonGraphics::Engine; 
    
    //this is the view widget . It's a QGLWidget child. Call KGLView::setEngine(KGLEngine *) to attach the engine to the view. 
    // YOu can set the engine directly from the constructor
    GluonGraphics::GLWidget * view = new GluonGraphics::GLWidget();
    
//    view->setEngine(engine);
   
    // This function show the current axis xy
  
    //Now we can create an object. KGLBoxItem is a simple box with 4 GLPoints. 
    GluonGraphics::Item * item = new GluonGraphics::Item(QSizeF(5.f, 5.f));
    //setup the item.
    //This function align the center of item to the center of the view.
    // itemCenter() return the coord center in Item coordinate
    //center() return the coord center in View coordinate
    // you can call translate() for add a translation.. And setTranslate() to define a translation factor in the transformation matrix
    //item->setPosition(-item->center());
    //this function make a rotation around the itemCenter. 
    // you can call rotate() to add a rotation .
 
    //this function must be called after each transformation. It updates the current Tranformation matrix of the item.
    item->updateTransform();
    
    //now we can add a color filter.
    item->setColor(Qt::red);
    //and this function apply a texture to the current Item
    
    //after all setup... We can add the item inside the engine.
//    engine->addItem(item);
    
    view->show();
   
    return app.exec();

}
