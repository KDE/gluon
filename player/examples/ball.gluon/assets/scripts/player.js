var gMaxFrameJumpInt = 25;
var gCurrentlyFrameJumpInt=0
var gJumpingBool = false;
function initialize() {
}
function update(time) {
    this.rotate();
    this.jump();
}
function draw(){
}
function rotate(time){
  this.GameObject.rotate(-2.5,new QVector3D(0,0,1));
}
function jump(){
  if(this.GameObject.Key_Jump.isActionHeld()){
    gJumpingBool = true;
  }
  if(gJumpingBool == true){
    if(gCurrentlyFrameJumpInt <= gMaxFrameJumpInt){
      this.GameObject.setPosition(this.GameObject.position.x(),this.GameObject.position.y()+0.7);
    }
    if(gCurrentlyFrameJumpInt > gMaxFrameJumpInt){
      this.GameObject.setPosition(this.GameObject.position.x(),this.GameObject.position.y()-0.7);
    }
    if(gCurrentlyFrameJumpInt >= gMaxFrameJumpInt*2){
      gJumpingBool = false;
      gCurrentlyFrameJumpInt=0
    }
   gCurrentlyFrameJumpInt++;
  }
}
function partOfFrame(time){
 return  time/1000*25;
}