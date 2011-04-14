var gMaxFrameJumpInt = 25;
var gCurrentlyFrameJumpInt=0
var gJumpingBool = false;

this.initialize = function()
{
}

this.update = function(time)
{
    this.rotate();
    this.jump();
}

this.draw = function()
{
}

this.rotate = function(time)
{
    this.GameObject.rotate(-2.5, new QVector3D(0,0,1));
}

this.jump = function()
{
    if (this.GameObject.Key_Jump.isActionHeld()) {
        gJumpingBool = true;
    }

    if (gJumpingBool) {
        if (gCurrentlyFrameJumpInt <= gMaxFrameJumpInt) {
            this.GameObject.setPosition(this.GameObject.position.x(), this.GameObject.position.y()+0.7);
        }

        if (gCurrentlyFrameJumpInt > gMaxFrameJumpInt) {
            this.GameObject.setPosition(this.GameObject.position.x(), this.GameObject.position.y()-0.7);
        }

        if (gCurrentlyFrameJumpInt >= gMaxFrameJumpInt*2) {
            gJumpingBool = false;
            gCurrentlyFrameJumpInt = 0;
        }

        ++gCurrentlyFrameJumpInt;
    }
}

this.partOfFrame = functiontime)
{
    return  time/1000*25;
}
