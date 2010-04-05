var xdir = 10;
var ydir = 5;

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
    }
}