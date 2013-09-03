var xdir = 10,
ydir = -5,

bullet = null,
bulletChance = 0.005,
alive = true,
deathAnimTime = 439; // The length of the quiet explosion sound
var deathAnimTimeRemaining = deathAnimTime;

function start()
{
    bullet = Game.getFromScene("Bullet");    
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

    self.GameObject.translate(xdir * (time/1000), 0, 0);

    var position = self.GameObject.position;
    if(position.x() > 35 || position.x() < -35) {
            self.GameObject.translate(0, ydir, 0);
            xdir = -xdir;
    }

    if(self.GameObject.BulletCollider.isColliding() || self.GameObject.PlayerCollider.isColliding())
    {
        if(self.GameObject.BulletCollider.isColliding())
            self.GameObject.BulletCollider.collidesWith().destroy();

        alive = false;
        self.GameObject.SpriteRenderer.setMaterial("Invaders/Assets/Main Material/Enemy_Fade");
        self.GameObject.Kapow.play();
    }

    if(Game.random() < bulletChance)
    {
        var newBullet = Game.clone(bullet);
        newBullet.position = self.GameObject.position;
        newBullet.enabled = true;
        newBullet.Collider.collisionGroup = 2;
        newBullet.rotate(180, new Vector3f(0, 0, 1));
    }
}

function playDeathAnim(time)
{
    var scaleVal = 1 + (deathAnimTimeRemaining / deathAnimTime);
    self.GameObject.setScale(new Vector3f(scaleVal, scaleVal, 1));
    
    var color = self.GameObject.SpriteRenderer.material.materialColor;
    color.setAlpha(255 * (scaleVal - 1));
    self.GameObject.SpriteRenderer.material.materialColor = color;
    
    deathAnimTimeRemaining = deathAnimTimeRemaining - time;
    if(deathAnimTimeRemaining < 0)
    {
        self.GameObject.destroy();
        MessageHandler.publish("enemyDied");
    }
}

self.start = start;
self.update = update;
