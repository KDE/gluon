var Mouse,
zDepth,
radius,
fireInterval;

function initialize()
{
    self.Component.mouseSpeed = self.Component.mouseSpeed || 0.05;
    self.Component.fireInterval = self.Component.fireInterval || 20;
    Mouse = self.GameObject.Button_Fire;
    zDepth = self.GameObject.position.z();
    radius = 45;
}

function start()
{
    fireInterval = self.Component.fireInterval;
}

function update(time)
{
    if(self.Scene.paused)
        return;
    
    var x = self.GameObject.Button_Fire.normalizedXAxis() * radius;
    var y = -self.GameObject.Button_Fire.normalizedYAxis() * radius;

    self.GameObject.setPosition(x, y, zDepth);
    
    if(self.GameObject.Button_Fire.isActionHeld())
    {
        fireInterval -= time;
        if(fireInterval <= 0)
        {
            MessageHandler.publish("fireBullet");
            fireInterval = self.Component.fireInterval;
        }
    }
}

self.initialize = initialize;
self.start = start;
self.update = update;
