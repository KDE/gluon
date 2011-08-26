var bridge2;
var bridge2time = 1376780 / 44.1;
var couplet411;
var couplet411time = 1376780 / 44.1;
var couplet412;
var couplet412time = 1376780 / 44.1;
var couplet42break;
var couplet42breaktime = 1376780 / 44.1;
var couplet42;
var couplet42time = 1376780 / 44.1;
var refrain4;
var refrain4time = 2753560 / 44.1;

var nowPlaying;
var timeUntilNext = 0;
var playbackQueue = new Array();
var playbackQueueTimes = new Array();

function start()
{
    bridge2 = GameObject.bridge2;
    couplet411 = GameObject.couplet411;
    couplet412 = GameObject.couplet412;
    couplet42break = GameObject.couplet42break;
    couplet42 = GameObject.couplet42;
    refrain4 = GameObject.refrain4;
    pushCouplets();
}

function update(time)
{
    if(timeUntilNext <= 0)
    {
        nowPlaying = playbackQueue.shift();
        Component.debug("Now playing: " + nowPlaying.name);
        nowPlaying.play();
        timeUntilNext = playbackQueueTimes.shift();
        
        if(playbackQueue.length == 0)
            pushNextBlock();
    }
    timeUntilNext -= time;
}

function pushNextBlock()
{
    // Instructions from Przemysław
    // 1. Let's start with the "couplet 4.1.1" block
    // 2. The total number of following couplet blocks should be 2^n, where n
    //    is an integer greater than 1. Let's say that for now the number would
    //    be 2 or 3 with equal probability.
    // 3. The couplet variation can be for now chosen randomly from 4.1.1, 4.1.2 and 4.2, but
    // 4. The last of the couplet block before a refrain should be "couplet 4.2-break"
    // 5. The refrain block can't follow a refrain block
    // 6. The bridge block can be put only after the refrain block
    // 7. The bridge block can be followed only by a couplet block
    // 8. After a refrain there can be a bridge or a couplet, with equal probability.
    if(nowPlaying == bridge2)
    {
        pushCouplets();
    }
    else if(nowPlaying == couplet411)
    {
        Component.debug("This shouldn't happen: couplet411");
        // This shouldn't happen...
    }
    else if(nowPlaying == couplet412)
    {
        Component.debug("This shouldn't happen: couplet412");
        // This shouldn't happen...
    }
    else if(nowPlaying == couplet42break)
    {
        Component.debug("Pushing a refrain");
        playbackQueue.push(refrain4);
        playbackQueueTimes.push(refrain4time);
    }
    else if(nowPlaying == couplet42)
    {
        Component.debug("This shouldn't happen: couplet42");
        // This shouldn't happen...
    }
    else if(nowPlaying == refrain4)
    {
        var rnd = Math.random();
        if(rnd < 0.5)
        {
            Component.debug("Pushing a bridge...");
            playbackQueue.push(bridge2);
            playbackQueueTimes.push(bridge2time);
        }
        else
        {
            pushCouplets();
        }
    }
}

function pushCouplets()
{
    // First push (2^{2,3})-1 random couplets
    var n = Math.pow(2, Math.round(Math.random()) + 2) - 1;
    Component.debug("Pushing " + n + " couplets and a break");
    var previousPush;
    for(var i = 0; i < n; i++)
    {
        var rnd = Math.random();
        if(rnd < 0.33)
        {
            if(previousPush = couplet411)
            {
                previousPush = couplet42;
                playbackQueue.push(couplet42);
                playbackQueueTimes.push(couplet42time);
            }
            else
            {
                previousPush = couplet411;
                playbackQueue.push(couplet411);
                playbackQueueTimes.push(couplet411time);
            }
        }
        else if(rnd < 0.66)
        {
            if(previousPush = couplet412)
            {
                previousPush = couplet411;
                playbackQueue.push(couplet411);
                playbackQueueTimes.push(couplet411time);
            }
            else
            {
                previousPush = couplet412;
                playbackQueue.push(couplet412);
                playbackQueueTimes.push(couplet412time);
            }
        }
        else
        {
            if(previousPush = couplet42)
            {
                previousPush = couplet412;
                playbackQueue.push(couplet412);
                playbackQueueTimes.push(couplet412time);
            }
            else
            {
                previousPush = couplet42;
                playbackQueue.push(couplet42);
                playbackQueueTimes.push(couplet42time);
            }
        }
    }
    
    // Finally, push the couplet break
    playbackQueue.push(couplet42break);
    playbackQueueTimes.push(couplet42breaktime);
}
