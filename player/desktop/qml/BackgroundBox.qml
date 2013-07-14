import QtQuick 1.1

Rectangle {
	property Item target;
	y: (target.y - 10)
	height: (target.height + 20)
	x: (target.x - 10)
	width: (target.width + 20)
	color: "white";
	border.color: "white";
	radius: 0;
	opacity: 0.65;
}
