/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents

Item {
    id: ratingWidgetRootItem
    property int rating: 0

    Component {
        id: ratingDelegate

        Item {
            height: ratingWidgetRootItem.height; width: ratingWidgetRootItem.width/ratingModel.count;
            PlasmaComponents.ToolButton {
                id: ratingButton
                anchors.fill: parent

                iconSource: value > 0 ? "rating" : "draw-star"
                onClicked: console.log(index)
            }
        }
    }

    ListView {
        id: ratingList
        height: parent.height; width: parent.width;
        anchors.right: parent.right;

        orientation: ListView.Horizontal
        model: ratingModel
        delegate: ratingDelegate
    }

    ListModel {
        id: ratingModel

        ListElement {
            value: 0
        }
        ListElement {
            value: 0
        }
        ListElement {
            value: 0
        }
        ListElement {
            value: 0
        }
        ListElement {
            value: 0
        }
    }

    onRatingChanged: {
        var tmp = rating;
        var i = 0;
        var ratingPerStar = 100/ratingModel.count;

        //Clear all stars
        for (j=0; j<ratingModel.count; ++j) {
            ratingModel.get(j).value = 0;
        }

        while (tmp > 0) {
            if (tmp > ratingPerStar) {
                ratingModel.get(i).value = ratingPerStar;
            } else {
                ratingModel.get(i).value = tmp;
            }
            tmp -= ratingPerStar;
            ++i;
        }
    }
}