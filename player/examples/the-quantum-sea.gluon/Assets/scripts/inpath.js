var playerManager = 0;
var particleToHitVelocity;

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
  
  var particleToHit = Character.nearestParticle;
 
  //playerManager.particleAtoms[particleToHit.PositionInfo].precision = Character.nearestParticlePrecision;
  particleToHitPos = Character.nearestParticle.position;//playerManager.particleAtoms[particleToAvoid.PositionInfo].knowledge;
  
  //playerManager.particleAtoms[particleToHit.VelocityInfo].precision = Character.nearestParticlePrecision;
  particleToHitVelocity = Character.nearestParticle.ParticleMotion.velocityVector;//playerManager.particleAtoms[particleToAvoid.VelocityInfo].knowledge;
  
  var particleToHitVector = new QVector3D(particleToHitPos.x() - playerManager.currentParticle.position.x(),
					    particleToHitPos.y() - playerManager.currentParticle.position.y(),
					    particleToHitPos.z() - playerManager.currentParticle.position.z());

  var particleToHitVectorHead = new QVector3D(particleToHitPos.x() + particleToHitVelocity.x()
				, particleToHitPos.y() + particleToHitVelocity.y()
				, particleToHitPos.z() + particleToHitVelocity.z());
  
  var currentParticlVectorHeadPos = new QVector3D(playerManager.currentParticle.position.x() + playerManager.currentParticle.ParticleMotion.velocityVector.x()
				  , playerManager.currentParticle.position.y() + playerManager.currentParticle.ParticleMotion.velocityVector.y()
				  , playerManager.currentParticle.position.z() + playerManager.currentParticle.ParticleMotion.velocityVector.z());
				  
  if(calculateLineInterSect(playerManager.currentParticle.position, currentParticlVectorHeadPos, particleToHitPos, particleToHitVectorHead))
  {
    Node.status = 2;
  }
  else
  {
    Node.status = 0;
  }
}

function calculateLineInterSect(firstLineTail, firstLineHead, secondLineTail, secondLineHead)
{
  if(!firstLineTail)
    return false;
  
  if(!firstLineHead)
    return false;
  
  if(!secondLineHead)
    return false;
  
  if(!secondLineTail)
    return false;
  
  var denom = (secondLineHead.y()-secondLineTail.y())*(firstLineHead.x()-firstLineTail.x()) - (secondLineHead.x()-secondLineTail.x())*(firstLineHead.y()-firstLineTail.y());
  var firstLine = (secondLineHead.x()-secondLineTail.x())*(firstLineTail.y()-secondLineTail.y()) - (secondLineHead.y()-secondLineTail.y())*(firstLineTail.x()-secondLineTail.x());
  var secondLine = (firstLineHead.x()-firstLineTail.x())*(firstLineTail.y()-secondLineTail.y()) - (firstLineHead.y()-firstLineTail.y())*(firstLineTail.x()-secondLineTail.x());
  
  if(denom == 0)
    return true;
  
  var fu = firstLine / denom;
  var su = secondLine / denom;
  
  var x = firstLineTail.x() + fu * (firstLineHead.x() - firstLineTail.x());
  var y = firstLineTail.y() + fu * (firstLineHead.y() - firstLineTail.y());
  var z = firstLineTail.z();
  
  var dirVector = new QVector3D(x - firstLineTail.x(), y - firstLineTail.y(),  z -firstLineTail.z());
  var dot = dotProduct(dirVector, playerManager.currentParticle.ParticleMotion.velocityVector);
  
  if(dot == -1)
    return false;
  
  dirVector = new QVector3D(x - secondLineTail.x(), y - secondLineTail.y(),  z -secondLineTail.z());
  dot = dotProduct(dirVector, particleToHitVelocity);
  
  if(dot == -1)
    return false;
  
  return true;
}

function dotProduct(vector1, vecto2)
{
  return vector1.x() * vecto2.x()
	    + vector1.y() * vecto2.y() 
	    + vector1.z() * vecto2.z();
}