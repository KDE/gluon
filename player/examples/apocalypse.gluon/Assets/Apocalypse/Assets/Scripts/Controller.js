this.initialize = function()
{
    this.Component.minSpawnRate = this.Component.minSpawnRate || 1000;
    this.Component.maxSpawnRate = this.Component.maxSpawnRate || 80;
    this.Component.spawnRateChange = this.Component.spawnRateChange || 2000;
}

this.start = function()
{
    this.zombie = this.Scene.sceneContents().Zombie;
    this.camera = this.Scene.sceneContents().Camera;
    this.currentSpawnRate = this.Component.minSpawnRate;
    this.timeToSpawn = this.currentSpawnRate;
    this.timeToSpawnChange = this.Component.spawnRateChange;
    
    this.spawnArea = { minX: -60, minY: -60, maxX: 60, maxY: 60 }
}

this.update = function(time)
{
    this.timeToSpawn -= time;
    this.timeToSpawnChange -= time;

    //this.GameObject.debug(this.timeToSpawn);
    //this.GameObject.debug(this.timeToSpawnChange);
    if(this.timeToSpawn <= 0)
    {
	this.spawnZombie();
	this.timeToSpawn = this.currentSpawnRate;
    }
    
    if(this.timeToSpawnChange <= 0)
    {
	this.currentSpawnRate -= this.currentSpawnRate / 10;
        this.timeToSpawnChange = this.Component.spawnRateChange;
        
        if(this.currentSpawnRate < this.Component.minSpawnRate)
        {
            this.currentSpawnRate = this.Component.minSpawnRate;
            this.timeToSpawnChange = 1000000;
        }
    }
}

this.spawnZombie = function()
{
    var newZombie = Game.clone(this.zombie);
    newZombie.enabled = true;

    var side = Math.floor(Game.random() * 4);
    var position = new QVector3D();
    position.setZ(this.zombie.position.z());
    switch(side)
    {
        case 0:
            position.setY(this.spawnArea.maxY);
            position.setX(this.spawnArea.minX + Game.random() * (this.spawnArea.maxX - this.spawnArea.minX));
            break;
        case 1:
            position.setX(this.spawnArea.maxX);
            position.setY(this.spawnArea.minY + Game.random() * (this.spawnArea.maxY - this.spawnArea.minY));
            break;
        case 2:
            position.setY(this.spawnArea.minY);
            position.setX(this.spawnArea.minX + Game.random() * (this.spawnArea.maxX - this.spawnArea.minX));
            break;
        case 3:
            position.setX(this.spawnArea.minX);
            position.setY(this.spawnArea.minY + Game.random() * (this.spawnArea.maxY - this.spawnArea.minY));
            break;
    }
    position.setX(position.x() + this.camera.position.x());
    position.setY(position.y() + this.camera.position.y());
    newZombie.position = position;
}
