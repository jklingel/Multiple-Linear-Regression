# Multiple-Linear-Regression
Creating a multiple linear regression with two input variables in C

From the internet: "Use multiple regression when you want to analyze the relationship between a dependent variable and two or more independent variables. Use it for predictive modeling, such as estimating the value of a dependent variable (e.g., house prices) based on multiple factors like size, location, and age". This example uses two independent input variables x1 and x2 (size of house and age of house) to calculate an estimated house price y for a certain house, for which the size and the age is given.

Equations used:

y = b0 + b1*x1 + b2*x2 + ... + bn*xn

b1 = [ (Σx2²)(Σx1y) - (Σx1x2)(Σx2y) ] / [ (Σx1²)(Σx2²) - (Σx1x2)²

b2 = [ (Σx1²)(Σx2y) - (Σx1x2)(Σx1y) ] / [ (Σx1²)(Σx2²) - (Σx1x2)² 

b0 = ybar - b1*x1bar - b2*x2bar

Compile with 
  gcc -o multLinearRegression multLinearRegression.c -lm
