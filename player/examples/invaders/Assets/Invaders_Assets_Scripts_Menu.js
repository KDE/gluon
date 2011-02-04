this.update = function(time) 
{
    if(this.GameObject.Key_Space.isActionStarted()) 
    {
        Game.setCurrentScene("Invaders/Scenes/Game");
    }
}
