this.initialize = function()
{
    this.Component.paused = false;
}

this.start = function()
{
    Game.score = 0;
    Game.end = false;
    
    this.miniumBreak = 50;
    this.currentlyBreak = 0;
    this.lastScoreUpdate = 0;
    this.endedGame = false;

    this.trapReference = this.Scene.sceneContents().Trap;
    this.starReference = this.Scene.sceneContents().Star;
    this.playerReference = this.Scene.sceneContents().Player;
    this.playerReference.setPosition(-25, -40);
    this.playerReference.enabled = true;
}

this.update = function(time)
{
    if( !Game.end )
    {
        this.deployTrap();
        if( Game.score % 6 == 0 && Game.score != this.lastScoreUpdate )
            this.updateScore(Game.score/6);
    }
    else
    {
        if( !this.endedGame )
            this.end();
    }

    if (this.GameObject.Key_Reset.isActionStarted())
        this.resetGame();
}

this.deployTrap = function()
{
    this.currentlyBreak++;
    if(this.currentlyBreak >= this.miniumBreak)
    {
        if( Game.random() > 0.8)
        {
            var trap = Game.clone(this.trapReference);
            trap.setPosition(50, -40);
            trap.enabled = true;
            this.currentlyBreak = 0;
        }
    }
}

this.updateScore = function(score)
{
    this.lastScoreUpdate = score * 6;
    
    var star = Game.clone(this.starReference);
    star.setPosition(((score % 6) * 8) - 20, Math.floor(score / 6) * 8);
    star.enabled = true;
}

this.end = function()
{
    this.endedGame = true;
    
    var score = Game.clone(this.Scene.sceneContents().ScoreText);
    score.setPosition(-30, 0);
    score.enabled = true;
    
    var resetText = Game.clone(this.Scene.sceneContents().ResetText);
    resetText.setPosition(-5, -10);
    resetText.enabled = true;
}

this.resetGame = function()
{
    Game.resetCurrentScene();
}
