var speed = 10,
life = 3000,
angle = 90,
direction = 0,
cameraWidth,
player1Width,
player2Width,
leftcollide,
rightcollide;

function initialize()
{
    cameraWidth = self.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.width();
    player1Width = self.Scene.sceneContents().Player1.Player1SpriteRenderer.size.width();
    player2Width = self.Scene.sceneContents().Player2.Player2SpriteRenderer.size.width();
    leftcollide = -cameraWidth + player1Width;
    rightcollide = cameraWidth - player2Width;
}

function update(time)
{
    if(self.Scene.paused)
        return;
    
    var addX = speed*(time/1000);
    var addY = addX * (1 - angle/90);

    var pos = self.GameObject.position;
    if (direction == 0)
    {
        if (pos.x() < leftcollide)
        {
            direction = 1;
        }
        else
        {
            GameObject.translate(-addX, addY, 0);
        }
    }
    else if(direction == 1)
    {
        if (pos.x() > rightcollide)
        {
            direction = 0;
        }
        else
        {
            GameObject.translate(addX, addY, 0);
        }
    }
}

self.initialize = initialize;
self.update = update;
