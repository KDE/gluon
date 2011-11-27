/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

ListModel {
    ListElement {
        iconPath: "icons/hi32-app-gluon.png";
        text: "Screenshots";
        subtext: "Check out the screenshots";
    }

    ListElement {
        iconPath: "icons/media-playback-start.png";
        text: "Play the game";
        subtext: "1697 others currently playing";
    }

    ListElement {
        iconPath: "icons/dialog-information.png";
        text: "Read Author's Description";
        subtext: "No description";
    }

    ListElement {
        iconPath: "icons/games-highscores.png";
        text: "High Scores";
        subtext: "Your global high-score: 258th";
    }

    ListElement {
        iconPath: "icons/games-achievements.png";
        text: "Achievements";
        subtext: "You have 4 of 16";
    }

    ListElement {
        iconPath: "icons/help-feedback.png";
        text: "Rate & Comment";
        subtext: "20984 ratings, 413 comments";
    }

    ListElement {
        iconPath: "icons/help-donate.png";
        text: "Donate";
        subtext: "€3 suggested";
    }

    ListElement {
        iconPath: "icons/hi32-app-gluon.png";
        text: "Comments";
        subtext: "Check out the comments";
    }
}
