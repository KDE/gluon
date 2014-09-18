/*
 * Called when the scene any GameObject an instance of this class is
 * attached to is loaded by the engine. This will happen exactly once
 * during the instance's lifetime.
 */
function initialize()
{
}

/*
 * Called when the scene any GameObject an instance of this class is
 * attached to begins to play. This can happen multiple times over
 * the instance's lifetime.
 */
function start()
{
}

/*
 * Called a set number of times every second while the scene is active. This
 * happend after start and before stop.
 * The parameter time describes the number of milliseconds since the previous
 * update call.
 */
function update(time)
{
}

/*
 * Called any number of times every update, from 0 to many, depending on how
 * powerful the machine the game is being run on is. If you are drawing anything
 * in the game, put it in this function.
 * The parameter timeLapse contains the number of milliseconds which have passed
 * since the most recent update call.
 */
function draw(timeLapse)
{
}

/*
 * Called when the scene any GameObject an instance of this class is
 * attached to stops playing. This can happen multiple times during the
 * instance's lifetime.
 */
function stop()
{
}

/*
 * Called when the scene is unloaded by the engine. Use this to clean up
 * your object's impact on the game (such as MessageHandler subscriptions).
 * This will happen exactly once during the instance's lifetime.
 */
function cleanup()
{
}

/*
 * Here you describe which functions and other variables should be available
 * outside the the object instance. The six functions defined here are the
 * ones the engine will call, but you can also call functions on other objects
 * by defining them here. The self object is given to you by the engine. You
 * can view this as a way of creating public and private sections of the object.
 */
self.initialize = initialize;
self.start = start;
self.update = update;
self.draw = draw;
self.stop = stop;
self.cleanup = cleanup;
