let qrt = prompt("Please enter the quantities of product")
let sum = 0
for(var i = 1; i <= qrt; i++)
{
  let item_price = prompt("Price of item: " + i)
  document.getElementById("price-list").innerHTML += "Item no." + i + ": " + item_price + " Bath" + "<br>"
  sum += parseInt(item_price)
}
document.getElementById("price-list").innerHTML += "Summary: " + sum + " Bath"