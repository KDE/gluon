var speed = 30;
var life = 3000;

function start()
{
}

function update(time)
{
    var addX = speed*(time/1000)

    GameObject.translate(0, addX, 0);
    
    life -= time;
    if(life <= 0)
        GameObject.destroy();
    
    if(GameObject.Collider.isColliding())
        GameObject.destroy();
}
