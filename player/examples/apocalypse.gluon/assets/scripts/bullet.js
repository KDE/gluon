
this.initialize = function()
{
    this.Component.direction = this.Component.direction || new QVector3D(0.0, 1.0, 0.0);
    this.Component.speed = this.Component.speed || 50.0;
    this.Component.life = this.Component.life || 10;
}

this.start = function()
{
    this.life = this.Component.life;
}

this.update = function(time)
{
    var move = new QVector3D();
    move.setX(this.Component.direction.x() * (this.Component.speed * (time/1000)));
    move.setY(this.Component.direction.y() * (this.Component.speed * (time/1000)));
    this.GameObject.translate(move);

    this.life -= (time/1000);
    if(this.life <= 0)
        this.GameObject.destroy();
}

this.draw = function(timeLapse)
{
}

this.stop = function()
{
}

this.cleanup = function()
{
}
