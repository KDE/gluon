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
  
  var rotate = 0;
  if(playerManager.rotate)//Character.spinNeeded > 0 || Character.spinNeeded < 0)
  {
   /* if(Character.spinNeeded > 0)
     rotate =  Math.min(15,Character.spinNeeded);
    else if(Character.spinNeeded < 0)
     rotate = Math.max(-15, Character.spinNeeded);
    
    Component.debug(Character.spinNeeded);
    Component.debug(rotate);
    var up = playerManager.currentParticle.ParticleMotion.upVector;
    if(rotate != 0)
      playerManager.currentParticle.rotate(rotate, up);
   
  /*  var particleToHit = Character.nearestParticle;
 
  //playerManager.particleAtoms[particleToHit.PositionInfo].precision = Character.nearestParticlePrecision;
    particleToHitPos = Character.nearestParticle.position;//playerManager.particleAtoms[particleToAvoid.PositionInfo].knowledge;
  
  //playerManager.particleAtoms[particleToHit.VelocityInfo].precision = Character.nearestParticlePrecision;
    particleToHitVelocity = Character.nearestParticle.ParticleMotion.velocityVector;//playerManager.particleAtoms[particleToAvoid.VelocityInfo].knowledge;
  
    var particleToHitVector = new QVector3D(particleToHitPos.x() - playerManager.currentParticle.position.x(),
					    particleToHitPos.y() - playerManager.currentParticle.position.y(),
					    particleToHitPos.z() - playerManager.currentParticle.position.z());  

    var perpDot = playerManager.currentParticle.ParticleMotion.velocityVector.x()*particleToHitVector.y()
		-playerManager.currentParticle.ParticleMotion.velocityVector.y()*particleToHitVector.x();
		
    var angle = Math.atan2(QVector3D.crossProduct(playerManager.currentParticle.ParticleMotion.velocityVector, particleToHitVector).length(), QVector3D.dotProduct(playerManager.currentParticle.ParticleMotion.velocityVector, particleToHitVector));
    angle = angle * (180/Math.PI);*/
    
    Node.status = 2;
    //Character.spinNeeded = angle;
  }
  else
  {
    Node.status = 1;
  }
}