var zombie,
camera,
currentSpawnRate,
timeToSpawn,
timeToSpawnChange,
spawnArea;

function initialize()
{
    self.Component.minSpawnRate = self.Component.minSpawnRate || 1000;
    self.Component.maxSpawnRate = self.Component.maxSpawnRate || 80;
    self.Component.spawnRateChange = self.Component.spawnRateChange || 2000;

    MessageHandler.subscribe("playerDied", playerDied, self);
}

function start()
{
    zombie = self.Scene.sceneContents().Zombie;
    camera = self.Scene.sceneContents().Camera;
    currentSpawnRate = self.Component.minSpawnRate;
    timeToSpawn = currentSpawnRate;
    timeToSpawnChange = self.Component.spawnRateChange;

    self.Scene.score = 0;
    self.Scene.paused = false;
    
    spawnArea = { minX: -60, minY: -60, maxX: 60, maxY: 60 }
}

function update(time)
{
    if(self.Scene.paused)
        return;
    
    timeToSpawn -= time;
    timeToSpawnChange -= time;

    if(timeToSpawn <= 0)
    {
        spawnZombie();
        timeToSpawn = currentSpawnRate;
    }

    if(timeToSpawnChange <= 0)
    {
        currentSpawnRate -= currentSpawnRate / 10;
        timeToSpawnChange = self.Component.spawnRateChange;
        
        if(currentSpawnRate < self.Component.maxSpawnRate)
        {
            currentSpawnRate = Component.maxSpawnRate;
            timeToSpawnChange = 1000000;
        }
    }
}

function cleanup()
{
    MessageHandler.unsubscribe("playerDied", playerDied, self);
}

function spawnZombie()
{
    var newZombie = Game.clone(zombie);
    newZombie.enabled = true;

    var side = Math.floor(Game.random() * 4);
    var position = new Vector3f();
    position.setZ(zombie.position.z());
    switch(side)
    {
        case 0:
            position.setY(spawnArea.maxY);
            position.setX(spawnArea.minX + Game.random() * (spawnArea.maxX - spawnArea.minX));
            break;
        case 1:
            position.setX(spawnArea.maxX);
            position.setY(spawnArea.minY + Game.random() * (spawnArea.maxY - spawnArea.minY));
            break;
        case 2:
            position.setY(spawnArea.minY);
            position.setX(spawnArea.minX + Game.random() * (spawnArea.maxX - spawnArea.minX));
            break;
        case 3:
            position.setX(spawnArea.minX);
            position.setY(spawnArea.minY + Game.random() * (spawnArea.maxY - spawnArea.minY));
            break;
    }
    position.setX(position.x() + camera.position.x());
    position.setY(position.y() + camera.position.y());
    newZombie.position = position;
}

function playerDied()
{
    self.Scene.paused = true;
}

self.initialize = initialize;
self.start = start;
self.update = update;
