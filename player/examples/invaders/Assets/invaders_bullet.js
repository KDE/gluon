
function start()
{
    print("Starting bullet");
}

function update(time)
{
    GameObject.translate(0, -20*(time/1000), 0);
}
