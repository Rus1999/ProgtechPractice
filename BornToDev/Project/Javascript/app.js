var carPrice = 0
var downPayment = 0
var tranche = 0
var interestRatePerYear = 0

var financeAmount = 0
var interestTotalAmount = 0
var paymentAmount = 0
var paymentPerMonthAmount = 0

function financeCal(carPrice, downPayment)
{
  financeAmount = carPrice - downPayment
  return financeAmount
}

function interestTotalCal(financeAmount, interestRatePerYear, tranche)
{
  interestTotalAmount = (financeAmount * interestRatePerYear) * (tranche / 12)
  return interestTotalAmount
}

function paymentCal(financeAmount, interestAmount)
{
  paymentAmount = financeAmount + interestTotalAmount
  return paymentAmount
}

function paymentPerMonthCal(paymentAmount, tranche)
{
  paymentPerMonthAmount = paymentAmount / tranche
  return paymentPerMonthAmount
}

function enterAndDisplay(text)
{
  if(text == "Car Price")
  {
    carPrice = prompt("Please enter " + text)
    document.getElementById("carPrice").innerHTML = "<h6>Car Price: " + carPrice + " Bath</h6>"
  }
  else if(text == "Down Payment")
  {
    downPayment = prompt("Please enter " + text)
    document.getElementById("downPayment").innerHTML = "<h6>Down Payment: " + downPayment + " Bath</h6>"
  }
  else if(text == "Tranche")
  {
    tranche = prompt("Please enter " + text)
    document.getElementById("tranche").innerHTML = "<h6>Tranche: " + tranche + "</h6>"
  }
  else if(text == "Interest Rate Per Year")
  {
    interestRatePerYear = prompt("Please enter " + text)
    document.getElementById("interestRatePerYear").innerHTML = "<h6>Interest Rate Per Year: " + interestRatePerYear + "</h6>"
  }
}

function calculate()
{
  document.getElementById("financeAmount").innerHTML = "<h6>Total Finance: " + financeCal(carPrice, downPayment) + " Bath</h6>"
  document.getElementById("interestAmount").innerHTML = "<h6>Total Interest: " + interestTotalCal(financeAmount, interestRatePerYear, tranche) + " Bath</h6>"
  document.getElementById("paymentAmount").innerHTML = "<h6>Total Payment: " + paymentCal(financeAmount, interestAmount) + " Bath</h6>"
  document.getElementById("interestPerMonth").innerHTML = "<h6>Payment/Month: " + paymentPerMonthCal(paymentAmount, tranche) + " Bath</h6>"
}


// , tranche, interestRatePerYear
