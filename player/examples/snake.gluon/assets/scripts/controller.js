var snake = [],
numRows = 50,
numColumns = 50;
var table = [numRows * numColumns],
links = [],
directionArray = [],
head = {row: 0, column: 0},
scores = 0;

function rand(n)
{
    return (Math.floor(Math.random() * n));
}

function directions(direction)
{
    if (directionArray[directionArray.length-1] != direction)
        directionArray.push(direction);
}

function isFree(row, column)
{
    return table[row * numColumns + column] == undefined;
}

function isHead(row, column)
{
    return head && head.column == column && head.row == row;
}

function isCookie(row, column)
{
    return cookie && cookie.row == row && cookie.column == column;
}

function createCookie() {
  
    if (numRows * numColumns - snake.length < 10)
        return;

    var column = rand(numColumns);
    var row = rand(numRows);
    while (!isFree(row, column)) {
        ++column;
        if (column == numColumns) {
            column = 0;
            ++row;
            if (row == numRows)
                row = 0;
        }
    }

    var newPlayer = Game.clone(Game.getFromScene("Cookie"));
    newPlayer.position = new Vector3f(0, -50, 2); 
    newPlayer.enabled = true;
    cookie.row = row;
    cookie.column = column;
}

function initialize()
{
}

function start()
{
    table = [numRows * numColumns];
    snake = [];
    directionArray = [];

    for (var i = 0; i < numRows * numColumns; ++i) {
        var bodyElement = Game.getFromScene("BodyElement"));
        links.push(Game.clone(bodyElement);
    }   

    head = links[0];
    snake.push(head);
    head.row = numRows/2 -1;
    head.column = numColumns/2 -1;
    head.spawned = true;
 
    score = 0;

    for (var i = 0; i < 4; ++i) {
        newLink = links[snake.length];
        newLink.rotation = snake[snake.length-1].rotation;
        snake.push(newLink);
    }

    var lastLink = snake[snake.length-1];
    table[lastLink.row * numColumns + lastLink.column] = undefined;
}

function move()
{
    if (!head)
        return;

    var dir = direction;

    if (directionArray.length) {
        dir = directionArray.shift();
    }

    if (state == "starting") {
        var turn = (dir - headDirection);
        head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
        headDirection = dir;
        return;
    }

    var row = head.row;
    var column = head.column;

    if (dir == 0) {
        row = row - 1;
    } else if (dir == 1) {
        column = column + 1
    } else if (dir == 2) {
        row = row + 1;
    } else if (dir == 3) {
        column = column - 1;
    }

    //validate the new position
    if (row < 0 || row >= numRows
        || column < 0 || column >= numColumns
        || !isFree(row, column))
    {
        var turn = (dir - headDirection);
        head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
        headDirection = dir;
        // Stop the game
        return;
    }

    for (var i = snake.length-1; i > 0; --i) {
        snake[i].row = snake[i-1].row;
        snake[i].column = snake[i-1].column;
        snake[i].rotation = snake[i-1].rotation;
    }

    // Move the head
    head.row = row;
    head.column = column;
    table[row * numColumns + column] = head;

    var turn = (dir - headDirection);
    head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
    headDirection = dir;

    if (isCookie(row, column)) {
        ++score;
        createCookie();
    }
}

function update(time)
{
    move();
}

function draw(timeLapse)
{
}

function stop()
{
     activeGame = false;
     for(var i in snake)
         snake[i].dying = true;
     if (cookie) {
         cookie.destory();
     }
     lastScore = score;
     highScores.saveScore(lastScore);
}

function ceanup()
{
}

self.initialize = initialize;
self.start = start;
self.update = update;
self.draw = draw;
self.stop = stop;
self.cleanup = cleanup;
