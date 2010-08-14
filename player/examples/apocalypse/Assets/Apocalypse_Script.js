function initialize()
{
    Component.mouseSpeed = Component.mouseSpeed || 10;
}

function start()
{
}

function update(time)
{
    var x = GameObject.Mouse_Left.xAxis() / Component.mouseSpeed;
    var y = GameObject.Mouse_Left.yAxis() / Component.mouseSpeed;
  
    GameObject.setPosition(x, y, 0);
    
    if(GameObject.Mouse_Left.isActionHeld())
    {
	GameObject.SpriteRenderer.setColor(255, 0, 0);
    }
    else if(GameObject.Mouse_Right.isActionHeld())
    {
	GameObject.SpriteRenderer.setColor(0, 255, 0);
    }
    else if(GameObject.Mouse_Middle.isActionHeld())
    {
	GameObject.SpriteRenderer.setColor(0, 0, 255);
    }
    else
    {
	GameObject.SpriteRenderer.setColor(255, 255, 255);
    }
}

function draw(timeLapse)
{
}

function stop()
{
}

function cleanup()
{
}
