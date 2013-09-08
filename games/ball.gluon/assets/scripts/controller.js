var miniumBreak,
currentlyBreak,
lastScoreUpdate,
endedGame,
trapReference,
starReference,
playerReference;

function initialize()
{
    self.Component.paused = false;
}

function start()
{
    Game.score = 0;
    Game.end = false;

    miniumBreak = 50;
    currentlyBreak = 0;
    lastScoreUpdate = 0;
    endedGame = false;

    trapReference = self.Scene.sceneContents().Trap;
    starReference = self.Scene.sceneContents().Star;
    playerReference = self.Scene.sceneContents().Player;
    playerReference.setPosition(-25, -40);
    playerReference.enabled = true;
}

function update(time)
{
    if( !Game.end )
    {
        deployTrap();
        if( Game.score % 6 == 0 && Game.score != self.lastScoreUpdate )
            updateScore(Game.score/6);
    }
    else
    {
        if( !endedGame )
            end();
    }

    if (self.GameObject.Key_Reset.isActionStarted())
        resetGame();
}

function deployTrap()
{
    currentlyBreak++;
    if(currentlyBreak >= miniumBreak)
    {
        if( Game.random() > 0.8)
        {
            var trap = Game.clone(trapReference);
            trap.setPosition(50, -40);
            trap.enabled = true;
            currentlyBreak = 0;
        }
    }
}

function updateScore(score)
{
    lastScoreUpdate = score * 6;
    
    var star = Game.clone(starReference);
    star.setPosition(((score % 6) * 8) - 20, Math.floor(score / 6) * 8);
    star.enabled = true;
}

function end()
{
    endedGame = true;
    
    var score = Game.clone(self.Scene.sceneContents().ScoreText);
    score.setPosition(-30, 0);
    score.enabled = true;
    
    var resetText = Game.clone(self.Scene.sceneContents().ResetText);
    resetText.setPosition(-5, -10);
    resetText.enabled = true;
}

function resetGame()
{
    Game.resetCurrentScene();
}

self.initialize = initialize;
self.start = start;
self.update = update;
