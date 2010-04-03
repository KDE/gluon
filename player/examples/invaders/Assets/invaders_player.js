function start() 
{
}

function update(time) 
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
        GameObject.setPosition(-30, pos.y(), pos.z());
    if(pos.x() > 30)
        GameObject.setPosition(30, pos.y(), pos.z());
    if(pos.y() > 30)
        GameObject.setPosition(pos.x(), 30, pos.z());
    if(pos.y() < -30)
        GameObject.setPosition(pos.x(), -30, pos.z());
    
    if(GameObject.Collider.isColliding())
    {
        GameObject.SpriteRenderer.setColor(new QColor(255, 0, 0));
    }
    else
    {
        GameObject.SpriteRenderer.setColor(new QColor(255, 255, 255));
    }
    
    if(GameObject.Key_Fire.isActionHeld())
    {
        GameObject.FireSound.play();
        
        var bullet = Game.clone(Game.getFromScene("Bullet"));
        bullet.setPosition(GameObject.position);
        bullet.Script.enabled = true;
    }
}

function draw() 
{

}

function stop() 
{

}
