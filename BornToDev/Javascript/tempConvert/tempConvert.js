function toCelsius(farenheit)
{
  let celsius = (farenheit - 32) * 5 / 9
  return celsius.toFixed(2) + " °C"
}

function toFarenheit(celsius)
{
  let farenheit = (celsius * 9 / 5) + 32
  return farenheit.toFixed(2) + " °F"
}

function display(elemenId, value)
{
  document.getElementById(elemenId).innerHTML = value
}

function toCelsiusProgram(value)
{
  alert(toCelsius(value))
}

function toFarenheitProgram(value)
{
  alert(toFarenheit(value))
}