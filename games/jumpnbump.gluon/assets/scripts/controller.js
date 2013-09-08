var gMiniumBreakInt = 50,
gCurrentlyBreakInt = 0,
gPlayerRef = null,
gPlayer2Ref = null,
gLastScoreUpdateInt = 0,
gEndedGameBool = false,
gStarRef = null;

function initialize()
{
    self.Component.paused = false;
}

function start()
{
    Game.score = 0;
    Game.end = false;

    gStarRef = Game.getFromScene("Star");
    gPlayerRef = Game.clone(Game.getFromScene("Player"));
    gPlayerRef.setPosition(-25, -40);
    gPlayerRef.enabled = true;
    gPlayer2Ref = Game.clone(Game.getFromScene("Player2"));
    gPlayer2Ref.setPosition(25, -40);
    gPlayer2Ref.enabled = true;
}

function update(time)
{
    if (Game.end == false) {
        if (Game.score%6 == 0 && Game.score != gLastScoreUpdateInt) {
            updateScore(Game.score/6);
        }
    } else {
        if (gEndedGameBool == false) {
            end();
        }

        if (self.GameObject.Key_Reset.isActionHeld()) {
            resetGame();
        }
    }
}

function updateScore(score) {
    gLastScoreUpdateInt = score * 6;
    var star = Game.clone(gStarRef);
    star.setPosition(((score%6)*8)-20, Math.floor(score/6)*8);
    star.enabled = true;

}

function end()
{
    gEndedGameBool = true;
    var score = Game.clone(Game.getFromScene("ScoreText"));
    score.setPosition(-30, 0);
    score.enabled = true;
    var resetText = Game.clone(Game.getFromScene("ResetText"));
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
