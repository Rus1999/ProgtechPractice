function financeAmount(carPrice, downPayment)
{
  return carPrice - downPayment
}

function totalInterestCalculate(tranche, interestRatePerYear, financeAmount)
{
  // tranch convert to year be fore calculate
  return (interestRatePerYear * financeAmount * (tranche/12))
}

function totalPayment(totalInterestCalculate, financeAmount)
{
  return totalInterestCalculate + financeAmount
}

function totalPaymentAmountPerMonth(financeAmount, totalInterestCalculate, tranche)
{
  return (financeAmount + totalInterestCalculate) / tranche
}