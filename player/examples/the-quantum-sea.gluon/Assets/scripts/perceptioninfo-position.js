var particleMotion;

function update()
{
}

function draw()
{
}

function getAdjustedValue(precision)
{
  Component.knowledge = new QVector3D(GameObject.position.x()* precision, GameObject.position.y()* precision, GameObject.position.z()* precision);
}

function initialize()
{
  particleMotion = GameObject.ParticleMotion;
}

function stop()
{
}

function start()
{
}