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
  
  if(!playerManager.currentParticle)
  {  
    var allParticles = playerManager.allParticles;
    for(item in allParticles)
    {
       if(allParticles[item].enabled && allParticles[item].ParticleInfo.collidableParticle)
      {
	playerManager.currentParticle = allParticles[item];//Scene.findComponentInChildren("Nitrogen-14");//Game.getFromScene("Nitrogen-14");
	Node.status = 2;
	return;
      }      
    }
  }
  
  if(!Character.nearestParticle)
  {  
    var allParticles = playerManager.allParticles;
    for(item in allParticles)
    {
      if(allParticles[item] == playerManager.currentParticle)
      {
	continue;
      }
      else if(allParticles[item].enabled && allParticles[item].ParticleInfo.collidableParticle)
      {
	Character.nearestParticle = allParticles[item];//Scene.findComponentInChildren("Nitrogen-14");//Game.getFromScene("Nitrogen-14");
	break;
      }      
    }
  }
  
  /*var particleAtoms = Scene.MasterControl.PlayerManager.particleAtoms;
  
  Component.debug("dan " +  Scene.MasterControl.PlayerManager.particleAtoms);
  
  particleAtoms[Character.nearestParticle.VelocityInfo].precision = Character.nearestParticlePrecision;
  Character.nearestParticleVelocity = particleAtoms [Character.nearestParticle.VelocityInfo].knowledge;*/
 // playerManager.particleAtoms = particleAtoms;
 
  Character.nearestParticleVelocity = Character.nearestParticle.ParticleMotion.VelocityVector;
  Node.status = 1;
}