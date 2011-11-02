/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

import QtQuick 1.0

/**
 * An item that indicates if something is happening.
 */

Image {
    id: indicator
    property bool running: false
    source: "icons/progress-indicator.png"
    opacity: 0
    scale: 4
    smooth: true;

    NumberAnimation {
        id: rotateAnimation
        target: indicator
        property: "rotation"
        from: 0
        to: 360
        duration: 1000
        loops: Animation.Infinite
    }

    states: [
        State {
            name: "running"
            when: indicator.running
            PropertyChanges {
                target: rotateAnimation
                running: true
            }

            PropertyChanges {
                target: indicator
                opacity: 1
                scale: 1
            }
        }
    ]


    transitions: [
        Transition {
            from: "running"
            SequentialAnimation {
                NumberAnimation {
                    properties: "opacity,scale"
                    duration: 500
                    easing.type: Easing.InOutQuad
                }

                PropertyAction {
                    property: "running"
                }
            }
        },

        Transition {
            to: "running"
            SequentialAnimation {
                NumberAnimation {
                    properties: "opacity,scale"
                    duration: 1000
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]
}
