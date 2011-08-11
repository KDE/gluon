this.speed = 30;

this.initialize = function()
{
}

this.move = function(time)
{
    var addY = this.speed * (time/1000);

    if(this.GameObject.Key_W.isActionHeld())
    {
        this.GameObject.translate(0, addY, 0);
    } 
    else if(this.GameObject.Key_S.isActionHeld())
    {
        this.GameObject.translate(0, -addY, 0);
    }

    var pos = this.GameObject.position;
    if(pos.y() < -30)
    {
        this.GameObject.setPosition(pos.x(), -30, pos.z());
    }
    if(pos.y() > 30)
    {
        this.GameObject.setPosition(pos.x(), 30, pos.z());
    }
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;

    this.move(time);

}

this.draw = function()
{
}

