var color = 255;
var increase = false;

function start() {
  
}

function update() {
  if(GameObject.Key_Space.isActionHeld()) {
    Game.setCurrentScene("Invaders.Game");
  }
}

function draw(time) {
  GameObject.SpriteRenderer.setColor(color, color, color, 255);

  if(increase) {
    color += 10;
    if(color >= 250) {
      increase = false;
    }
  }
  else
  {
    color -= 10;
    if(color < 0) {
      increase = true;
    }
  }
}

function stop() {
  
}
