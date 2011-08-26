var allParticles;
var currentParticle;
var mainCamera;
var level;
var energyText;
var contextText;
var infoText;
var pointsText;
var background;
var viewCone2;
var viewCone1;
var viewCone3;
var character;
var particleAtoms = new Object();

var pointsPerSecond = 100000;
var textAdjust = new QVector3D(-4.8, -48, 0);
var contextAdjust = new QVector3D(3.8, -48, 0);
var pointsAdjust = new QVector3D(3.8, 46, 0);
var infoAdjust = new QVector3D(0.2, 1, 0);
var upwards = new QVector3D(0, 0, 50);

function initialize()
{
    Component.availableEnergy = 100;
    Component.maxEnergy = 100;
    Component.energyDrainPerSecond = 25;
    Component.energyRegainedPerSecond = 5;
    
    Component.perceptionSpeed = 50;
    Component.context = 0;
    
    //hack hack
    Component.stop = false;
    // Component.metaInfo().setPropertyRange("context", 0, 1);
    // Component.metaInfo().setPropertySteps("context", 2);
}

function start()
{
    Component.switchParticleTo = 0;
    Component.currentParticle = 0;
    
    allParticles = new Array();
    allParticles.push(Game.getFromScene("Berylium-10"));
    allParticles.push(Game.getFromScene("Nitrogen-14"));
    Component.allParticles = allParticles;
    mainCamera = Game.getFromScene("Camera");
    level = Game.getFromScene("LevelData");
    energyText = Game.getFromScene("EnergyText");
    contextText = Game.getFromScene("ContextText");
    infoText = Game.getFromScene("ParticleInfo");
    pointsText = Game.getFromScene("PointsText");
    background = Game.getFromScene("Background");
    //Component.currentParticle = Game.getFromScene("Berylium-10");
    Component.switchParticleTo = Game.getFromScene("Berylium-10");
    Game.getFromScene("Berylium-10").ParticleInfo.changeTo = "Berylium-10";
    Game.getFromScene("Nitrogen-14").ParticleInfo.changeTo = "Nitrogen-14";
    Component.nearest = Game.getFromScene("Nitrogen-14");
    Component.points = 0;
    Component.addPoints = 0;
    
    /*viewCone1 = GameObject.ViewCone1;
    viewCone2 = GameObject.ViewCone2;
    viewCone3 = GameObject.ViewCone3;*/
    character = GameObject.Character;
    Component.rotate = false;
    
    /*GameObject.BeryliumSpeed.perceptionInfo = Game.getFromScene("Berylium-10").SpeedInfo;
    GameObject.BeryliumSpin.perceptionInfo = Game.getFromScene("Berylium-10").SpinInfo;
    GameObject.BeryliumVelocityvector.perceptionInfo = Game.getFromScene("Berylium-10").VelocityInfo;
    GameObject.BeryliumPosition.perceptionInfo = Game.getFromScene("Berylium-10").Position;
    
    GameObject.NitrogenSpeed.perceptionInfo = Game.getFromScene("Nitrogen-14").SpeedInfo;
    GameObject.NitrogenSpin.perceptionInfo = Game.getFromScene("Nitrogen-14").SpinInfo;
    GameObject.NitrogenVelocityvector.perceptionInfo = Game.getFromScene("Nitrogen-14").VelocityInfo;
    GameObject.NitrogenPosition.perceptionInfo = Game.getFromScene("Nitrogen-14").Position;
    
    particleAtoms[Game.getFromScene("Berylium-10").SpeedInfo] = GameObject.BeryliumSpeed;	
    particleAtoms[Game.getFromScene("Berylium-10").SpinInfo] = GameObject.BeryliumSpin;
    particleAtoms[Game.getFromScene("Berylium-10").VelocityInfo] = GameObject.BeryliumVelocityvector;
    particleAtoms[Game.getFromScene("Berylium-10").PositionInfo] = GameObject.BeryliumPosition;
    
    
    particleAtoms[Game.getFromScene("Nitrogen-14").SpeedInfo] = GameObject.NitrogenSpeed;
    particleAtoms[Game.getFromScene("Nitrogen-14").SpinInfo] = GameObject.NitrogenSpin;
    particleAtoms[Game.getFromScene("Nitrogen-14").VelocityInfo] = GameObject.NitrogenVelocityvector;
    particleAtoms[Game.getFromScene("Nitrogen-14").PositionInfo] = GameObject.NitrogenPosition;*/
    
    Component.particleAtoms = particleAtoms;
    Component.debug(particleAtoms.length);
    // This is a hack for spawning particles in the right place and such...
    Component.killParticles = new Array();
    Component.spawnParticles = new Array();
    Component.spawnParticlesPosition = new QVector3D(0, 0, 0);
    Component.spawnParticlesAdjustment = new QVector3D(0, 0, 0);
}

