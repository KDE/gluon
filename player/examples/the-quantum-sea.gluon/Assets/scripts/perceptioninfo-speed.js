var particleMotion;

function update()
{
}

function draw()
{
}

function getAdjustedValue(precision)
{
  Component.knowledge = particleMotion.currentSpeed * precision;
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