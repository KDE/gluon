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
    
  if(Character.time > Node.interval*1000)
  {
    Character.useTimeEnergy = true;
    Character.timeEnergy = Character.time;
    Character.time = 0;
    Node.runChild(0);
    Node.status = 3;
  }
  else
  {
    Character.useTimeEnergy = false;
    Character.time += Component.time;
    Node.status = 2;
  }
}