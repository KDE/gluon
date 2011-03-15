this.initialize = function()
{
}

this.start = function()
{
    this.AnimatedSprite = this.GameObject.AnimatedSpriteRendererComponent;
    this.Background = this.GameObject.parentGameObject().Background.SpriteRendererComponent.material;
    this.Component.speed = this.Component.speed || 0.025;
    
    this.scaleX = this.Background.textureParameters.z();
    this.scaleY = this.Background.textureParameters.w();
    this.moveX = 0.0;
    this.moveY = 0.0;
}

this.update = function(time)
{    
    var translateX = 0;
    var translateY = 0;
    
    if(this.GameObject.Key_Left.isActionHeld())
        translateX = -this.Component.speed;
    
    if(this.GameObject.Key_Right.isActionHeld())
        translateX = this.Component.speed;
    
    if(this.GameObject.Key_Up.isActionHeld())
        translateY = this.Component.speed;
    
    if(this.GameObject.Key_Down.isActionHeld())
        translateY = -this.Component.speed;
    
    this.moveX += translateX;
    this.moveY += translateY;
    this.Background.textureParameters = new QVector4D(this.moveX, this.moveY, this.scaleX, this.scaleY);
    
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
        if(this.GameObject.Key_Swing.isActionHeld())
        {
            if(this.AnimatedSprite.animation != 3)
                this.AnimatedSprite.animation = 3;
        }
        else
        {
            if(this.AnimatedSprite.animation != 0)
                this.AnimatedSprite.animation = 0;
        }
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
