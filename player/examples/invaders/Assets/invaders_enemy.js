var x = 0;
var y = -35;
var xdir = 10;
var ydir = 5;

function start() {
  //x = GameObject.position.x();
  //y = GameObject.position.y();
}

function update(time) {
  x += xdir * (time / 1000);
  GameObject.setPosition(x, y, 1);
  if(x > 35 || x < -35) {
    y += ydir;
    xdir = -xdir;
  }
}

function draw(time) {

}

function stop() {

}
 
