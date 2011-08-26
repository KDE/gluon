var initialSpin;
var spinDeviation;
var mass;
var lifeTime;
var impactLevels;
var perceptionLimit;
var viewConeInfo;
var color;
var radius = 6;

function initialize()
{
    // This does not work yet, as values get overridden on initialize
    // since that happens after properties are set by the Component...
    // Not so clever, and we'll have to fix that... but for now, hack :P
}

function start()
{
     setParticleByName(GameObject.name);
     Component.changeTo = "";
}

function update(time)
{
    if(Component.changeTo != "")
    {
        setParticleByName(Component.changeTo);
        Component.changeTo = "";
    }
}

function setParticleByName(name)
{
    name = name.split(" ")[0];
//    Component.debug("Changing particle from " + Component.particleName + " to " + name);
    var maxParticleLifetime = 16000000;
    var collidableParticle = true;
    var particleName = name;
    switch(name)
    {
        case "Carbon-14":
            color = new QColor(255, 0, 0);
            initialSpin = 0;
            spinDeviation = 0;
            mass = 14.003281;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(20 , new Array(1, "Nitrogen-14", 1, "Electron", 1, "Electron-Antineutrino"), 0),
                new Array(70 , new Array(1, "Helion-4", 1, "Helium-3", 2, "Proton", 7, "Neutron"), 0),
                new Array(100, new Array(1, "Helion-4", 1, "Helium-3", 2, "Proton", 6, "Neutron", 1, "Up-quark", 2, "Down-quark"), 0));
            perceptionLimit = 50;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 50, 0.5),
                new Array(2, 0, 90, 25, 1.0),
                new Array(3, 180, 90, 5, 0.7));
            break;
        case "Nitrogen-14":
            color = new QColor(255, 255, 0);
            initialSpin = 10;
            spinDeviation = 0;
            mass = 14.0030740;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(70 , new Array(1, "Berylium-10", 3, "Proton", 1, "Neutron"), 0),
                new Array(100 , new Array(1, "Berylium-10", 2, "Proton", 2, "Up-quark", 1, "Down-quark"), 0));
            perceptionLimit = 25;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 25, 0.5),
                new Array(2, 0, 90, 20, 1.0),
                new Array(3, 180, 90, 10, 0.7));
            break;
        case "Berylium-10":
            color = new QColor(255, 0, 255);
            initialSpin = 0;
            spinDeviation = 0;
            mass = 10.0135337;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(20, new Array(1, "Boron-10", 1, "Electron-Antineutrino"), 555816),
                new Array(70, new Array(3, "Hydrogen-2", 1, "Proton", 7, "Neutron"), 555816),
                new Array(100, new Array(3, "Hydrogen-2", 7, "Neutron", 2, "Up-quark", 1, "Down-quark"), 555816));
            perceptionLimit = 15;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 15, 0.5),
                new Array(2, 0, 90, 10, 1.0),
                new Array(3, 180, 90, 2, 0.7));
            break;
        case "Boron-10":
            color = new QColor(0, 255, 255);
            initialSpin = 30;
            spinDeviation = 0;
            mass = 10.0129370;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(70, new Array(5, "Hydrogen-2"), 0),
                new Array(100, new Array(4, "Hydrogen-2", 1, "Proton", 1, "Up-quark", 2, "Down-quark"), 0));
            perceptionLimit = 15;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 15, 0.5),
                new Array(2, 0, 90, 10, 1.0),
                new Array(3, 180, 90, 2, 0.7));
            break;
// D'OH! Missing the particle info sheets for these two :P
/*         case "Helion-4":
            initialSpin = ;
            spinDeviation = ;
            mass = ;
            lifeTime = ;
            impactLevels = new Array(
                new Array( , new Array(), ),
                new Array( , new Array(), ),
                new Array( , new Array(), ));
            perceptionLimit = ;
            viewConeInfo = new Array(
                new Array(1, ),
                new Array(2, ),
                new Array(3, ));
             break;*/
