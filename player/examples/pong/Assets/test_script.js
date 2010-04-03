var x = 0;
var y = 0;
var addX = 1;
var addY = 0;
function start() {
  
}

function update() {
//   x += 1* (time / 1000);
x+=addX;

if (( x > 10) || (x < -10))
addX = addX *-1;

GameObject.setPosition(x, y, 1);

}

function draw(time) {

}


function stop() {
  
}