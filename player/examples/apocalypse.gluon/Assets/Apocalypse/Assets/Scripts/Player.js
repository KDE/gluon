this.initialize = function()
{
    this.Component.backgroundDivisor = this.Component.backgroundDivisor || 50;
    this.Component.speed = this.Component.speed || 20;
    
    MessageHandler.subscribe("fireBullet", this.fireBullet, this);
}

this.start = function()
{
    this.AnimatedSprite = this.GameObject.AnimatedSpriteRendererComponent;
    this.Background = this.GameObject.parentGameObject().Background.SpriteRendererComponent.material;
    this.bullet = this.Scene.sceneContents().Bullet;
    
    this.scaleX = this.Background.textureParameters.z();
    this.scaleY = this.Background.textureParameters.w();
    this.moveX = 0.0;
    this.moveY = 0.0;
}

this.update = function(time)
{   
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
    this.Background.textureParameters = new QVector4D(this.moveX, this.moveY, this.scaleX, this.scaleY);
   
    this.GameObject.parentGameObject().translate(translateX / this.scaleX, translateY / this.scaleY, 0);
    
    if(translateX == -this.Component.speed && translateY == this.Component.speed)
        this.AnimatedSprite.direction = 0;
    
    if(translateX == -this.Component.speed && translateY == 0)
        this.AnimatedSprite.direction = 1;
    
    if(translateX == -this.Component.speed && translateY == -this.Component.speed)
        this.AnimatedSprite.direction = 2;
    
    if(translateX == 0 && translateY == -this.Component.speed)
        this.AnimatedSprite.direction = 3;
    
    if(translateX == this.Component.speed && translateY == -this.Component.speed)
        this.AnimatedSprite.direction = 4;
    
    if(translateX == this.Component.speed && translateY == 0)
        this.AnimatedSprite.direction = 5;
    
    if(translateX == this.Component.speed && translateY == this.Component.speed)
        this.AnimatedSprite.direction = 6;
    
    if(translateX == 0 && translateY == this.Component.speed)
        this.AnimatedSprite.direction = 7;
    
    if(translateX == 0 && translateY == 0)
    {
	if(this.AnimatedSprite.animation != 0)
	    this.AnimatedSprite.animation = 0;
    }
    else
    {
        if(this.AnimatedSprite.animation != 1)
            this.AnimatedSprite.animation = 1;
    }
}

this.draw = function(timeLapse)
{
}

this.stop = function()
{
}

this.cleanup = function()
{
}

this.fireBullet = function() 
{
    //this.GameObject.debug("Fire");
    var newBullet = Game.clone(this.bullet);
    newBullet.position.setX(this.GameObject.position.x());
    newBullet.position.setY(this.GameObject.position.y());
    newBullet.enabled = true;
}
