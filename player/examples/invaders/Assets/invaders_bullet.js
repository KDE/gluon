var speed = 30;

function start()
{
    print("Starting bullet");
}

function update(time)
{
    var addX = speed*(time/1000)

    GameObject.translate(0,-addX, 0);
}
