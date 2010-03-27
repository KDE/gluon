
function start() {
  
}

function update(time) {
  if(GameObject.Key_Left.isActionHeld())
  {
    GameObject.translate(10*(time/1000), 0, 0);
  }

  if(GameObject.Key_Right.isActionHeld())
  {
    GameObject.translate(-10*(time/1000), 0, 0);
  }

  var pos = GameObject.position;
  if(pos.x() < -30)
    GameObject.setPosition(-30, pos.y(), pos.z());
  if(pos.x() > 30)
    GameObject.setPosition(30, pos.y(), pos.z());
}

function draw() {
  
}

function stop() {
  
}
