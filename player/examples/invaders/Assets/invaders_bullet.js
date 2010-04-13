var controller = null;
var speed = 30;
var life = 3000;

function start()
{
	controller = Game.getFromScene("Background").ControllerScript;
}

function update(time)
{
	if(controller.paused)
		return;

    var addX = speed*(time/1000)

    GameObject.translate(0,-addX, 0);
    
    life -= time;
    if(life <= 0)
        GameObject.destroy();
}
