var currentSpeed = 0;
var currentSpin = 0;
var upVector = new QVector3D(0, 0, 1);
var forwardVector = new QVector3D(1, 0, 0);
var leftVector = new QVector3D(0, -1, 0);
var playerManager;

function initialize()
{
    Component.initialSpin = 0;
    Component.reductionPerSecond = 0.1;
    Component.speedIncreasePerEnergyPoint = 0.3;
//    Component.metaInfo().setPropertyRange("reductionPerSecond", 0.0, 1.0);
}

function start()
{
    currentSpin = Component.initialSpin;
    
    // These three are used to allow the player to push energy onto the particle,
    // which then reacts accordingly
    
    Component.speedEnergy = 0;
    Component.rightEnergy = 0;
    Component.leftEnergy = 0;
    Component.age = 0;
    Component.velocityVector = new QVector3D(0, 0, 0);
    Component.collidableParticle = true;
    Component.dieNext = false;
    
    Component.currentSpeed = currentSpeed;
    Component.currentSpin= currentSpin;
    Component.upVector = upVector;
    Component.forwardVector = forwardVector;
    Component.leftVector = leftVector;
    
    playerManager = Game.getFromScene("MasterControl").PlayerManager;
}

function adjustMovement(time)
{
    var fixedTime = time / 100;
    
    currentSpin = Component.currentSpin;
    
    currentSpeed += Component.speedEnergy;
    Component.speedEnergy = 0;
    currentSpin += Component.leftEnergy - Component.rightEnergy;
    Component.rightEnergy = 0;
    Component.leftEnergy = 0;
    
    var adjustment = Component.reductionPerSecond * fixedTime;
    // Reduce the speed by Component.reduction adjusted by time
    currentSpeed -= adjustment;
    if(currentSpeed < 0)
        currentSpeed = 0;
    // Reduce the spin by the same amount as speed, though approximating initial spin in stead of 0
    var initSpin = Component.initialSpin;
    if(currentSpin < initSpin)
    {
        currentSpin += adjustment
        if(currentSpin > initSpin)
            currentSpin = initSpin;
    }
    else
    {
        currentSpin -= adjustment
        if(currentSpin < initSpin)
            currentSpin = initSpin;
    }
    
    // Move particle according to speed and spin
    var rotate = 0;
    if(currentSpin != 0)
    {
        rotate = currentSpin*(time/1000);
        GameObject.rotate(rotate, upVector);
    }
    
    if(playerManager.rotate && Component == playerManager.currentParticle.ParticleMotion)
    {
      particleToHitPos = playerManager.nearest.position;
    
      
      var velVector = Component.forwardVector;//new QVector2D( playerManager.nearest.ParticleMotion.velocityVector.x(),playerManager.nearest.ParticleMotion.velocityVector.y());
      
      var particleToHitVector = new QVector2D(particleToHitPos.x() - playerManager.currentParticle.position.x(),
					      particleToHitPos.y() - playerManager.currentParticle.position.y());

    var dot = velVector.x()*particleToHitVector.x() + velVector.y()*particleToHitVector.y();//QVector2D.dotProduct(velVector, particleToHitVector);
     	
    var lengthThing = Math.sqrt(velVector.x()*velVector.x() +velVector.y()*velVector.y()) * Math.sqrt(particleToHitVector.x()*particleToHitVector.x() + particleToHitVector.y()*particleToHitVector.y());
    
    var angle = Math.acos(dot/lengthThing);
          
      angle = angle * (180/Math.PI);
      
      angle = angle == 0 ? angle : 180 - angle;
 
      
      if(angle !=0)//|| angle < 0)
      {
        var factor = 2;
      
        var leftVector = Component.leftVector;
         dot = leftVector.x()*particleToHitVector.x() + leftVector.y()*particleToHitVector.y();//QVector2D.dotProduct(velVector, particleToHitVector);
         lengthThing = Math.sqrt(leftVector.x()*leftVector.x() +leftVector.y()*leftVector.y()) *Math.sqrt(particleToHitVector.x()*particleToHitVector.x() +particleToHitVector.y()*particleToHitVector.y());
                  
        var rAngle = Math.acos(dot/lengthThing)
        rAngle = rAngle *(180/Math.PI);
        rAngle = rAngle == 0 ? rAngle : 180 - rAngle;
        var rightTurn = rAngle > 90;
        //Component.debug("rAngle " +rAngle);
        //Component.debug("rightTurn " +rightTurn);
        if(rightTurn)
            rotate = Math.max(-3.6*(40/100)*factor, -angle);
        else
            rotate =  Math.min(3.6*(40/100)*factor,angle);
	    
        //Component.debug("angle " +angle);
        //Component.debug("rotate " +rotate);
        var up = playerManager.currentParticle.ParticleMotion.upVector;
        if(rotate != 0)
            playerManager.currentParticle.rotate(rotate, up);
      }
    }
    
    var rotationQuaternion = QQuaternion.fromAxisAndAngle(upVector, rotate);
    if(currentSpeed != 0)
    {
        var movement = new QVector3D(currentSpeed * fixedTime * Component.speedIncreasePerEnergyPoint, 0, 0);
        var x = movement.x()* Math.cos((rotate*(Math.PI/180)))- movement.y() *Math.sin((rotate*(Math.PI/180)));
        var y = movement.x()*Math.sin((rotate*(Math.PI/180))) + movement.y() *Math.cos((rotate*(Math.PI/180)));
        //movement = rotationQuaternion.rotatedVector(movement);
        var movement = new QVector3D(x,y, 0);
        GameObject.translate(movement);
    }
    Component.currentSpeed = currentSpeed;
    Component.currentSpin = currentSpin;
    
    var x = (currentSpeed * Component.speedIncreasePerEnergyPoint)* Math.cos((rotate*(Math.PI/180))) - Component.velocityVector.y() *Math.sin((rotate*(Math.PI/180)));
    var y = (currentSpeed * Component.speedIncreasePerEnergyPoint)*Math.sin((rotate*(Math.PI/180))) + Component.velocityVector.y() *Math.cos((rotate*(Math.PI/180)));
    
    Component.velocityVector = new QVector3D(x, y, 0);


    x = Component.forwardVector.x()*Math.cos((rotate*(Math.PI/180))) - Component.forwardVector.y() *Math.sin((rotate*(Math.PI/180)));
    y = Component.forwardVector.x()*Math.sin((rotate*(Math.PI/180)))+ Component.forwardVector.y() *Math.cos((rotate*(Math.PI/180)));
    
    Component.forwardVector = new QVector3D(x, y, 0);
    
    x = Component.leftVector.x()*Math.cos((rotate*(Math.PI/180))) - Component.leftVector.y() *Math.sin((rotate*(Math.PI/180)));
    y = Component.leftVector.x()*Math.sin((rotate*(Math.PI/180))) + Component.leftVector.y() *Math.cos((rotate*(Math.PI/180)));
    
    Component.leftVector = new QVector3D(x, y, 0);
    /*Component.velocityVector = rotationQuaternion.rotatedVector(new QVector3D(currentSpeed * Component.speedIncreasePerEnergyPoint, 0, 0));
    Component.forwardVector = rotationQuaternion.rotatedVector(new QVector3D(1, 0, 0));
    Component.leftVector = rotationQuaternion.rotatedVector(new QVector3D(0, -1, 0));//*/
}

