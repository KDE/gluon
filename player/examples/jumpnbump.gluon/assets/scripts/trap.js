this.initialize = function()
{
}

this.update = function(time)
{
    this.GameObject.setPosition(this.GameObject.position.x()-0.5, this.GameObject.position.y());
    if (this.GameObject.Collider.isColliding()) {
        this.GameObject.destroy();
        Game.end = true;
    }

    if (this.GameObject.position.x() < -50)
    {
        ++Game.score;
        this.GameObject.destroy();
    }
}

this.draw = function()
{
}
