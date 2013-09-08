var AnimatedSprite,
player,
bulletCollider,
playerCollider,
dead,
attack;

function initialize ()
{
    Component().speed = Component().speed || 25;
}

function start()
{
    AnimatedSprite = GameObject().AnimatedSpriteRendererComponent;
    player = Scene().sceneContents().Camera.Player;
    bulletCollider = GameObject().BulletCollider;
    playerCollider = GameObject().PlayerCollider;
    dead = false;
    attack = false;
}

function update(time)
{
    if(!dead && !Scene().paused)
    {
        var playerPos = player.worldPosition();
        var thisPos = GameObject().position;

        var diff = new QVector3D(playerPos.x() - thisPos.x(), playerPos.y() - thisPos.y(), 0);
        diff.normalize();

        var dist = Component().speed * (time / 1000);
        diff.setX(diff.x() * dist);
        diff.setY(diff.y() * dist);

        GameObject().translate(diff);
        setDirection(diff);

        if(bulletCollider.isColliding())
        {
            bulletCollider.collidesWith().destroy();
            kill();
        }

        if(playerCollider.isColliding())
        {
            MessageHandler.publish("playerHurt");
            GameObject().translate(diff.multiply(-10));
        }
//         {
//             attack = true;
//             AnimatedSprite.animation = 3;
//         }
//         else
//         {
//             attack = false;
//             AnimatedSprite.animation = 1;
//         }
    }
}

function kill()
{
    GameObject().AnimatedSpriteRendererComponent.animation = 6;
    GameObject().AnimatedSpriteRendererComponent.loop = false;
    dead = true;
    Scene.score++;
}

function setDirection(direction)
{
    var angle = QVector3D.dotProduct(direction, new QVector3D(0, 1, 0));
    var dir = -1;
    if(direction.x() < 0)
    {
        if(angle > 0.75)
            dir = 7;
        else if(angle > 0.25)
            dir = 0;
        else if(angle > -0.25)
            dir = 1;
        else if(angle > -0.75)
            dir = 2;
        else
            dir = 3;
    }
    else
    {
        if(angle > 0.75)
            dir = 7;
        else if(angle > 0.25)
            dir = 6;
        else if(angle > -0.25)
            dir = 5;
        else if(angle > -0.75)
            dir = 4;
        else
            dir = 3;
    }
    AnimatedSprite.direction = dir;
}

self.initialize = initialize;
self.start = start;
self.update = update;
