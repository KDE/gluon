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
  
  if(playerManager.currentParticle.ParticleMotion.currentSpeed >= Character.speedNeeded)
  {
    Node.status = 1;
  }
  else if(playerManager.availableEnergy < 1)
  {
    Node.status = 0;
  }
  else
  {
    Node.status = 3;
  }
}
