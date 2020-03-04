install.packages("GA")
library(GA)

f <-function(x)
{
  resultado = 2 * x + 5
  
  if (resultado > 20) {
    return (20 - resultado)
  }
  else {
    return( resultado -20)
  }
}

resultado = ga("real-value", fitness = f, lower=c(-20), upper=c(20), popSize = 10, maxiter = 20, monitor = T, names = c("a"))

summary(resultado)$solution

plot(resultado)