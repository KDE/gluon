var collider,
life;

function initialize()
{
    self.Component.direction = self.Component.direction || new QVector3D(0.0, 1.0, 0.0);
    self.Component.speed = self.Component.speed || 50.0;
    self.Component.life = self.Component.life || 10;
}

function start()
{
    collider = self.GameObject.SphereCollisionComponent;
    life = self.Component.life;
}

function update(time)
{
    if(self.Scene.paused)
        return;
    
    var move = new QVector3D();
    move.setX(self.Component.direction.x() * (self.Component.speed * (time/1000)));
    move.setY(self.Component.direction.y() * (self.Component.speed * (time/1000)));
    self.GameObject.translate(move);

    life -= (time/1000);
    if(life <= 0)
        self.GameObject.destroy();
}

self.initialize = initialize;
self.start = start;
self.update = update;
