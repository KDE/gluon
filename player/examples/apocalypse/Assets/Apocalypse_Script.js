this.frameCounter = 0;
this.currentFrame = 0;

this.frames =     [ 4, 8, 8,   6,  4,  2,  6 ];
this.frameStart = [ 0, 4, 12, 20, 26, 30, 32 ];
this.currentAnimation = 0;

this.initialize = function()
{
    this.Component.mouseSpeed = this.Component.mouseSpeed || 10;
    this.Component.frameSize = this.Component.frameSize || new QVector2D(0, 0);
    this.Component.direction = this.Component.direction || 0;
    this.Component.frameRate = this.Component.frameRate || 24;
    this.Component.textureSize = this.Component.textureSize || new QVector2D(1024, 1024);
}

this.update = function(time)
{
//     var x = this.GameObject.Mouse_Left.xAxis() / this.Component.mouseSpeed;
//     var y = this.GameObject.Mouse_Left.yAxis() / this.Component.mouseSpeed;
//
//     this.GameObject.setPosition(x, y, 0);
//
    //this.GameObject.SpriteRenderer.material.frame =
    this.currentFrame += 25 / this.Component.frameRate;
    if(this.currentFrame >= this.frames[this.currentAnimation])
        this.currentFrame = 0;
    
    if(this.GameObject.Key_Left.isActionStarted())
    {
        this.Component.direction += 1.0;
        if(this.Component.direction > 7)
            this.Component.direction = 0;
    }
    
    if(this.GameObject.Key_Right.isActionStarted())
    {
        this.Component.direction -= 1.0;
        if(this.Component.direction < 0)
            this.Component.direction = 7;
    }
    
    if(this.GameObject.Key_Up.isActionStarted())
    {
        this.currentAnimation += 1;
        if(this.currentAnimation >= this.frames.length)
            this.currentAnimation = 0;
    }
    
    if(this.GameObject.Key_Down.isActionStarted())
    {
        this.currentAnimation -= 1;
        if(this.currentAnimation < 0)
            this.currentAnimation = this.frames.length - 1;
    }
}

this.draw = function(timeLapse)
{
    var frame = new QVector4D();
    frame.setX((this.Component.frameSize.x() / this.Component.textureSize.x()) * (Math.floor(this.currentFrame) + this.frameStart[this.currentAnimation]));
    frame.setY((this.Component.frameSize.y() / this.Component.textureSize.y()) * this.Component.direction);
    frame.setZ(this.Component.frameSize.x() / this.Component.textureSize.x());
    frame.setW(this.Component.frameSize.y() / this.Component.textureSize.y());

    this.GameObject.SpriteRendererComponent.material.frame = frame;
}