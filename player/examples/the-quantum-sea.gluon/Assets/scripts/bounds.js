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
  
  if(Scene.MasterControl.PlayerManager.currentParticle.position.x() > 2560/2
    || Scene.MasterControl.PlayerManager.currentParticle.position.y() >1600/2
    || Scene.MasterControl.PlayerManager.currentParticle.position.x() < -(2560/2)
    || Scene.MasterControl.PlayerManager.currentParticle.position.y() < -(1600/2))
  {
    Node.status = 0;
  }
  else
  {
    Node.status = 2;
  }
}