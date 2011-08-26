function update()
{
}

function draw()
{
}

function getAdjustedValue(precision)
{
  Component.knowledge = new QVector3D(GameObject.ParticleMotion.velocityVector.x()*precision, GameObject.ParticleMotion.velocityVector.y()*precision, GameObject.ParticleMotion.velocityVector.z()*precision);
}

function initialize()
{
}

function stop()
{
}

function start()
{
}