this.speed = 10;
this.life = 3000;
this.angle = 90;
this.direction = 0;
this.cameraWidth;
this.player1Width;
this.player2Width;
this.leftcollide;
this.rightcollide;

this.initialize = function()
{
    this.cameraWidth = this.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.width();
    this.player1Width = this.Scene.sceneContents().Player1.Player1SpriteRenderer.size.width();
    this.player2Width = this.Scene.sceneContents().Player2.Player2SpriteRenderer.size.width();
    this.leftcollide = -this.cameraWidth + (this.player1Width);
    this.rightcollide = this.cameraWidth - (this.player2Width);    
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;
    
    var addX = this.speed*(time/1000);
    var addY = addX * (1 - this.angle/90);

    var pos = this.GameObject.position;
    if (this.direction == 0)
    {
        if (pos.x() < this.leftcollide)
        {
            this.direction = 1;
        }
        else
        {
            this.GameObject.translate(-addX, addY, 0);
        }
    }
    else if(this.direction == 1)
    {
        if (pos.x() > this.rightcollide)
        {
            this.direction = 0;
        }
        else
        {
            this.GameObject.translate(addX, addY, 0);
        }
    }
}
