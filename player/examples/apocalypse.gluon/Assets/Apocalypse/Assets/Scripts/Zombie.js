this.initialize = function()
{
    //this.player = this.GameObject.parentGameObject().Camera.Player;
    //this.GameObject.debug(this.GameObject.parentGameObject().Camera.Player);
    this.Component.speed = this.Component.speed || 25;
}

this.start = function()
{
    this.player = this.Scene.sceneContents().Camera;
}

this.update = function(time)
{
    var playerPos = this.player.position;
    var thisPos = this.GameObject.position;
    
    var diff = new QVector3D(playerPos.x() - thisPos.x(), playerPos.y() - thisPos.y(), 0);
    diff.normalize();
    
    var dist = this.Component.speed * (time / 1000);
    //this.GameObject.debug(dist);
    diff.setX(diff.x() * dist);
    diff.setY(diff.y() * dist);
    
    //this.GameObject.debug(diff);
    this.GameObject.translate(diff);
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
