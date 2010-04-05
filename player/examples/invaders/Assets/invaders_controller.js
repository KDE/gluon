

function start()
{
    var enemy = Game.getFromScene("Enemy");
    for(var y = -30; y <= 0; y += 10)
    {
        for(var x = -30; x <= 30; x += 10)
        {
            var newEnemy = Game.clone(enemy);
            
            newEnemy.setPosition(x, y, 2);
            newEnemy.enabled = true;
        }
    }
}