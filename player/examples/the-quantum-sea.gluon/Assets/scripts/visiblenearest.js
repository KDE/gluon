var playerManager = 0;
var visibleParticles;
var viewCones;

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
  
  var allParticles = playerManager.allParticles;
  visibleParticles = new Array();
  viewCones = new Array();
  for(item in allParticles)
  {
      if(allParticles[item].enabled && allParticles[item].ParticleInfo.collidableParticle)
      {
	  if(allParticles[item] == playerManager.currentParticle)
	      continue;
	
	  var vectorToCurrent = createVector(allParticles[item].position, playerManager.currentParticle.position);
	  
          //vectorToCurrent = vectorToCurrent.normalized();
	  var forwardVecor = playerManager.currentParticle.ParticleMotion.velocityVector;//.normalized();
	  var det =  forwardVecor.x()* vectorToCurrent.y() - forwardVecor.y() * vectorToCurrent.x();
	  var angle = Math.acos((vectorToCurrent.x() * forwardVecor.x() + vectorToCurrent.y() * forwardVecor.y() + vectorToCurrent.z() * forwardVecor.z())/(vectorToCurrent.length*forwardVecor.length));
	  
	  //know it is done a little backwards but that was to clockwise thingy
	  if(det < 0)
	  {
	    angle = angle * (180/Math.PI);
	  }
	  else
	  {
	    angel = 360 - (angle * (180/Math.PI));
	  }	  
	  
	  if(Scene.MasterControl.ViewCone1.enabled)
	  {
	    if((0+Scene.MasterControl.ViewCone1.offsetAngleHorizontal) <= angle 
	      && (0+Scene.MasterControl.ViewCone1.offsetAngleHorizontal + Scene.MasterControl.ViewCone1.extentAngleHorizontal*2) >= angle)
	    {
	      if(vectorToCurrent.length() <= Scene.MasterControl.ViewCone1.radius)
	      {
		visibleParticles.push(allParticles[item]);
		viewCones.push(Scene.MasterControl.ViewCone1);
		continue;
	      }
	    }
	  }
	  
	  if(Scene.MasterControl.ViewCone2.enabled)
	  {
	    if((0+Scene.MasterControl.ViewCone2.offsetAngleHorizontal) <= angle 
	      && (0+Scene.MasterControl.ViewCone2.offsetAngleHorizontal + Scene.MasterControl.ViewCone2.extentAngleHorizontal*2) >= angle)
	    {
	      if(vectorToCurrent.length() <= Scene.MasterControl.ViewCone2.radius)
	      {
		visibleParticles.push(allParticles[item]);
		viewCones.push(Scene.MasterControl.ViewCone2);
		continue;
	      }
	    }
	  }
	  
	  if(Scene.MasterControl.ViewCone3.enabled)
	  {
	    if((0+Scene.MasterControl.ViewCone3.offsetAngleHorizontal) <= angle 
	      && (0+Scene.MasterControl.ViewCone3.offsetAngleHorizontal + Scene.MasterControl.ViewCone3.extentAngleHorizontal*2) >= angle)
	    {
	      if(vectorToCurrent.length() <= Scene.MasterControl.ViewCone3.radius)
	      {
		visibleParticles.push(allParticles[item]);
		viewCones.push(Scene.MasterControl.ViewCone3);
		continue;
	      }
	    }
	  }
      }
  }
  
  if(visibleParticles.length > 0)
  {
    var nearestParticle = visibleParticles[0];
    var viewCone = viewCones[0];
    var minLength = -1;
    for(var i = 1; i < visibleParticles.length; i++)
    {
      var vector = createVector(visibleParticles[i].position, playerManager.currentParticle.position);
      var vectorLength = vector.length();
      if(vectorLength < minLength || minLength == -1)
      {
	nearestParticle = visibleParticles;
	minLength = vectorLength;
      }
    }
    
    Character.nearestParticle = nearestParticle;
    Character.nearestParticlePrecision= viewCone.knowledgePrecision;
  }
  else
  {
    Character.nearestParticle = 0;
    Node.status = 2;
    return;
  }  
  
  Node.status = 1;
}

function createVector( head,  end)
{
  return new QVector3D(head.x() -end.x(), head.y() - end.y(), head.z() - end.z() );
}