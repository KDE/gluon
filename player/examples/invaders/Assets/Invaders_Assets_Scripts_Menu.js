this.update = function(time) 
{
    if(this.GameObject.Key_Space.isActionStarted()) 
    {
        this.Game.setCurrentScene("Invaders/Scenes/Game");
    }
}
