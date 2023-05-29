// let inputNumber = prompt("Please enter your lucky number")
// console.log("Your lucky number is: " + inputNumber)
// console.log("Wining Number: " + Math.floor(Math.random() * 100))
let input = document.getElementById("input").innerHTML = prompt("Please enter your lucky number")
let random = document.getElementById("WinningNumber").innerHTML =  Math.floor(Math.random() * 100)

if (input == random)
{
    document.getElementById("result").innerHTML = "You Win the Loto!!!!"
}
else 
{
    document.getElementById("result").innerHTML = "Better Luck Next Timt :)"
}

console.log(1 == 1)
console.log(1 == "1")
console.log(2 == 1)
console.log(1 === "1")
console.log(1 != 7)
console.log(1 !== "1")