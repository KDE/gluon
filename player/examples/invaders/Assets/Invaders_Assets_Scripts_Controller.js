this.gameEnded = false;

this.initialize = function()
{
    this.Scene.paused = false;
    MessageHandler.subscribe("playerDied", this.playerDied, this);
    MessageHandler.subscribe("enemyDied", this.enemyDied, this);
}

this.start = function()
{
    this.Scene.enemies = 28;
    this.Scene.lives = 5;

    var enemy = Game.getFromScene("Enemy");
    for(var y = 40; y >= 10; y -= 10)
    {
        for(var x = -30; x <= 30; x += 10)
        {
            var newEnemy = Game.clone(enemy);
            newEnemy.position = new QVector3D(x, y, 1);
            newEnemy.enabled = true;
        }
    }

    this.createPlayer();
}

this.update = function(time)
{
    if(this.gameEnded)
    {
        if(this.GameObject.Key_Continue.isActionStopped())
        {
            Game.resetCurrentScene();
        }
    }
    else
    {
        if(this.GameObject.Key_Pause.isActionStarted())
        {
            this.Scene.paused = !this.Scene.paused;
        }
    }
}

this.playerDied = function()
{
    this.Scene.lives--;
    
    if(this.Scene.lives <= 0)
    {
        this.Scene.paused = true;
        this.gameEnded = true;
    }
    else
    {
        this.createPlayer();
    }
}

this.enemyDied = function()
{
    this.Scene.enemies--;
    Game.score++;
    
    if(this.Scene.enemies <= 0)
    {
        this.Scene.paused = true;
        this.gameEnded = true;
    }
}

this.createPlayer = function()
{
    var newPlayer = Game.clone(Game.getFromScene("Player"));
    newPlayer.position = new QVector3D(0, -50, 2);
    newPlayer.enabled = true;
}
