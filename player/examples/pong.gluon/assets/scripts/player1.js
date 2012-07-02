var speed = 30,
cameraHeight,
player1Height,
downcollide,
upcollide;

function initialize()
{
    cameraHeight = self.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.height();
    player1Height = self.Scene.sceneContents().Player1.Player1SpriteRenderer.size.height();
    downcollide = -cameraHeight/2 + player1Height/2;
    upcollide = cameraHeight/2 - player1Height/2;
}

function move(time)
{
    var addY = speed * (time/1000);

    if(self.GameObject.Key_W.isActionHeld())
    {
        self.GameObject.translate(0, addY, 0);
    } 
    else if(self.GameObject.Key_S.isActionHeld())
    {
        self.GameObject.translate(0, -addY, 0);
    }

    var pos = self.GameObject.position;

    if(pos.y() < downcollide)
    {
        self.GameObject.setPosition(pos.x(), downcollide, pos.z());
    }
    else if(pos.y() > upcollide)
    {
        self.GameObject.setPosition(pos.x(), upcollide, pos.z());
    }
}

function update(time)
{
    if(self.Scene.paused)
        return;

    move(time);

}

self.initialize = initialize;
self.update = update;
