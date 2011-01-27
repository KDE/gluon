this.controller = null;
this.bullet = null;
this.camera = null;
this.speed = 30;
this.redness = 0;
this.fireDelay = 0;

this.justSpawned = true;
this.alive = true;
this.deathAnimTime = 439; // The length of the quiet explosion sound
this.deathAnimTimeRemaining = this.deathAnimTime;
this.invincibleTime = 254;

this.initialize = function()
{
    this.bullet = this.Game.getFromScene("Bullet");
    this.camera = this.Game.getFromScene("Camera").Camera;
}

this.move = function(time)
{
    var addX = this.speed * (time/1000);

    if(this.GameObject.Key_Left.isActionHeld())
    {
        this.GameObject.translate(-addX, 0, 0);
    }

    if(this.GameObject.Key_Right.isActionHeld())
    {
        this.GameObject.translate(addX, 0, 0);
    }

    var pos = this.GameObject.position;
    if(pos.x() < -30)
    {
        this.GameObject.setPosition(-30, pos.y(), pos.z());
    }
    if(pos.x() > 30)
    {
        this.GameObject.setPosition(30, pos.y(), pos.z());
    }

    if(pos.y() < -30)
    {
        this.GameObject.translate(0, 5 * (time/1000), 0);
    }
    else
    {
        this.justSpawned = false;
    }
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;

    if(!this.alive)
    {
        this.playDeathAnim(time);
        return; 
    }
    
    this.move(time);

    if(!this.justSpawned)
    {
        this.fireDelay--;
        if(this.GameObject.Key_Fire.isActionStarted() && this.fireDelay <= 0)
        {
            var newBullet = this.Game.clone(this.bullet);
            newBullet.setPosition(this.GameObject.position);
            newBullet.setEnabled(true);
            this.fireDelay = 25;
        }
    }

    if(this.invincibleTime > 0)
    {
        this.camera.renderTargetMaterial.materialColor = new QColor(255, 255 - this.invincibleTime, 255 - this.invincibleTime);
        this.invincibleTime -= 2;
    }

    if(this.GameObject.BulletCollider.isColliding() || this.GameObject.EnemyCollider.isColliding())
    {
        if(this.invincibleTime <= 0)
        {
            this.GameObject.Kapow.play();
            this.alive = false;
        }
    }
}

this.playDeathAnim = function(time)
{
    var value = this.deathAnimTimeRemaining / this.deathAnimTime;
    this.GameObject.setScale(new QVector3D(1 + value, 1 + value, 1));
    this.camera.renderTargetMaterial.materialColor = new QColor(255, 255 - (255 * value), 255 - (255 * value));    
    
    this.deathAnimTimeRemaining = this.deathAnimTimeRemaining - time;
    if(this.deathAnimTimeRemaining < 0)
    {
        this.GameObject.destroy();
        this.MessageHandler.publish("playerDied");
    }
}
