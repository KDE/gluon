this.numRows = 1;
this.numColumns = 1;
this.waitForCookie = 0;

this.rand = function(number)
 {
   return (Math.floor(Math.random() * number));
 }

 this.isFree = function(row, column)
 {
     return board[row * this.numColumns + column] == undefined;
 }

 this.createCookie = function(value) 
 {
     if (numRows * numColumns - snake.length < 10)
         return;

     var column = rand(numColumns);
     var row = rand(numRows);
     while (!isFree(row, column)) {
         column++;
         if (column == numColumns) {
             column = 0;
             row++;
             if (row == numRows)
                 row = 0;
         }
     }

     if(cookieComponent.status != Component.Ready) {
         if(cookieComponent.status == Component.Error)
             console.log(cookieComponent.errorString());
         else
             console.log("Still loading cookieComponent");
         return;//TODO: Better error handling?
     }
     cookie = cookieComponent.createObject(head.parent);
     cookie.value = value;
     cookie.row = row;
     cookie.column = column;
 }

this.initialize = function()
{
}

this.start = function()
{
}

this.update = function(time)
{
}

this.draw = function(timeLapse)
{
}

this.stop = function()
{
}

this.cleanup = function()
{
}
