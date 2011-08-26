var playerManager = 0;
var energyAdded = 0;

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
  
  var speedEnergy = 0;
 
  speedEnergy = drawEnergy(40);//Character.useTimeEnergy ?  drawEnergy(Character.timeEnergy): drawEnergy(Component.time);

  playerManager.currentParticle.ParticleMotion.speedEnergy += 2;//speedEnergy;
  energyAdded += speedEnergy;
  
  if(energyAdded >= 5)
  {
    Node.status = 1;
  }
  else
  {
    Node.status = 2;
  }
}

function drawEnergy(time)
{
    var availableEnergy = playerManager.availableEnergy;
    var drainPerSecond = playerManager.energyDrainPerSecond;
    var drainNow = drainPerSecond * time/1000;
    
    drainNow = Math.min(drainNow, availableEnergy);
    playerManager.availableEnergy -= drainNow;
    return drainNow;
}