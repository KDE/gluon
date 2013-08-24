import QtQuick 1.1

Rectangle {
	property Item target;
	y: (target.y - 10)
	height: (target.height + 20)
	x: (target.x - 10)
	width: (target.width + 20)
	color: "#E6E6E6";
	border.color: "black";
	radius: 5;
	opacity: 1;
}
