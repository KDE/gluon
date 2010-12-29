this.controller = null;
this.bullet = null;
this.speed = 30;
this.redness = 0;
this.fireDelay = 0;

this.justSpawned = true;
this.alive = true;
this.deathAnimTime = 439; // The length of the quiet explosion sound
this.deathAnimTimeRemaining = 0;
this.invincibleTime = 254;

this.initialize = function() 
{
    this.controller = this.Game.getFromScene("Background").ControllerScript;
    this.bullet = this.Game.getFromScene("Bullet");
    this.deathAnimTimeRemaining = this.deathAnimTime;
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
    if(this.alive)
    {
        if(this.controller.paused)
            return;
        
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
            this.GameObject.SpriteRenderer.material.materialColor = new QColor(255, this.redness, this.redness);
            this.redness += 2;
            this.invincibleTime -= 2;
        } 
        
        if(this.GameObject.BulletCollider.isColliding() || this.GameObject.EnemyCollider.isColliding())
        {
            if(this.invincibleTime <= 0)
            {
                this.GameObject.SpriteRenderer.material.materialColor = new QColor(255, 0, 0);
                this.Game.lives--;
                this.GameObject.Kapow.play();
                this.alive = false;
            }
        }
    }
    else
    {
        var scaleVal = 1 + (this.deathAnimTimeRemaining / this.deathAnimTime);
        this.GameObject.setScale(new QVector3D(scaleVal, scaleVal, 1));
        
        /*var color = this.GameObject.SpriteRenderer.material.materialColor;
        color.setAlpha(255 * (scaleVal - 1));
        this.GameObject.SpriteRenderer.material.materialColor = color;*/
        
        this.deathAnimTimeRemaining = this.deathAnimTimeRemaining - time;

        if(this.deathAnimTimeRemaining < 0)
        {
            this.GameObject.destroy();
            if(this.Game.lives > 0)
            {
                var player = this.Game.clone(this.Game.getFromScene("Player"));
                player.setPosition(0, -50, 1);
                player.enabled = true;
            }
        }
    }
}
