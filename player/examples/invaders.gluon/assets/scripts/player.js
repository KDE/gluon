var controller = null,
bullet = null,
camera = null,
speed = 30,
redness = 0,
fireDelay = 0,

justSpawned = true,
alive = true,
deathAnimTime = 439; // The length of the quiet explosion sound
var deathAnimTimeRemaining = deathAnimTime,
invincibleTime = 254;

function initialize()
{
    bullet = Game.getFromScene("Bullet");
    camera = Game.getFromScene("Camera").Camera;
}

function move(time)
{
    var addX = speed * (time/1000);

    if(self.GameObject.Key_Left.isActionHeld())
    {
        self.GameObject.translate(-addX, 0, 0);
    }

    if(self.GameObject.Key_Right.isActionHeld())
    {
        self.GameObject.translate(addX, 0, 0);
    }

    var pos = self.GameObject.position;
    if(pos.x() < -30)
    {
        self.GameObject.setPosition(-30, pos.y(), pos.z());
    }
    if(pos.x() > 30)
    {
        self.GameObject.setPosition(30, pos.y(), pos.z());
    }

    if(pos.y() < -30)
    {
        self.GameObject.translate(0, 5 * (time/1000), 0);
    }
    else
    {
        justSpawned = false;
    }
}

function update(time)
{
    if(self.Scene.paused)
        return;

    if(!alive)
    {
        playDeathAnim(time);
        return; 
    }
    
    move(time);

    if(!justSpawned)
    {
        fireDelay--;
        if(self.GameObject.Key_Fire.isActionStarted() && fireDelay <= 0)
        {
            var newBullet = Game.clone(bullet);
            newBullet.setPosition(self.GameObject.position);
            newBullet.setEnabled(true);
            fireDelay = 25;
        }
    }

    if(invincibleTime > 0)
    {
        camera.renderTargetMaterial.materialColor = new QColor(255, 255 - invincibleTime, 255 - invincibleTime);
        invincibleTime -= 2;
    }

    if(self.GameObject.BulletCollider.isColliding() || self.GameObject.EnemyCollider.isColliding())
    {
        if(invincibleTime <= 0)
        {
            self.GameObject.Kapow.play();
            alive = false;
        }
    }
}

function playDeathAnim(time)
{
    var value = deathAnimTimeRemaining / deathAnimTime;
    self.GameObject.setScale(new Vector3f(1 + value, 1 + value, 1));
    camera.renderTargetMaterial.materialColor = new QColor(255, 255 * value, 255 * value);    
    
    deathAnimTimeRemaining = deathAnimTimeRemaining - time;
    if(deathAnimTimeRemaining < 0)
    {
        self.GameObject.destroy();
        MessageHandler.publish("playerDied");
    }
}

self.initialize = initialize;
self.update = update;
