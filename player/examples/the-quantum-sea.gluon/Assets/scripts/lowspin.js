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
  if(Character.spinDirection == 0)
    Character.spinNeeded = -Node.spin;
  else
    Character.spinNeeded = Node.spin;
  
  Node.status = 1;
}