 /****************************************************************************
 **
 ** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** GNU Lesser General Public License Usage
 ** This file may be used under the terms of the GNU Lesser General Public
 ** License version 2.1 as published by the Free Software Foundation and
 ** appearing in the file LICENSE.LGPL included in the packaging of this
 ** file. Please review the following information to ensure the GNU Lesser
 ** General Public License version 2.1 requirements will be met:
 ** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights. These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU General
 ** Public License version 3.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of this
 ** file. Please review the following information to ensure the GNU General
 ** Public License version 3.0 requirements will be met:
 ** http://www.gnu.org/copyleft/gpl.html.
 **
 ** Other Usage
 ** Alternatively, this file may be used in accordance with the terms and
 ** conditions contained in a signed written agreement between you and Nokia.
 **
 **
 **
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

import QtQuick 1.0
import Qt.labs.shaders 1.0

ShaderEffectItem {
	id: effect
	property real ratio: 1.0
	property variant source
	property Item target
	
	anchors.fill: parent
	
	source: ShaderEffectSource {
		sourceItem: target
		live: false
		hideSource: false
	}

	SequentialAnimation on ratio {
		id: ratioAnimation
		running: true
		loops: Animation.Infinite
		NumberAnimation {
			easing.type: Easing.Linear
			to: 0.0
			duration: 1500
		}
		PauseAnimation { duration: 1000 }
		NumberAnimation {
		easing.type: Easing.Linear
		to: 1.0
		duration: 1500
		}
		PauseAnimation { duration: 1000 }
	}
	
	fragmentShader:
		"
		varying highp vec2 qt_TexCoord0;
		uniform sampler2D source;
		uniform highp float ratio;
		void main(void)
		{
			lowp vec4 textureColor = texture2D(source, qt_TexCoord0.st);
			lowp float gray = dot(textureColor, vec4(0.299, 0.587, 0.114, 0.0));
			gl_FragColor = vec4(gray * ratio + textureColor.r * (1.0 - ratio), gray * ratio + textureColor.g * (1.0 - ratio), gray * ratio + textureColor.b * (1.0 - ratio), textureColor.a);
		}
		"
}
