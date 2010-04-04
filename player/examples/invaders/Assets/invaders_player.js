var g_bullet;

function initialize() 
{
    g_bullet = Game.getFromScene("Bullet");
    Game.setProperty("lives", 5);
}

function move(time)
{
    if(GameObject.Key_Left.isActionHeld())
    {
        GameObject.translate(10*(time/1000), 0, 0);
    }

    if(GameObject.Key_Right.isActionHeld())
    {
        GameObject.translate(-10*(time/1000), 0, 0);
    }

    if(GameObject.Key_Up.isActionHeld())
    {
        GameObject.translate(0, 10*(time/1000), 0);
    }

    if(GameObject.Key_Down.isActionHeld())
    {
        GameObject.translate(0, -10*(time/1000), 0);
    }

    var pos = GameObject.position;
    if(pos.x() < -30) 
    {
        GameObject.setPosition(-30, pos.y(), pos.z());
    }
    if(pos.x() > 30)
    {
        GameObject.setPosition(30, pos.y(), pos.z());
    }
    if(pos.y() > 30)
    {
        GameObject.setPosition(pos.x(), 30, pos.z());
    }
    if(pos.y() < -30)
    {
        GameObject.setPosition(pos.x(), -30, pos.z());
    }
}

function update(time) 
{
    move(time);
    
    if(GameObject.Collider.isColliding())
    {
        GameObject.SpriteRenderer.setColor(new QColor(255, 0, 0));
        Game.setProperty("lives", Game.property("lives") - 1);
        if(Game.property("lives") <= 0)
        {
            GameObject.destroy();
        }
    }
    else
    {
        GameObject.SpriteRenderer.setColor(new QColor(255, 255, 255));
    }
    
    if(GameObject.Key_Fire.isActionStarted())
    {
        var bullet = Game.clone(g_bullet);
        bullet.setPosition(GameObject.position);
        bullet.setEnabled(true);
    }
}

function draw() 
{

}

function stop() 
{

}
