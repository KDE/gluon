var controller = null;
var bullet = null;
var speed = 30;

var justSpawned = true;

function initialize() 
{
	controller = Game.getFromScene("Background").ControllerScript;
    bullet = Game.getFromScene("Bullet");
}

function move(time)
{
    var addX = speed*(time/1000);

    if(GameObject.Key_Left.isActionHeld())
    {
        GameObject.translate(addX, 0, 0);
    }

    if(GameObject.Key_Right.isActionHeld())
    {
        GameObject.translate(-addX, 0, 0);
    }

    /*if(GameObject.Key_Up.isActionHeld())
    {
        GameObject.translate(0, addX, 0);
    }

    if(GameObject.Key_Down.isActionHeld())
    {
        GameObject.translate(0, -addX, 0);
    }*/

    var pos = GameObject.position;
    if(pos.x() < -30) 
    {
        GameObject.setPosition(-30, pos.y(), pos.z());
    }
    if(pos.x() > 30)
    {
        GameObject.setPosition(30, pos.y(), pos.z());
    }
    /*if(pos.y() > 30)
    {
        GameObject.setPosition(pos.x(), 30, pos.z());
    }
    if(pos.y() < -30)
    {
        GameObject.setPosition(pos.x(), -30, pos.z());
    }*/
    if(pos.y() < -30)
    {
        GameObject.translate(0, 5 * (time/1000), 0);
    }
    else if(justSpawned)
    {
		justSpawned = false;
	}
}

function update(time) 
{
	if(controller.paused)
		return;
	
    move(time);
    
    if(justSpawned)
    {
		GameObject.SpriteRenderer.setColor(new QColor(255, 255, 255, 128));
    }
    else
    {
		if(GameObject.Collider.isColliding())
		{
			GameObject.SpriteRenderer.setColor(new QColor(255, 0, 0));
			
			GameObject.Collider.collidesWith().destroy();
			
			Game.enemies--;
			Game.lives--;
			GameObject.Kapow.play();
			GameObject.destroy();
			
			if(Game.lives > 0)
			{
				var player = Game.clone(Game.getFromScene("Player"));
				player.setPosition(0, 50, 1);
				player.enabled = true;
			}
		}
		else
		{
			GameObject.SpriteRenderer.setColor(new QColor(255, 255, 255));
		}
    }
    
    if(GameObject.Key_Fire.isActionStarted())
    {
        var newBullet = Game.clone(bullet);
        newBullet.setPosition(GameObject.position);
        newBullet.setEnabled(true);
    }
}

function draw() 
{

}

function stop() 
{

}
