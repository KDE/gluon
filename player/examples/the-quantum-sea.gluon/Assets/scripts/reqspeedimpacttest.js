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
  var particleToHitPos = Character.nearestParticle.position;//playerManager.particleAtoms[particleToAvoid.PositionInfo].knowledge;
  
  //playerManager.particleAtoms[particleToHit.VelocityInfo].precision = Character.nearestParticlePrecision;
  particleToHitVelocity = Character.nearestParticle.ParticleMotion.velocityVector;//playerManager.particleAtoms[particleToAvoid.VelocityInfo].knowledge;
  
  var particleToHitVector = new QVector3D(particleToHitPos.x() - playerManager.currentParticle.position.x(),
					    particleToHitPos.y() - playerManager.currentParticle.position.y(),
					    particleToHitPos.z() - playerManager.currentParticle.position.z());

  var dot = dotProduct(particleToHitVector, particleToHitVelocity);
  var correctSpeed = false;
  
  var currentParticlVectorHeadPos = new QVector3D(playerManager.currentParticle.position.x() + playerManager.currentParticle.ParticleMotion.velocityVector.x()
				  , playerManager.currentParticle.position.y() + playerManager.currentParticle.ParticleMotion.velocityVector.y()
				  , playerManager.currentParticle.position.z() + playerManager.currentParticle.ParticleMotion.velocityVector.z());
  
  if(dot > 0.9 && particleToHit.ParticleMotion.currentSpeed == 0)
  {
    d = calculateD(playerManager.currentParticle.position, currentParticlVectorHeadPos, particleToHitPos, particleToHit.ParticleInfo.radius);
      
    correctSpeed = (d <= 0);
  }
  else
  {
    var particleToHitVectorHead = new QVector3D(particleToHitPos.x() + particleToHitVelocity.x()
				, particleToHitPos.y() + particleToHitVelocity.y()
				, particleToHitPos.z() + particleToHitVelocity.z());
				
    correctSpeed = calculateLineInterSect(playerManager.currentParticle.position, currentParticlVectorHeadPos, particleToHitPos, particleToHitVectorHead)
  }
    
  if(correctSpeed)
  {
    Character.speedNeeded = playerManager.currentParticle.ParticleMotion.currentSpeed+10;
  }  
  else
  {
    Character.speedNeeded = playerManager.currentParticle.ParticleMotion.currentSpeed;
  }
  
  Node.status = 1;
}

function calculateLineInterSect(firstLineTail, firstLineHead, secondLineTail, secondLineHead)
{
  if(!firstLineTail)
    return;
  
  if(!firstLineHead)
    return;
  
  if(!secondLineHead)
    return;
  
  if(!secondLineTail)
    return;
  
  var denom = (secondLineHead.y()-secondLineTail.y())*(firstLineHead.x()-firstLineTail.x()) - (secondLineHead.x()-secondLineTail.x())*(firstLineHead.y()-firstLineTail.y());
  var firstLine = (secondLineHead.x()-secondLineTail.x())*(firstLineTail.y()-secondLineTail.y()) - (secondLineHead.y()-secondLineTail.y())*(firstLineTail.x()-secondLineTail.x());
  var secondLine = (firstLineHead.x()-firstLineTail.x())*(firstLineTail.y()-secondLineTail.y()) - (firstLineHead.y()-firstLineTail.y())*(firstLineTail.x()-secondLineTail.x());
  
  if(denom == 0)
    return false;
  
  var fu = firstLine / denom;
  var su = secondLine / denom;
  
  var x = firstLineTail.x() + fu * (firstLineHead.x() - firstLineTail.x());
  var y = firstLineTail.y() + fu * (firstLineHead.y() - firstLineTail.y());
  var z = firstLineTail.z();
  
  var dirVector = new QVector3D(x - firstLineTail.x(), y - firstLineTail.y(),  z -firstLineTail.z());
  var dot = dotProduct(dirVector, playerManager.currentParticle.ParticleMotion.velocityVector);
  
  if(dot == -1)
    return true;
  
  dirVector = new QVector3D(x - secondLineTail.x(), y - secondLineTail.y(),  z -secondLineTail.z());
  dot = dotProduct(dirVector, particleToHitVelocity);
  
  if(dot == -1)
    return true;
  
  return false;
}

function calculateD(pos1, pos2, center, r)
{
  a = Math.pow((pos2.x() - pos1.x()),2) + Math.pow((pos2.y() - pos1.y()),2) + Math.pow((pos2.z() - pos1.z()),2);
  b = 2*((pos2.x() - pos1.x())*(pos1.x() - center.x()) + (pos2.y() - pos1.y())* (pos1.y() - center.y()) + (pos2.z() - pos1.z())*(pos1.z() - center.z()));
  c = center.x()*center.x() + center.y()*center.y() + center.z()*center.z() + pos1.x()*pos1.x() + pos1.y()*pos1.y() + pos1.z()*pos1.z() - 2*(center.x()*pos1.x() + center.y()*pos1.y()+center.z() *pos1.z()) - r*r;
  return b * b - 4 * a * c;
}

function dotProduct(vector1, vector2)
{
  return vector1.x() * vector2.x()
	    + vector1.y() * vector2.y() 
	    + vector1.z() * vector2.z();
}