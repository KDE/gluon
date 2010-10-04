var xdir = 10;
var ydir = -5;

var controller = null;
var bullet = null;
var bulletChance = 0.005;
var alive = true;
var deathAnimTime = 439; // The length of the quiet explosion sound
var deathAnimTimeRemaining = 0;

function start() {
	controller = Game.getFromScene("Background").ControllerScript;
	bullet = Game.getFromScene("Bullet");
	deathAnimTimeRemaining = deathAnimTime;
	
}

function update(time) {

	if(alive)
	{
		if(controller.paused)
			return;
		
		GameObject.translate(xdir * (time/1000), 0, 0);
		
		var position = GameObject.position;
		if(position.x() > 35 || position.x() < -35) {
			GameObject.translate(0, ydir, 0);
			xdir = -xdir;
		}
		
		if(GameObject.BulletCollider.isColliding() || GameObject.PlayerCollider.isColliding())
		{
			alive = false;
			GameObject.SpriteRenderer.setMaterial("Invaders/Assets/Material/Enemy_Fade");
			GameObject.Kapow.play();
			Game.enemies--;
		}
		
		if(Game.random() < bulletChance)
		{
			var newBullet = Game.clone(bullet);
			newBullet.position = GameObject.position;
			newBullet.enabled = true;
			newBullet.Collider.collisionGroup = 2;
			newBullet.rotate(180, new QVector3D(0, 0, 1));
		}
	}
	else
	{
		var scaleVal = 1 + (deathAnimTimeRemaining / deathAnimTime);
		GameObject.setScale(new QVector3D(scaleVal, scaleVal, 1));
		
		var color = GameObject.SpriteRenderer.material.materialColor;
		color.setAlpha(255 * (scaleVal - 1));
		GameObject.SpriteRenderer.material.materialColor = color;
		
		deathAnimTimeRemaining = deathAnimTimeRemaining - time;

		if(deathAnimTimeRemaining < 0)
			GameObject.destroy();
	}

}
