var playerManager = 0;

function run()
{
  if(!playerManager)
    playerManager = Scene.MasterControl.PlayerManager;
  
   //hack hack
    if(playerManager.stop)
    {
      Character.points = playerManager.addPoints;
      Component.autoThink = false;
      Node.status = 2;
      return;
    }
playerManager.rotate = false;
  Character.speedNeeded = Scene.MasterControl.PlayerManager.currentParticle.ParticleMotion.currentSpeed;
  
  Node.status = 1;
}