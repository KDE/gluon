this.snake = [];
this.numRows = 50;
this.numColumns = 50;
this.table = [this.numRows * this.numColumns];
this.links = [];
this.directionArray = [];
this.head = {row: 0, column: 0};
this.scores = 0;

this.rand = function(n)
{
    return (Math.floor(Math.random() * n));
}

this.directions = function(direction)
{
    if (this.directionArray[this.directionArray.length-1] != direction)
        this.directionArray.push(direction);
}

this.isFree = function(row, column)
{
    return table[row * this.numColumns + column] == undefined;
}

this.isHead = function(row, column)
{
    return head && head.column == column && head.row == row;
}

this.isCookie = function(row, column)
{
    return cookie && cookie.row == row && cookie.column == column;
}

this.createCookie = function() {
  
    if (this.numRows * this.numColumns - this.snake.length < 10)
        return;

    var column = rand(this.numColumns);
    var row = rand(this.numRows);
    while (!isFree(row, column)) {
        ++column;
        if (column == this.numColumns) {
            column = 0;
            ++row;
            if (row == this.numRows)
                row = 0;
        }
    }

    var newPlayer = Game.clone(Game.getFromScene("Cookie"));
    newPlayer.position = new QVector3D(0, -50, 2); 
    newPlayer.enabled = true;
    cookie.row = row;
    cookie.column = column;
}

this.initialize = function()
{
}

this.start = function()
{
    this.table = [this.numRows * this.numColumns];
    this.snake = [];
    this.directionArray = [];

    for (var i = 0; i < this.numRows * this.numColumns; ++i) {
        var bodyElement = Game.getFromScene("BodyElement"));
        links.push(Game.clone(bodyElement);
    }   

    this.head = this.links[0];
    this.snake.push(head);
    this.head.row = numRows/2 -1;
    this.head.column = numColumns/2 -1;
    this.head.spawned = true;
 
    this.score = 0;

    for (var i = 0; i < 4; ++i) {
        newLink = this.links[this.snake.length];
        newLink.rotation = this.snake[this.snake.length-1].rotation;
        this.snake.push(newLink);
    }

    var lastLink = this.snake[this.snake.length-1];
    this.table[lastLink.row * this.numColumns + this.lastLink.column] = undefined;
}

this.move = function()
{
    if (!this.head)
        return;

    var dir = this.direction;

    if (directionArray.length) {
        dir = directionArray.shift();
    }

    if (state == "starting") {
        var turn = (dir - headDirection);
        head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
        headDirection = dir;
        return;
    }

    var row = this.head.row;
    var column = this.head.column;

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
    if (row < 0 || row >= this.numRows
        || column < 0 || column >= this.numColumns
        || !isFree(row, column)) {
        var turn = (dir - headDirection);
        this.head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
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
    this.head.row = row;
    this.head.column = column;
    this.table[row * this.numColumns + column] = this.head;

    var turn = (dir - headDirection);
    head.rotation += turn == -3 ? 1 : (turn == 3 ? -1 : turn );
    headDirection = dir;

    if (isCookie(row, column)) {
        ++this.score;
        createCookie();
    }
}

this.update = function(time)
{
    this.move();
}

this.draw = function(timeLapse)
{
}

this.stop = function()
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

this.cleanup = function()
{
}
