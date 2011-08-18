var gMiniumBreakInt = 50;
var gCurrentlyBreakInt = 0;
var gPlayer1Ref = null;
var gPlayer2Ref = null;
var gBallRef = null;
var gLastScoreUpdateInt = 0;
var gEndedGameBool = false;

this.initialize = function()
{
    this.Component.paused = false;
}

this.start = function()
{
    Game.score = 0;
    Game.end = false;

    var cameraWidth = this.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.width();
    
    gPlayer1Ref = Game.clone(Game.getFromScene("Player1"));
    gPlayer1Ref.setPosition(-cameraWidth + this.Scene.sceneContents().Player1.Player1SpriteRenderer.size.width(), 0);
    gPlayer1Ref.enabled = true;

    gPlayer2Ref = Game.clone(Game.getFromScene("Player2"));
    gPlayer2Ref.setPosition(cameraWidth - this.Scene.sceneContents().Player2.Player2SpriteRenderer.size.width(), 0);
    gPlayer2Ref.enabled = true;

    gBallRef = Game.clone(Game.getFromScene("Ball"));
    gBallRef.setPosition(0, 0);
    gBallRef.enabled = true;
}

this.update = function(time)
{
    // if (Game.end == false) {
        // if (Game.score%6 == 0 && Game.score != gLastScoreUpdateInt) {
            // this.updateScore(Game.score/6);
        // }
    // } else {
        // if (gEndedGameBool == false) {
            // this.end();
        // }

        // if (this.GameObject.Key_Reset.isActionHeld()) {
            // this.resetGame();
        // }
    // }
}

this.updateScore = function(score) {
    gLastScoreUpdateInt = score * 6;
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
    MessageHandler.publish("GameEnded");
}

this.resetGame = function()
{
    // Game.resetCurrentScene();
}