function collissionChecker()
{
    if(GameObject.SphereCollider.isColliding() && !GameObject.dieNext)
    {
        var other = GameObject.SphereCollider.collidesWith();
        if(!other.ParticleMotion.collidableParticle)
            return;
        if(!other.enabled)
            return;
	
	//hack hack
	playerManager.stop = true;
	
        var thisVelocity = Component.velocityVector;
        var otherVelocity = other.ParticleMotion.velocityVector;
        // This can't be right, there /has/ to be a better way of doing this...
        var impactVector = new QVector3D(
            Math.abs(thisVelocity.x() - otherVelocity.x()),
            Math.abs(thisVelocity.y() - otherVelocity.y()),
            Math.abs(thisVelocity.z() - otherVelocity.z()));
//        GameObject.debug("collision power: " + Component.impactVector.toString() + " (from adding " + thisVelocity + " and " + other.ParticleMotion.velocityVector + ")");


        var impactLevels = GameObject.ParticleInfo.impactLevels;
        impactLevels.reverse();
        //Component.debug("Looking for the right level for power " + impactVector.length());
        //Component.debug("Searching through " + impactLevels.length + " impact levels for " + GameObject.name + ": " + impactLevels);
        if(impactLevels.length > 0)
        {
            for(var i = 0; i <= impactLevels.length; i++)
            {
                var level = impactLevels[i];
                if(level[0] >= impactVector.length())
                {
                    //Component.debug("Level discovered, wah! Level: " + level[1]);
                    var amount = 0;
                    var newParticles = playerManager.spawnParticles;
                    for(var j = 0; j <= level[1].length; j++)
                    {
                        if(j % 2 == 0)
                        {
                            amount = level[1][j];
                        }
                        else
                        {
                            while(amount)
                            {
                                //Component.debug("Creating new object: " + level[1][j]);
                                var newParticle = Game.clone(GameObject);
                                newParticle.setEnabled(false);
//                                newParticle.name = level[1][j];
//                                newParticle.ParticleInfo.particleName = level[1][j];
                                newParticle.ParticleInfo.changeTo = level[1][j];
                                newParticle.ParticleMotion.age = 0;
                                newParticles.push(newParticle);
                                amount--;
                            }
                        }
                    }
                    playerManager.spawnParticles = newParticles;
                    if(playerManager.currentParticle == other || playerManager.currentParticle == GameObject)
                    {
                        var oPI = other.ParticleInfo;
                        var oPM = other.ParticleMotion;
                        var tPI = GameObject.ParticleInfo;
                        var tPM = Component;
                        var v1l = oPM.velocityVector.length();
                        var v2l = tPM.velocityVector.length();
                        var vf = (oPI.mass * v1l + tPI.mass * v2l) / (oPI.mass + tPI.mass);
                        var Ek1 = 0.5 * oPI.mass * Math.pow(v1l, 2);
                        var Ek2 = 0.5 * tPI.mass * Math.pow(v2l, 2);
                        var K = Ek1 + Ek2 - vf;
                        var normalizedAngle = 1;
                        var points = 1 + Math.pow(tPI.mass * normalizedAngle * K, 2) + level[2];
                        points = Math.floor(Math.sqrt(points));
                        playerManager.addPoints += points;
                        GameObject.debug(GameObject.name + " colliding with " + other.name + " at position " + GameObject.position + " with the impact " + impactVector + " yielding " + points + " points");
                    }
                    break;
                }
            }
        }
        
        playerManager.spawnParticlesPosition = GameObject.position;
        playerManager.spawnParticlesAdjustment = impactVector;
        GameObject.dieNext = true;
    }
}

function update()
{
  //hack hack
  var time = 40;
    if(playerManager.stop)
      return;
      
    Component.age += time;
    if(GameObject.dieNext)
    {
        //Component.debug("Killed at age " + Component.age);
        GameObject.deleteLater();
        
        var killParticles = playerManager.killParticles;
        killParticles.push(GameObject);
        playerManager.killParticles = killParticles;
        
        var tmpColor = new QColor(0, 0, 0, 0);
        GameObject.Shadow.color = tmpColor;
        GameObject.Atom.color = tmpColor;
        GameObject.Glow.color = tmpColor;
        GameObject.Triangle.color = tmpColor;
        GameObject.setEnabled(false);
    }
    else
    {      
        adjustMovement(time);
        if(Component.age > 500 && Component.collidableParticle)
            collissionChecker();
    }
    if(Component.age > GameObject.ParticleInfo.lifeTime)
    {
//        Component.debug("Particle " + GameObject.name + " decayed");
        GameObject.dieNext = true;
        if(playerManager.currentParticle == GameObject)
        {
            playerManager.currentParticle = 0;
        }
    }
}

function draw()
{
}
