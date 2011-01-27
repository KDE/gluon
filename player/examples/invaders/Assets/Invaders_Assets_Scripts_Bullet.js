this.speed = 30;
this.life = 3000;

this.update = function(time)
{
    if(this.Scene.paused)
        return;
    
    var addX = this.speed*(time/1000)

    this.GameObject.translate(0, addX, 0);
    
    this.life -= time;
    if(this.life <= 0)
        this.GameObject.destroy();
    
    if(this.GameObject.Collider.isColliding())
        this.GameObject.destroy();
}
