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

/**
 * A big red label which animates when showError() is called on it. Use clear()
 * to unset the error again.
 */
Text {
    id: errorLabel

    color: "red"
    font.bold: true

    function showError(message) {
        errorLabel.text = message;
        scaleAnimation.running = true;
    }

    function clear() {
        errorLabel.text = " ";
    }

    ParallelAnimation {
        id: scaleAnimation
        NumberAnimation {
            target: errorLabel;
            property: "scale"; from: 2; to: 1;
            easing.type: Easing.OutQuad
        }
        NumberAnimation {
            target: errorLabel;
            property: "opacity"; from: 0; to: 1;
            easing.type: Easing.OutQuad
        }
    }
}
