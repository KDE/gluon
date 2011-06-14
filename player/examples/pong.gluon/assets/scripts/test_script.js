var x = 0;
var y = 0;
var addX = 3;
var addY = 0;

function start() {
  
}

function update() {
//   x += 1* (time / 1000);
x+=addX;
y+=addY;
if (( x > 30) || (x < -30))
addX = addX *-1;

if (( y > 30) || (y < -30))
addY = addY *-1;

var leftPlayer = Game.getFromScene("leftPlayer");
var rightPlayer = Game.getFromScene("rightPlayer");

if ( (x > 25) || (x<-25) )
{
addX = addX * -1;
if ( y >leftPlayer.position.y());
addY = 1;
if ( y <leftPlayer.position.y());
addY = -1;
}









GameObject.setPosition(x, y, 1);

}

function draw(time) {

}


function stop() {
  
}