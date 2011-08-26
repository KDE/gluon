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
    
  Component.debug(Character.nearestParticle);
  playerManager.switchParticleTo = Character.nearestParticle;
  
  Node.status = 1;
}
