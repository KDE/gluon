this.initialize = function()
{
    this.Component.speed = this.Component.speed || 25;
}

this.start = function()
{
    this.AnimatedSprite = this.GameObject.AnimatedSpriteRendererComponent;
    this.player = this.Scene.sceneContents().Camera.Player;
    this.collider = this.GameObject.SphereCollisionComponent;
    this.dead = false;
}

this.update = function(time)
{
    if(!this.dead)
    {
        var playerPos = this.player.worldPosition();
        var thisPos = this.GameObject.position;

        var diff = new QVector3D(playerPos.x() - thisPos.x(), playerPos.y() - thisPos.y(), 0);
        diff.normalize();

        var dist = this.Component.speed * (time / 1000);
        diff.setX(diff.x() * dist);
        diff.setY(diff.y() * dist);

        this.GameObject.translate(diff);
        this.setDirection(diff);

        if(this.collider.isColliding())
        {
            this.collider.collidesWith().destroy();
            this.kill();
        }
    }
}

this.kill = function()
{
    this.GameObject.AnimatedSpriteRendererComponent.loop = false;
    this.GameObject.AnimatedSpriteRendererComponent.animation = 6;
    this.dead = true;
}

this.setDirection = function(direction)
{
    var angle = QVector3D.dotProduct(direction, new QVector3D(0, 1, 0));
    var dir = -1;
    if(direction.x() < 0)
    {
        if(angle > 0.75)
            dir = 7;
        else if(angle > 0.25)
            dir = 0;
        else if(angle > -0.25)
            dir = 1;
        else if(angle > -0.75)
            dir = 2;
        else
            dir = 3;
    }
    else
    {
        if(angle > 0.75)
            dir = 7;
        else if(angle > 0.25)
            dir = 6;
        else if(angle > -0.25)
            dir = 5;
        else if(angle > -0.75)
            dir = 4;
        else
            dir = 3;
    }
    this.AnimatedSprite.direction = dir;
}