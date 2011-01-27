/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

Item {
    id: mainview
    property string statepoint: "start"

    width: 1600
    height: 900

    SystemPalette {
        id: activePalette
    }

    states: [
        State { name: "startup"; when: statepoint == "startup"
            PropertyChanges { }
        },

        State { name: "registration"; when: statepoint == "registration"
            PropertyChanges { }
        },

        State { name: "home"; when: statepoint == "home"
            PropertyChanges { }
        },

        State { name: "details"; when: statepoint == "details"
            PropertyChanges { }
        },

        State { name: "comments"; when: statepoint == "comments"
            PropertyChanges { }
        },

        State { name: "other"; when: statepoint == "other" }
    ]

    Startup {
        height: parent.height
        width: parent.width
        visible: statepoint == "startup"
    }

    Registration {
        height: parent.height
        width: parent.width
        visible: statepoint == "registration"
    }

    Home {
        height: parent.height
        width: parent.width
        visible: statepoint == "home"
    }

    Details {
        height: parent.height
        width: parent.width
        visible: statepoint == "details"
    }

    Comments {
        height: parent.height
        width: parent.width
        visible: statepoint == "comments"
    }

    Component.onCompleted: {
        statepoint = "startup"
    }
}

