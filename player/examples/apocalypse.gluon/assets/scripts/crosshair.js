this.initialize = function()
{
    this.Component.mouseSpeed = this.Component.mouseSpeed || 0.05;
    this.Component.fireInterval = this.Component.fireInterval || 20;
    this.Mouse = this.GameObject.Button_Fire;
    this.zDepth = this.GameObject.position.z();
    this.radius = 45;
}

this.start = function()
{
    this.fireInterval = this.Component.fireInterval;
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;
    
    var x = this.GameObject.Button_Fire.normalizedXAxis() * this.radius;
    var y = -this.GameObject.Button_Fire.normalizedYAxis() * this.radius;

    this.GameObject.setPosition(x, y, this.zDepth);
    
    if(this.GameObject.Button_Fire.isActionHeld())
    {
        this.fireInterval -= time;
        if(this.fireInterval <= 0)
        {
            MessageHandler.publish("fireBullet");
            this.fireInterval = this.Component.fireInterval;
        }
    }
}
