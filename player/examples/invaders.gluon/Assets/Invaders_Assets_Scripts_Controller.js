this.gameEnded = false;

this.initialize = function()
{
    Game.score = Game.score || 0;
    this.Scene.paused = false;
    this.Scene.enemies = 28;
    this.Scene.lives = 5;
    this.Scene.sceneScore = 0;
    
    MessageHandler.subscribe("playerDied", this.playerDied, this);
    MessageHandler.subscribe("enemyDied", this.enemyDied, this);
}

this.start = function()
{
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

this.cleanup = function()
{
    if(this.Scene.resetting && this.Scene.lives <= 0)
        Game.score -= this.Scene.sceneScore;
    MessageHandler.unsubscribe("playerDied", this.playerDied, this);
    MessageHandler.unsubscribe("enemyDied", this.enemyDied, this);
}

this.playerDied = function()
{
    this.Scene.lives--;
    
    if(this.Scene.lives <= 0)
    {
        this.Scene.paused = true;
        this.Scene.gameEnded = true;
        MessageHandler.publish("GameEnded");
    }
    else
    {
        this.createPlayer();
    }
}

this.enemyDied = function()
{
    this.Scene.enemies--;
    this.Scene.sceneScore++;
    Game.score++;
    
    if(this.Scene.enemies <= 0)
    {
        this.Scene.paused = true;
        this.Scene.gameEnded = true;
        MessageHandler.publish("GameEnded");
    }
}

this.createPlayer = function()
{
    var newPlayer = Game.clone(Game.getFromScene("Player"));
    newPlayer.position = new QVector3D(0, -50, 2);
    newPlayer.enabled = true;
}