var oneMoreTime = false;
function update(time)
{
  //hack hack
  var time = 40;
    if(Component.stop)
      return;
  
    if(Component.spawnParticles.length > 0)
    {
        //Component.debug("Changing information for " + Component.spawnParticles.length + " new particles");
        var newParticles = Component.spawnParticles;
        Component.spawnParticles = new Array();
        
        var pos = Component.spawnParticlesPosition;
        var startVector = new QVector3D(15, 0, 0);
        var velVector = new QVector3D(Component.spawnParticlesAdjustment.length(), 0, 0);
        var rotateBy = 360 / newParticles.length;
        // Yes, this is pretty ugly, but hey, quick'n'dirty and whatnot ;)
        newParticles.sort(function() {return 0.5 - Math.random()});
        for(var j = 0; j < newParticles.length; j++)
        {
            var rotation = QQuaternion.fromAxisAndAngle(upwards, rotateBy * j);
            newParticles[j].position = pos;
            newParticles[j].translate(rotation.rotatedVector(startVector));
            newParticles[j].rotate(rotateBy * j, upwards);
            newParticles[j].ParticleMotion.velocityVector = rotation.rotatedVector(velVector);
            newParticles[j].ParticleMotion.speedEnergy = 10;
            newParticles[j].ParticleMotion.age = 0;
            newParticles[j].setEnabled(true);
	    
	    /*var newSpeed = new PerceptionAtom();
	    newSpeed.perceptionInfo = newParticles[j].SpeedInfo;
	    particleAtoms[newParticles[j].SpeedInfo] = newSpeed;
	    Component.gameObject.addComponent(newSpeed);
	    
	    var newSpin = new PerceptionAtom();
	    newSpin.perceptionInfo = newParticles[j].SpinInfo;
	    particleAtoms[newParticles[j].SpinInfo] = newSpin;
	    Component.gameObject.addComponent(newSpin);
	    
	    var newVelocity = new PerceptionAtom();
	    newVelocity.perceptionInfo = newParticles[j].VelocityInfo;
	    particleAtoms[newParticles[j].VelocityInfo] = newVelocity;
	    Component.gameObject.addComponent(newVelocity);
	    
	    var newPos = new PerceptionAtom();
	    newPos.perceptionInfo = newParticles[j].PositionInfo;
	    particleAtoms[newParticles[j].PositionInfo] = newPos;
	    Component.gameObject.addComponent(newPos);	 */   
	    
            allParticles.push(newParticles[j]);
        }
        oneMoreTime = true;
    }
    
    if(Component.killParticles.length > 0)
    {
        //Component.debug("Killing " + Component.killParticles.length + " particles");
        var killParticles = Component.killParticles;
        for(item in killParticles)
        {
            allParticles.splice(allParticles.indexOf(killParticles[item]), 1);
            if(currentParticle == killParticles[item])
                Component.currentParticle = 0;
	    
	    /*Component.gameObject().removeComponent(particleAtoms[killParticles[item].SpeedInfo]);
	    delete particleAtoms[killParticles[item].SpeedInfo];
	    Component.gameObject().removeComponent(particleAtoms[killParticles[item].SpinInfo]);
	    delete particleAtoms[killParticles[item].SpinInfo];
	    Component.gameObject().removeComponent(particleAtoms[killParticles[item].PositionInfo]);
	    delete particleAtoms[killParticles[item].PositionInfo];
	    Component.gameObject().removeComponent(particleAtoms[killParticles[item].VelocityInfo]);
	    delete particleAtoms[killParticles[item].VelocityInfo];*/
        }
        Component.killParticles = new Array();
    }
    
    if(Component.currentParticle == 0)
    {
        if(!oneMoreTime)
        {
            for(item in allParticles)
            {
                if(allParticles[item].enabled && allParticles[item].ParticleInfo.collidableParticle)
                {
                    Component.switchParticleTo = allParticles[item];
                    break;
                }
            }
        }
        oneMoreTime = false;
    }
    
    if(Component.switchParticleTo != 0)
    {      
        currentParticle = Component.switchParticleTo;
        Component.currentParticle = currentParticle;
        Component.debug("Switched to the " + currentParticle.ParticleInfo.particleName + " particle named " + currentParticle.name);
        Component.switchParticleTo = 0;
	
	/*var viewInfo = Component.currentParticle.ParticleInfo.viewConeInfo;
	if(viewInfo[0])
	{
	  viewCone1.enabled = true;
	  viewCone1.offsetAngleHorizontal = viewInfo[0][1];
	  viewCone1.extentAngleHorizontal = viewInfo[0][2];
	  viewCone1.radius = viewInfo[0][3]*3;
	  viewCone1.knowledgePrecision = viewInfo[0][4];
	}
	else
	{
	  viewCone1.enabled = false;
	}
	
	if(viewInfo[1])
	{
	  viewCone2.enabled = true;
	  viewCone2.offsetAngleHorizontal = viewInfo[1][1];
	  viewCone2.extentAngleHorizontal = viewInfo[1][2];
	  viewCone2.radius = viewInfo[1][3]*3;
	  viewCone2.knowledgePrecision = viewInfo[1][4];
	}
	else
	{
	  viewCone2.enabled = false;
	}
	
	if(viewInfo[2])
	{
	  viewCone3.enabled = true;
	  viewCone3.offsetAngleHorizontal = viewInfo[2][1];
	  viewCone3.extentAngleHorizontal = viewInfo[2][2];
	  viewCone3.radius = viewInfo[2][3]*3;
	  viewCone3.knowledgePrecision = viewInfo[2][4];
	}
	else
	{
	  viewCone3.enabled = false;
	}*/
    }
    
    if(Component.addPoints > 0)
    {
        var addPoints = Math.floor(Math.min(Component.addPoints, pointsPerSecond / time));
        Component.addPoints -= addPoints;
        Component.points += addPoints;
    }
        
    energyText.TextRenderer.setText("Energy: " + Math.round(Component.availableEnergy));

    if(currentParticle != Component.currentParticle)
    {
        currentParticle = Component.currentParticle;
    }

    Component.availableEnergy = Math.min(Component.availableEnergy + (time/1000) * Component.energyRegainedPerSecond, Component.maxEnergy);

    if(currentParticle == 0)
    {
        // View the entire level from very far above... maybe slowly rotating?
    }
    else
    {
        var newInfo = currentParticle.ParticleInfo.particleName;
        newInfo += " Speed: " + Math.round(currentParticle.ParticleMotion.currentSpeed);
        newInfo += " Spin: " + Math.round(currentParticle.ParticleMotion.currentSpin);
        infoText.TextRenderer.setText(newInfo);
        
        pointsText.TextRenderer.setText("Points: " + Component.points);

        var pos = currentParticle.position;
	GameObject.setPosition(pos);
	GameObject.setOrientation(currentParticle.orientation);
        energyText.setPosition(pos);
        energyText.translate(textAdjust);
        contextText.setPosition(pos);
        contextText.translate(contextAdjust);
        pointsText.setPosition(pos);
        pointsText.translate(pointsAdjust);
        infoText.setPosition(pos);
        infoText.translate(infoAdjust);
        mainCamera.setPosition(pos);
        mainCamera.translate(upwards);
        background.setPosition(new QVector3D(pos.x() / 2, pos.y() / 2, -3));
        
        // Rotate camera to be the same direction the current particle faces... maybe?
        // This may not look so nice in practice... needs experimentation
    }
    
    character.time = time;
}

function draw()
{
}
