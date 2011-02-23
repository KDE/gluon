this.initialize = function()
{
    this.Component.mouseSpeed = this.Component.mouseSpeed || 10;
    this.AnimatedSprite = this.GameObject.AnimatedSpriteRendererComponent;
}

this.update = function(time)
{
    if(this.GameObject.Key_Left.isActionStarted())
    {
        this.AnimatedSprite.direction += 1;
        if(this.AnimatedSprite.direction > 7)
            this.AnimatedSprite.direction = 0;
    }
    
    if(this.GameObject.Key_Right.isActionStarted())
    {
        this.AnimatedSprite.direction -= 1;
        if(this.AnimatedSprite.direction < 0)
            this.AnimatedSprite.direction = 7;
    }
    
    if(this.GameObject.Key_Up.isActionStarted())
    {
        this.AnimatedSprite.animation += 1;
    }
    
    if(this.GameObject.Key_Down.isActionStarted())
    {
        this.AnimatedSprite.animation -= 1;
    }
}