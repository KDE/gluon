var xdir = 10;
var ydir = 5;

var controller = null;
var bullet = null;
var bulletChance = 0.005;
var alive = true;

function start() {
	controller = Game.getFromScene("Background").ControllerScript;
    bullet = Game.getFromScene("Bullet");
}

function update(time) {
	if(controller.paused)
		return;

    GameObject.translate(xdir * (time/1000), 0, 0);
    
    var position = GameObject.position;
    if(position.x() > 35 || position.x() < -35) {
        GameObject.translate(0, ydir, 0);
        xdir = -xdir;
    }
    
    if(GameObject.BulletCollider.isColliding())
    {
		alive = false;
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