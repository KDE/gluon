var gMaxFrameJumpInt = 25,
gCurrentlyFrameJumpInt=0,
gJumpingBool = false;

function update(time)
{
    if(!Game.end)
    {
        rotate();
        jump();
    }
}

function rotate(time)
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
        }

        if (gCurrentlyFrameJumpInt > gMaxFrameJumpInt) {
            self.GameObject.setPosition(self.GameObject.position.x(), self.GameObject.position.y()-0.7);
        }

        if (gCurrentlyFrameJumpInt >= gMaxFrameJumpInt*2) {
            gJumpingBool = false;
            gCurrentlyFrameJumpInt = 0;
        }

        ++gCurrentlyFrameJumpInt;
    }
}

function partOfFrame(time)
{
    return time/1000*25;
}

self.update = update;
