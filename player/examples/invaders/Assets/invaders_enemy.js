var xdir = 10;
var ydir = -5;

var bullet = null;
var bulletChance = 0.005;

function start() {
    bullet = Game.getFromScene("Bullet");
}

function update(time) {
    GameObject.translate(xdir * (time/1000), 0, 0);
    
    var position = GameObject.position;
    if(position.x() > 35 || position.x() < -35) {
        GameObject.translate(0, ydir, 0);
        xdir = -xdir;
    }
    
    if(GameObject.BulletCollider.isColliding())
    {
        GameObject.destroy();
        GameObject.BulletCollider.collidesWith().destroy();
        GameObject.Kapow.play();
        Game.enemies--;
    }
    
    if(Math.random() < bulletChance)
    {
        var newBullet = Game.clone(bullet);
        newBullet.position = GameObject.position;
        newBullet.enabled = true;
        newBullet.Collider.collisionGroup = 0;
        newBullet.rotate(180, new QVector3D(0, 0, 1));
    }
}