this.initialize = function()
{
    this.Component.speed = this.Component.speed || 100;
}

this.start = function()
{
}

this.update = function(time)
{
    this.GameObject.translate(0, ths.Component.speed * (time / 1000), 0);
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
