var switchContextControl;
var useEnergyControl;
var leftControl;
var rightControl;

var playerManager;

var contextText;

function start()
{
    switchContextControl = GameObject.SwitchContextControl;
    useEnergyControl = GameObject.UseEnergyControl;
    leftControl = GameObject.LeftControl;
    rightControl = GameObject.RightControl;
    playerManager = GameObject.PlayerManager;
    contextText = Game.getFromScene("ContextText");
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

function update(time)
{
  //hack hack
  var time = 40;
    if(playerManager.stop)
      return;
  
    if(switchContextControl.isActionStarted())
    {
        if(playerManager.context == 1)
        {
            playerManager.context = 0;
            contextText.TextRenderer.setText("Control Particle");
        }
        else
        {
            playerManager.context = 1;
            contextText.TextRenderer.setText("Switch Particle");
        }
    }
    
    // If context is 1, we're in the particle selection context
    if(playerManager.context)
    {
    }
    // Otherwise we're controlling a particle
    else
    {
        if(playerManager.currentParticle == 0)
        {
            playerManager.context = 1;
            contextText.TextRenderer.setText("Switch Particle");
            return;
        }
        if(useEnergyControl.isActionHeld())
            playerManager.currentParticle.ParticleMotion.speedEnergy += drawEnergy(time);
        if(leftControl.isActionHeld())
            playerManager.currentParticle.ParticleMotion.leftEnergy += drawEnergy(time);
        if(rightControl.isActionHeld())
            playerManager.currentParticle.ParticleMotion.rightEnergy += drawEnergy(time);
    }
}

function draw()
{
}
