this.initialize = function()
{
    this.Component.mouseSpeed = this.Component.mouseSpeed || 0.05;
    this.Mouse = this.GameObject.Button_Fire;
    this.zDepth = this.GameObject.position.z();
    this.radius = 45;
}

this.update = function(time)
{
    var x = this.GameObject.Button_Fire.normalizedXAxis() * this.radius;
    var y = -this.GameObject.Button_Fire.normalizedYAxis() * this.radius;

    //this.GameObject.debug(x);
    //this.GameObject.debug(y);
    this.GameObject.setPosition(x, y, this.zDepth);
}
