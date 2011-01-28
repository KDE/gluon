this.xdir = 10;
this.ydir = -5;

this.bullet = null;
this.bulletChance = 0.005;
this.alive = true;
this.deathAnimTime = 439; // The length of the quiet explosion sound
this.deathAnimTimeRemaining = this.deathAnimTime;

this.start = function()
{
    this.bullet = this.Game.getFromScene("Bullet");    
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
        
    this.GameObject.translate(this.xdir * (time/1000), 0, 0);
    
    var position = this.GameObject.position;
    if(position.x() > 35 || position.x() < -35) {
            this.GameObject.translate(0, this.ydir, 0);
            this.xdir = -this.xdir;
    }
    
    if(this.GameObject.BulletCollider.isColliding() || this.GameObject.PlayerCollider.isColliding())
    {
	if(this.GameObject.BulletCollider.isColliding())
	    this.GameObject.BulletCollider.collidesWith().destroy();
	
        this.alive = false;
        this.GameObject.SpriteRenderer.setMaterial("Invaders/Assets/Material/Enemy_Fade");
        this.GameObject.Kapow.play();
    }
        
    if(this.Game.random() < this.bulletChance)
    {
        var newBullet = this.Game.clone(this.bullet);
        newBullet.position = this.GameObject.position;
        newBullet.enabled = true;
        newBullet.Collider.collisionGroup = 2;
        newBullet.rotate(180, new QVector3D(0, 0, 1));
    }
}

this.playDeathAnim = function(time)
{
    var scaleVal = 1 + (this.deathAnimTimeRemaining / this.deathAnimTime);
    this.GameObject.setScale(new QVector3D(scaleVal, scaleVal, 1));
    
    var color = this.GameObject.SpriteRenderer.material.materialColor;
    color.setAlpha(255 * (scaleVal - 1));
    this.GameObject.SpriteRenderer.material.materialColor = color;
    
    this.deathAnimTimeRemaining = this.deathAnimTimeRemaining - time;
    if(this.deathAnimTimeRemaining < 0)
    {
        this.GameObject.destroy();
        this.MessageHandler.publish("enemyDied");
    }
}
