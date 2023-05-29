let score = prompt("Your Score: ")

if (score >= 80)
{
    document.getElementById("result").innerHTML = "You get an A grade"
}
else if (score >= 70)
{
    document.getElementById("result").innerHTML = "You get a B grade"
}
else if (score >= 60)
{
    document.getElementById("result").innerHTML = "You get a C grade"
}
else if (score >= 50)
{
    document.getElementById("result").innerHTML = "You get a D grade"
}
else
{
    document.getElementById("result").innerHTML = "You failed"
}