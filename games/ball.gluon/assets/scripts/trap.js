function update(time)
{
    if(Game.end)
        return;

    self.GameObject.setPosition(self.GameObject.position.x()-0.5, self.GameObject.position.y());
    if (self.GameObject.Collider.isColliding())
    {
        self.GameObject.destroy();
        Game.end = true;
    }

    if (self.GameObject.position.x() < -50)
    {
        ++Game.score;
        self.GameObject.destroy();
    }
}

self.update = update;
