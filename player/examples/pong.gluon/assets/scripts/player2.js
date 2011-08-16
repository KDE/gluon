this.speed = 30;
this.cameraHeight;
this.playerHeight;
this.downcollide;
this.upcollide;

this.initialize = function()
{
    this.cameraHeight = this.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.height();
    this.player1Height = this.Scene.sceneContents().Player2.Player2SpriteRenderer.size.height();
    this.downcollide = -this.cameraHeight/2 + this.player1Height/2;
    this.upcollide = this.cameraHeight/2 - this.player1Height/2;
}

this.move = function(time)
{
    var addY = this.speed * (time/1000);

    if(this.GameObject.Key_Up.isActionHeld())
    {
        this.GameObject.translate(0, addY, 0);
    } 
    else if(this.GameObject.Key_Down.isActionHeld())
    {
        this.GameObject.translate(0, -addY, 0);
    }

    var pos = this.GameObject.position;

    if(pos.y() < this.downcollide)
    {   
        this.GameObject.setPosition(pos.x(), this.downcollide, pos.z());
    }   
    else if(pos.y() > this.upcollide)
    {   
        this.GameObject.setPosition(pos.x(), this.upcollide, pos.z());
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

