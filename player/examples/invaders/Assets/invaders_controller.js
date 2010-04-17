function initialize()
{
	Component.paused = false;
}

function start()
{
    Game.enemies = 28;
    Game.lives = 5;
    
    var enemy = Game.getFromScene("Enemy");
    for(var y = 40; y >= 10; y -= 10)
    {
        for(var x = -30; x <= 30; x += 10)
        {
            var newEnemy = Game.clone(enemy);
            
            newEnemy.setPosition(x, y, 2);
            newEnemy.enabled = true;
        }
    }
    
    var player = Game.clone(Game.getFromScene("Player"));
    player.setPosition(0, -50, 1);
    player.enabled = true;
}

function update(time)
{
    if(Game.enemies <= 0)
    {
        //Win
        Game.getFromScene("GameWon").setPosition(0, 0, 10);
        Component.paused = true;
    }
    else if(Game.lives <= 0)
    {
        //Game over
        Game.getFromScene("GameOver").setPosition(0, 0, 10);
        Component.paused = true;
    }
}
