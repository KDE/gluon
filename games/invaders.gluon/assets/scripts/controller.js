var gameEnded = false;

function initialize()
{
    Game.score = Game.score || 0;
    Scene().paused = false;
    Scene().enemies = 28;
    Scene().lives = 5;
    Scene().sceneScore = 0;

    MessageHandler.subscribe("playerDied", playerDied, self);
    MessageHandler.subscribe("enemyDied", enemyDied, self);
}

function start()
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

    createPlayer();
}

function cleanup()
{
    if(self.Scene.resetting && self.Scene.lives <= 0)
        Game.score -= self.Scene.sceneScore;
    MessageHandler.unsubscribe("playerDied", playerDied, self);
    MessageHandler.unsubscribe("enemyDied", enemyDied, self);
}

function playerDied()
{
    self.Scene.lives--;

    if(self.Scene.lives <= 0)
    {
        self.Scene.paused = true;
        self.Scene.gameEnded = true;
        MessageHandler.publish("GameEnded");
    }
    else
    {
        createPlayer();
    }
}

function enemyDied()
{
    self.Scene.enemies--;
    self.Scene.sceneScore++;
    Game.score++;

    if(self.Scene.enemies <= 0)
    {
        self.Scene.paused = true;
        self.Scene.gameEnded = true;
        MessageHandler.publish("GameEnded");
    }
}

function createPlayer()
{
    var newPlayer = Game.clone(Game.getFromScene("Player"));
    newPlayer.position = new QVector3D(0, -50, 2);
    newPlayer.enabled = true;
}

self.initialize = initialize;
self.start = start;
self.cleanup = cleanup;
