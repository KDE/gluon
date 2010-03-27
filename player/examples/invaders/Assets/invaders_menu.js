var color = 50;
var color_increment = 3;
var ypos = 0.0;
var ypos_increment = 1 - Math.random() * 2;
var xpos = 0.0;
var xpos_increment = 1 - Math.random() * 2;
var timer = 0;

function start() {
  
}

function update() {
  if(GameObject.Key_Space.isActionHeld()) {
    Game.setCurrentScene("Invaders/Game");
  }

  GameObject.setPosition(xpos, ypos, 1);
  
  ypos += ypos_increment;
  if(ypos <= -30 || ypos >= 30) {
    ypos_increment = -ypos_increment;
  }

  xpos += xpos_increment;
  if(xpos <= -30 || xpos >= 30) {
    xpos_increment = -xpos_increment;
  }

  GameObject.SpriteRenderer.setColor(color, color, color, 255);

  color += color_increment;
  if(color <= 50 || color >= 250) {
    color_increment = -color_increment;
  }
}

function draw(time) {

}

function stop() {
  
}
