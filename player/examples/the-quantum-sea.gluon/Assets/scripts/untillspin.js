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
  
  var success = false;
  //right
  if(Character.spinDirection == 0)
  {
    if(playerManager.currentParticle.ParticleMotion.currentSpin < Character.spinNeeded)
    {
      success = true;
    }
  }
  else if (Character.spinDirection == 1) // left
  {
    if(playerManager.currentParticle.ParticleMotion.currentSpin > Character.spinNeeded)
    {
      success = true;
    }
  }
  
  if(success)
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