var xdir = 10;
var ydir = 5;

function update(time) {
  GameObject.translate(xdir * (time/1000), 0, 0);
  
  var position = GameObject.postion;
  if(postion.x() > 35 || postion.x() < -35) {
    GameObject.translate(0, ydir, 0);
    xdir = -xdir;
  }
}