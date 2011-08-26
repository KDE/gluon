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
    
  playerManager.currentParticle.ParticleMotion.speedEnergy += drawEnergy(Component.time);
  Node.status = 1;
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