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

            newEnemy.setPosition(x, y);
            newEnemy.enabled = true;
        }
    }

    var player = Game.clone(Game.getFromScene("Player"));
    player.setPosition(0, -50);
    player.enabled = true;
}

function update(time)
{
    if(Game.enemies <= 0)
    {
        //Win
        Game.getFromScene("GameWon").setPosition(0, 0);
        Game.getFromScene("Camera").Camera.renderTargetMaterial.materialColor = new QColor(0, 255, 0);
        Component.paused = true;
    }
    else if(Game.lives <= 0)
    {
        //Game over
        Game.getFromScene("GameOver").setPosition(0, 0);
        Game.getFromScene("Camera").Camera.renderTargetMaterial.materialColor = new QColor(255, 0, 0);
        Component.paused = true;
    }

    if(Component.paused)
    {
        if(GameObject.Continue.isActionStarted())
        {
            Game.resetCurrentScene();
        }
    }
}