/*         case "Helium-3":
            initialSpin = ;
            spinDeviation = ;
            mass = ;
            lifeTime = ;
            impactLevels = new Array(
                new Array( , new Array(), ),
                new Array( , new Array(), ),
                new Array( , new Array(), ));
            perceptionLimit = ;
            viewConeInfo = new Array(
                new Array(1, ),
                new Array(2, ),
                new Array(3, ));
             break;*/
        case "Hydrogen-2":
            color = new QColor(0, 255, 0);
            initialSpin = 10;
            spinDeviation = 0;
            mass = 2.0141018;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(70, new Array(1, "Proton", 1, "Neutron"), 1000),
                new Array(90, new Array(1, "Proton", 1, "Up-quark", 2, "Down-quark"), 1000000),
                new Array(100, new Array(3, "Up-quark", 3, "Down-quark"), 1000));
            perceptionLimit = 100;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 100, 0.5),
                new Array(2, 0, 90, 50, 1.0),
                new Array(3, 180, 90, 10, 0.7));
            break;
        case "Neutron":
            color = new QColor(0, 0, 255);
            initialSpin = 5;
            spinDeviation = 5;
            mass = 1.008664915;
            lifeTime = 14.7661667;
            impactLevels = new Array(
                new Array(90, new Array(1, "Neutron"), 0),
                new Array(100, new Array(1, "Up-quark", 2, "Down-quark"), 0));
            perceptionLimit = 5;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 5, 1.0));
            break;
        case "Proton":
            color = new QColor(255, 128, 255);
            initialSpin = 5;
            spinDeviation = 5;
            mass = 1.00727646677;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(90, new Array(1, "Proton"), 0),
                new Array(100, new Array(2, "Up-quark", 1, "Down-quark"), 0));
            perceptionLimit = 5;
            viewConeInfo = new Array(
                new Array(3, 1, 0, 180, 5, 1.0));
            break;
        case "Electron":
            color = new QColor(255, 128, 128);
            initialSpin = 5;
            spinDeviation = 0;
            mass = 0.0005485790943;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(100, new Array(1, "Photon"), 1000000));
            perceptionLimit = 1000;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 100, 0.1),
                new Array(2, 0, 180, 1000, 0.5),
                new Array(3, 0, 90, 500, 1.0));
            break;
        case "Electron-Antineutrino":
            color = new QColor(128, 255, 128);
            initialSpin = 5;
            spinDeviation = 0;
            mass = 0.0000005;
            lifeTime = maxParticleLifetime;
            impactLevels = new Array(
                new Array(100, new Array(1, "Photon"), 1000000));
            perceptionLimit = 1000;
            viewConeInfo = new Array(
                new Array(1, 0, 23, 1000, 0.9),
                new Array(2, 0, 45, 500, 0.4));
            break;
        case "Up-quark":
            color = new QColor(0, 128, 128);
            initialSpin = 5;
            spinDeviation = 0;
            mass = 0.002;
            lifeTime = 150;
            impactLevels = new Array(
                new Array(100, new Array(1, "Gamma-ray"), 2000000));
            perceptionLimit = 20;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 10, 0.1),
                new Array(2, 0, 180, 20, 0.9));
            break;
        case "Down-quark":
            color = new QColor(128, 0, 128);
            initialSpin = 5;
            spinDeviation = 0;
            mass = 0.006;
            lifeTime = 150;
            impactLevels = new Array(
                new Array(100, new Array(1, "Gamma-ray"), 6000000));
            perceptionLimit = 20;
            viewConeInfo = new Array(
                new Array(1, 0, 180, 10, 0.1),
                new Array(2, 0, 180, 20, 0.9));
            break;
        case "Gamma-ray":
            color = new QColor(128, 128, 128);
            collidableParticle = false;
            initialSpin = 0;
            spinDeviation = 10;
            mass = 1;
            lifeTime = 10;
            impactLevels = new Array();
            perceptionLimit = 0;
            viewConeInfo = new Array();
            break;
        case "Photon":
            color = new QColor(255, 255, 255);
            collidableParticle = false;
            initialSpin = 10;
            spinDeviation = 0;
            mass = 1;
            lifeTime = 100;
            impactLevels = new Array();
            perceptionLimit = 0;
            viewConeInfo = new Array();
            break;
        default:
            // PARTICLE UNKNOWNEDED!!111elebenty
            particleName = "UNKNOWN! (" + name + ")";
            color = new QColor(0, 128, 0);
            collidableParticle = false;
            initialSpin = 0;
            spinDeviation = 0;
            mass = 1;
            lifeTime = 100;
            impactLevels = new Array();
            perceptionLimit = 100;
            viewConeInfo = new Array();
            break;
    }
    Component.collidableParticle = collidableParticle;
    Component.particleName = particleName;
    Component.initialSpin = initialSpin;
    Component.lifeTime = lifeTime * 200;
    Component.spinDeviation = spinDeviation;
    Component.mass = mass;
    Component.impactLevels = impactLevels;
    Component.perceptionLimit = perceptionLimit;
    Component.viewConeInfo = viewConeInfo;
    Component.color = color;

    GameObject.SphereCollider.enabled = collidableParticle;
    GameObject.name = particleName;
    GameObject.ParticleMotion.collidableParticle = collidableParticle;
    GameObject.ParticleMotion.initialSpin = initialSpin + (Math.random() * spinDeviation);
    GameObject.Atom.setColor(color);
    GameObject.Shadow.setColor(color);
    GameObject.Glow.setColor(color);
/*    if(collidableParticle)
        Component.debug("Particle morphed into the collidable particle " + particleName);
    else
        Component.debug("Particle morphed into the NON-collidable particle " + particleName);*/
}
