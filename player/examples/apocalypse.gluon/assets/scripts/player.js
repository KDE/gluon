this.initialize = function()
{
    this.Component.backgroundDivisor = this.Component.backgroundDivisor || 50;
    this.Component.speed = this.Component.speed || 20;
    this.Component.health = this.Component.health || 100;
    
    MessageHandler.subscribe("fireBullet", this.fireBullet, this);
    MessageHandler.subscribe("playerHurt", this.damagePlayer, this);
}

this.start = function()
{
    this.animatedSprite = this.GameObject.AnimatedSpriteRendererComponent;
    this.background = this.GameObject.parentGameObject().Background.SpriteRendererComponent.material;
    this.bullet = this.Scene.sceneContents().Bullet;
    this.crosshair = this.Scene.sceneContents().Camera.Crosshair;
    this.renderTarget = this.Scene.sceneContents().Camera.CameraControllerComponent.renderTargetMaterial;
    
    this.scaleX = this.background.textureParameters.z();
    this.scaleY = this.background.textureParameters.w();
    this.moveX = 0.0;
    this.moveY = 0.0;
    this.lightIntensity = this.background.lightIntensity;

    this.Scene.currentHealth = this.Component.health;
    this.renderTarget.saturation = 1.0;
    this.background.lightIntensity = 1500;
}

this.update = function(time)
{
    if(this.Scene.paused)
        return;
    
    var dt = time / 1000;
    
    var translateX = 0;
    var translateY = 0;
    
    if(this.GameObject.Key_Left.isActionHeld())
        translateX = -this.Component.speed * dt;
    
    if(this.GameObject.Key_Right.isActionHeld())
        translateX = this.Component.speed * dt;
    
    if(this.GameObject.Key_Up.isActionHeld())
        translateY = this.Component.speed * dt;
    
    if(this.GameObject.Key_Down.isActionHeld())
        translateY = -this.Component.speed * dt;
    
    //this.GameObject.debug(translateX);
    //this.GameObject.debug(translateY);
    
    this.moveX += translateX / this.Component.backgroundDivisor;
    this.moveY += translateY / this.Component.backgroundDivisor;
    this.background.textureParameters = new QVector4D(this.moveX, this.moveY, this.scaleX, this.scaleY);
   
    this.GameObject.parentGameObject().translate(translateX / this.scaleX, translateY / this.scaleY, 0);
    
    this.setDirection();
    
    if(translateX == 0 && translateY == 0)
    {
	if(this.animatedSprite.animation != 0)
	    this.animatedSprite.animation = 0;
    }
    else
    {
        if(this.animatedSprite.animation != 1)
            this.animatedSprite.animation = 1;
    }
}

this.cleanup = function()
{
    MessageHandler.unsubscribe("fireBullet", this.fireBullet, this);
    MessageHandler.unsubscribe("playerHurt", this.damagePlayer, this);
}

this.fireBullet = function() 
{
    var newBullet = Game.clone(this.bullet);
    newBullet.enabled = true;

    var newPosition = this.GameObject.worldPosition();
    newPosition.setZ(this.bullet.position.z());
    newBullet.setPosition(newPosition);

    var dir = new QVector3D();
    dir.setX(this.crosshair.worldPosition().x() - newPosition.x());
    dir.setY(this.crosshair.worldPosition().y() - newPosition.y());
    dir.normalize();
    newBullet.ScriptingComponent.direction = dir;
}

this.setDirection = function()
{
    var dir = this.crosshair.worldPosition().subtract(this.GameObject.worldPosition());
    dir.normalize();

    var angle = QVector3D.dotProduct(dir, new QVector3D(0, 1, 0));
    if(dir.x() < 0)
    {
        if(angle > 0.75)
            this.animatedSprite.direction = 7;
        else if(angle > 0.25)
            this.animatedSprite.direction = 0;
        else if(angle > -0.25)
            this.animatedSprite.direction = 1;
        else if(angle > -0.75)
            this.animatedSprite.direction = 2;
        else
            this.animatedSprite.direction = 3;
    }
    else
    {
        if(angle > 0.75)
            this.animatedSprite.direction = 7;
        else if(angle > 0.25)
            this.animatedSprite.direction = 6;
        else if(angle > -0.25)
            this.animatedSprite.direction = 5;
        else if(angle > -0.75)
            this.animatedSprite.direction = 4;
        else
            this.animatedSprite.direction = 3;
    }
}

this.damagePlayer = function()
{
    this.Scene.currentHealth -= 1;
    this.background.lightIntensity = (this.Scene.currentHealth / this.Component.health) * (this.lightIntensity); // / 2) + this.lightIntensity / 2;
    this.renderTarget.saturation = this.Scene.currentHealth / this.Component.health;

    if(this.Scene.currentHealth < 0)
    {
        MessageHandler.publish("playerDied");
    }
}

this.serialize = function()
{
    var persistenceObject = new Object();
    persistenceObject.health = this.Scene.currentHealth;
    return persistenceObject;
}

this.restore = function( persistenceObject )
{
    this.Scene.currentHealth = persistenceObject.health;
}