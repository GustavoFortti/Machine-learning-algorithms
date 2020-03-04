install.packages("GA")
library(GA)

f <-function(x)
{
  resultado = 2 * x + 5
  
  if (resultado > 20) {
    return (20 - resultado)
  }
  else {
    return( resultado - 20)
  }
}