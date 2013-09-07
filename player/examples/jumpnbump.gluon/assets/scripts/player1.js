var gMaxFrameJumpInt = 25,
gCurrentlyFrameJumpInt=0,
gJumpingBool = false,
speed = 30;

function move(time)
{
    var addX = speed * (time/1000);

    if(self.GameObject.Key_Left.isActionHeld())
    {
        self.GameObject.translate(-addX, 0, 0);
    }

    else if(self.GameObject.Key_Right.isActionHeld())
    {
        self.GameObject.translate(addX, 0, 0);
    }

    var pos = self.GameObject.position;
    if(pos.x() < -30)
    {
        self.GameObject.setPosition(-30, pos.y(), pos.z());
    }
    else if(pos.x() > 30)
    {
        self.GameObject.setPosition(30, pos.y(), pos.z());
    }

    if(pos.y() < -30)
    {
        self.GameObject.translate(0, 5 * (time/1000), 0);
    }
    else
    {
        // justSpawned = false;
    }
}

function update(time)
{
    if(self.Scene.paused)
        return;

    move(time);
    jump();
}

function rotate()
{
    self.GameObject.rotate(-2.5, new Vector3f(0,0,1));
}

function jump()
{
    if (self.GameObject.Key_Jump.isActionHeld()) {
        gJumpingBool = true;
    }

    if (gJumpingBool) {
        if (gCurrentlyFrameJumpInt <= gMaxFrameJumpInt) {
            self.GameObject.setPosition(self.GameObject.position.x(), self.GameObject.position.y()+0.7);
        } else {
            self.GameObject.setPosition(self.GameObject.position.x(), self.GameObject.position.y()-0.7);
            if (gCurrentlyFrameJumpInt >= gMaxFrameJumpInt*2) {
                gJumpingBool = false;
                gCurrentlyFrameJumpInt = 0;
            }
        }

        ++gCurrentlyFrameJumpInt;
    }
}

function partOfFrame(time)
{
    return time/1000*25;
}

self.update = update;
