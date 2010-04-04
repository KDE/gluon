var spawned = false;

function update(time)
{
    if(!spawned)
    {
        var enemy = Game.getFromScene("Enemy");    
        for(var i = -3; i < 3; ++i)
        {
            var newEnemy = Game.clone(enemy);
            
            newEnemy.setPosition(10*i, -30, 2);
            newEnemy.enabled = true;
        }
        spawned = true;
    }
}