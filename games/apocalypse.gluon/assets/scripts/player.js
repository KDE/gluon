var animatedSprite,
background,
bullet,
crosshair,
renderTarget,

scaleX,
scaleY,
moveX,
moveY,
lightIntensity;

function initialize()
{
    self.Component.backgroundDivisor = self.Component.backgroundDivisor || 50;
    self.Component.speed = self.Component.speed || 20;
    self.Component.health = self.Component.health || 100;
    
    MessageHandler.subscribe("fireBullet", fireBullet, self);
    MessageHandler.subscribe("playerHurt", damagePlayer, self);
}

function start()
{
    animatedSprite = self.GameObject.AnimatedSpriteRendererComponent;
    background = self.GameObject.parentGameObject().Background.SpriteRendererComponent.material;
    bullet = self.Scene.sceneContents().Bullet;
    crosshair = self.Scene.sceneContents().Camera.Crosshair;
    renderTarget = self.Scene.sceneContents().Camera.CameraControllerComponent.renderTargetMaterial;

    scaleX = background.textureParameters.z();
    scaleY = background.textureParameters.w();
    moveX = 0.0;
    moveY = 0.0;
    lightIntensity = background.lightIntensity;

    self.Scene.currentHealth = self.Component.health;
    renderTarget.saturation = 1.0;
    background.lightIntensity = 1500;
}

function update(time)
{
    if(self.Scene.paused)
        return;
    
    var dt = time / 1000;
    
    var translateX = 0;
    var translateY = 0;
    
    if(self.GameObject.Key_Left.isActionHeld())
        translateX = -self.Component.speed * dt;
    
    if(self.GameObject.Key_Right.isActionHeld())
        translateX = self.Component.speed * dt;
    
    if(self.GameObject.Key_Up.isActionHeld())
        translateY = self.Component.speed * dt;
    
    if(self.GameObject.Key_Down.isActionHeld())
        translateY = -self.Component.speed * dt;
    
    //self.GameObject.debug(translateX);
    //self.GameObject.debug(translateY);
    
    moveX += translateX / self.Component.backgroundDivisor;
    moveY += translateY / self.Component.backgroundDivisor;
    background.textureParameters = new Vector4f(moveX, moveY, scaleX, scaleY);
   
    self.GameObject.parentGameObject().translate(translateX / scaleX, translateY / scaleY, 0);
    
    setDirection();
    
    if(translateX == 0 && translateY == 0)
    {
	if(animatedSprite.animation != 0)
	    animatedSprite.animation = 0;
    }
    else
    {
        if(animatedSprite.animation != 1)
            animatedSprite.animation = 1;
    }
}

function cleanup()
{
    MessageHandler.unsubscribe("fireBullet", fireBullet, self);
    MessageHandler.unsubscribe("playerHurt", damagePlayer, self);
}

function fireBullet() 
{
    var newBullet = Game.clone(bullet);
    newBullet.enabled = true;

    var newPosition = self.GameObject.worldPosition();
    newPosition.setZ(bullet.position.z());
    newBullet.setPosition(newPosition);

    var dir = new Vector3f();
    dir.setX(crosshair.worldPosition().x() - newPosition.x());
    dir.setY(crosshair.worldPosition().y() - newPosition.y());
    dir.normalize();
    newBullet.ScriptingComponent.direction = dir;
}

function setDirection()
{
    var dir = crosshair.worldPosition().subtract(self.GameObject.worldPosition());
    dir.normalize();

    var angle = Vector3f.dotProduct(dir, new Vector3f(0, 1, 0));
    if(dir.x() < 0)
    {
        if(angle > 0.75)
            animatedSprite.direction = 7;
        else if(angle > 0.25)
            animatedSprite.direction = 0;
        else if(angle > -0.25)
            animatedSprite.direction = 1;
        else if(angle > -0.75)
            animatedSprite.direction = 2;
        else
            animatedSprite.direction = 3;
    }
    else
    {
        if(angle > 0.75)
            animatedSprite.direction = 7;
        else if(angle > 0.25)
            animatedSprite.direction = 6;
        else if(angle > -0.25)
            animatedSprite.direction = 5;
        else if(angle > -0.75)
            animatedSprite.direction = 4;
        else
            animatedSprite.direction = 3;
    }
}

function damagePlayer()
{
    self.Scene.currentHealth -= 1;
    background.lightIntensity = (self.Scene.currentHealth / self.Component.health) * (lightIntensity); // / 2) + lightIntensity / 2;
    renderTarget.saturation = self.Scene.currentHealth / self.Component.health;

    if(self.Scene.currentHealth < 0)
    {
        MessageHandler.publish("playerDied");
    }
}

self.initialize = initialize;
self.start = start;
self.update = update;
self.cleanup = cleanup;
