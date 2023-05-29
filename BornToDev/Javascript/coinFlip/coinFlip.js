let round = prompt("How many round you want to play?")
for (var i=0; i<round; i++)
{
  var answer = prompt("Head or Tail")
  var random_answer = ""
  if ((Math.floor(Math.random() * 10)) <= 4)
  {
    //Head
    random_answer = "Head"
  }
  else
  {
    //Tail
    random_answer = "Tail"
  }

  if (answer == random_answer)
  {
    alert("Win")
  }
  else
  {
    alert("Loss")
  }
}