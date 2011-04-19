var gMaxFrameJumpInt = 25;
var gCurrentlyFrameJumpInt=0
var gJumpingBool = false;
this.speed = 30;

this.initialize = function()
{
}

this.move = function(time)
{
    var addX = this.speed * (time/1000);

    if(this.GameObject.Key_Left.isActionHeld())
    {
        this.GameObject.translate(-addX, 0, 0);
    }

    if(this.GameObject.Key_Right.isActionHeld())
    {
        this.GameObject.translate(addX, 0, 0);
    }

    var pos = this.GameObject.position;
    if(pos.x() < -30)
    {
        this.GameObject.setPosition(-30, pos.y(), pos.z());
    }
    if(pos.x() > 30)
    {
        this.GameObject.setPosition(30, pos.y(), pos.z());
    }

    if(pos.y() < -30)
    {
        this.GameObject.translate(0, 5 * (time/1000), 0);
    }
    else
    {
        // this.justSpawned = false;
    }
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;

    this.move(time);
    this.jump();
}

this.draw = function()
{
}

this.rotate = function()
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
        } else {
            this.GameObject.setPosition(this.GameObject.position.x(), this.GameObject.position.y()-0.7);
            if (gCurrentlyFrameJumpInt >= gMaxFrameJumpInt*2) {
                gJumpingBool = false;
                gCurrentlyFrameJumpInt = 0;
            }
        }

        ++gCurrentlyFrameJumpInt;
    }
}

this.partOfFrame = function(time)
{
    return  time/1000*25;
}
