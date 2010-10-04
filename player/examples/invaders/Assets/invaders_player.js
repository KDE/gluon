var controller = null;
var bullet = null;
var speed = 30;
var redness = 0;
var fireDelay = 0;

var justSpawned = true;
var alive = true;
var deathAnimTime = 439; // The length of the quiet explosion sound
var deathAnimTimeRemaining = 0;
var invincibleTime = 254;

function initialize() 
{
    controller = Game.getFromScene("Background").ControllerScript;
    bullet = Game.getFromScene("Bullet");
    deathAnimTimeRemaining = deathAnimTime;
}

function move(time)
{
    var addX = speed*(time/1000);

    if(GameObject.Key_Left.isActionHeld())
    {
        GameObject.translate(-addX, 0, 0);
    }

    if(GameObject.Key_Right.isActionHeld())
    {
        GameObject.translate(addX, 0, 0);
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
    
    if(pos.y() < -30)
    {
        GameObject.translate(0, 5 * (time/1000), 0);
    }
    else
    {
        justSpawned = false;
    }
}

function update(time) 
{
    if(alive)
    {
        if(controller.paused)
            return;
        
        move(time);

        if(!justSpawned)
        {
            fireDelay--;
            if(GameObject.Key_Fire.isActionStarted() && fireDelay <= 0)
            {
                var newBullet = Game.clone(bullet);
                newBullet.setPosition(GameObject.position);
                newBullet.setEnabled(true);
                fireDelay = 25;
            }
        }
        
        if(invincibleTime > 0)
        {
            GameObject.SpriteRenderer.material.materialColor = new QColor(255, redness, redness);
            redness += 2;
            invincibleTime -= 2;
        } 
        
        if(GameObject.BulletCollider.isColliding() || GameObject.EnemyCollider.isColliding())
        {
            if(invincibleTime <= 0)
            {
                GameObject.SpriteRenderer.material.materialColor = new QColor(255, 0, 0);
                Game.lives--;
                GameObject.Kapow.play();
                alive = false;
            }
        }
    }
    else
    {
        var scaleVal = 1 + (deathAnimTimeRemaining / deathAnimTime);
        GameObject.setScale(new QVector3D(scaleVal, scaleVal, 1));
        
        var color = GameObject.SpriteRenderer.material.materialColor;
        color.setAlpha(255 * (scaleVal - 1));
        GameObject.SpriteRenderer.material.materialColor = color;
        
        deathAnimTimeRemaining = deathAnimTimeRemaining - time;

        if(deathAnimTimeRemaining < 0)
        {
            GameObject.destroy();
            if(Game.lives > 0)
            {
                var player = Game.clone(Game.getFromScene("Player"));
                player.setPosition(0, -50, 1);
                player.enabled = true;
            }
        }
    }
}

function draw() 
{

}

function stop() 
{

}
