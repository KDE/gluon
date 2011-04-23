var gMiniumBreakInt = 50;
var gCurrentlyBreakInt = 0;
var gPlayerRef = null;
var gPlayer2Ref = null;
var gLastScoreUpdateInt = 0;
var gEndedGameBool = false;
var gStarRef = null;

this.initialize = function()
{
    this.Component.paused = false;
}

this.start = function()
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

this.update = function(time)
{
    if (Game.end == false) {
        if (Game.score%6 == 0 && Game.score != gLastScoreUpdateInt) {
            this.updateScore(Game.score/6);
        }
    } else {
        if (gEndedGameBool == false) {
            this.end();
        }

        if (this.GameObject.Key_Reset.isActionHeld()) {
            this.resetGame();
        }
    }
}

this.updateScore = function(score) {
    gLastScoreUpdateInt = score * 6;
    var star = Game.clone(gStarRef);
    star.setPosition(((score%6)*8)-20, Math.floor(score/6)*8);
    star.enabled = true;

}

this.end = function()
{
    gEndedGameBool = true;
    var score = Game.clone(Game.getFromScene("ScoreText"));
    score.setPosition(-30, 0);
    score.enabled = true;
    var resetText = Game.clone(Game.getFromScene("ResetText"));
    resetText.setPosition(-5, -10);
    resetText.enabled = true;
}

this.resetGame = function()
{
    Game.resetCurrentScene();
}
