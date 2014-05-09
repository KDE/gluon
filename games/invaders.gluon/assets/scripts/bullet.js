var speed = 30,
life = 3000;

function update(time)
{
    if(this.Scene.paused)
        return;
    
    var addY = speed*(time/1000)

    this.GameObject.translate(0, addY, 0);
    
    life -= time;
    if(life <= 0)
        this.GameObject.destroy();
}

self.update = update;
