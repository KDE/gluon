var playerManager = 0;
var exec = 50;
var currentExec = 0;

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
    
  if(!Node.elapsTime || Node.elapsTime == 0)
    Node.elapsTime = Component.elapsedTime;
  
  if( currentExec > exec)
  {
    currentExec = 0;
    Node.status = 0;
  }
  else
  {
    currentExec++;
    Node.status = 2;
  }
}