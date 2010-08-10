function initialize()
{
}

function start()
{
}

function update(time)
{
    //GameObject.debug("Mouse X: " + GameObject.Mouse_Left.xAxis());
    //GameObject.debug("Mouse Y: " + GameObject.Mouse_Left.yAxis());
    var x = (GameObject.Mouse_Left.xAxis() / 1920) * -150;
    var y = (GameObject.Mouse_Left.yAxis() / 1200) * 150;
  
    GameObject.setPosition(x, y, 0);
    
    if(GameObject.Mouse_Left.isActionHeld())
    {
	GameObject.SpriteRenderer.setColor(255.0, 0.0, 0.0);
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
