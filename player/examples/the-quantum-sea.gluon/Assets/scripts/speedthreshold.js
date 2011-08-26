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
    
  if(playerManager.currentParticle.ParticleMotion.velocityVector.length() >= Node.speedThreshold)
  {
    Node.runChild(0);
    Node.status = 3;
    return;
  }

  Node.status = false;
}