var gMiniumBreakInt = 50,
gCurrentlyBreakInt = 0,
gPlayer1Ref = null,
gPlayer2Ref = null,
gBallRef = null,
gLastScoreUpdateInt = 0,
gEndedGameBool = false;

function initialize()
{
    self.Component.paused = false;
}

function start()
{
    Game.score = 0;
    Game.end = false;

    var cameraWidth = self.Scene.sceneContents().Camera.CameraControllerComponent.visibleArea.width();
    
    gPlayer1Ref = Game.clone(Game.getFromScene("Player1"));
    gPlayer1Ref.setPosition(-cameraWidth + self.Scene.sceneContents().Player1.Player1SpriteRenderer.size.width(), 0);
    gPlayer1Ref.enabled = true;

    gPlayer2Ref = Game.clone(Game.getFromScene("Player2"));
    gPlayer2Ref.setPosition(cameraWidth - self.Scene.sceneContents().Player2.Player2SpriteRenderer.size.width(), 0);
    gPlayer2Ref.enabled = true;

    gBallRef = Game.clone(Game.getFromScene("Ball"));
    gBallRef.setPosition(0, 0);
    gBallRef.enabled = true;
}

function update(time)
{
    // if (Game.end == false) {
        // if (Game.score%6 == 0 && Game.score != gLastScoreUpdateInt) {
            // self.updateScore(Game.score/6);
        // }
    // } else {
        // if (gEndedGameBool == false) {
            // self.end();
        // }

        // if (self.GameObject.Key_Reset.isActionHeld()) {
            // self.resetGame();
        // }
    // }
}

function updateScore(score) {
    gLastScoreUpdateInt = score * 6;
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
    MessageHandler.publish("GameEnded");
}

function resetGame()
{
    // Game.resetCurrentScene();
}

self.initialize = initialize;
self.start = start;
self.update = update;
