## Introduction
An interesting application of Monte Carlo methods is estimating the value of pi. By estimating the area of a unit circle and using the equation of the area of a circle, we can find pi. This is part of exercise 6.5 in the computational physics textbook by Landau (2015)[^1] on Monte Carlo integration.

## Quasi-random Sequences
Randomness in computers are usually implemented using pseudo-random sequences. Although it is possible to use numbers generated using pseudo-random sequences for Monte Carlo methods, it is possible to achieve faster convergence using quasi-random sequences instead. Quasi-random sequences, also known as low-discrepancy sequence provide an imporvement as it covers the space more evenly than normal random sequences.

## Halton Sequence

## Sobol Sequence
The implementation of the sobol sequence follows the paper by Bratley and Fox (1988)[^2].
### Direction Numbers
The direction numbers are prrovided by Stephen Joe and Frances Kuo[^3]. Although we require only 2 dimensions, the numbers provided support up to 21201 dimensions. 

## Finding Pi
![gif](media/monte-carlo2.gif)

[^1]: Landau, R. H. (2015). Computational physics problem solving with python. John Wiley & Sons, Incorporated. 

[^2] Bratley and Fox (1988) Algorithm 659: Implementing Sobol's quasirandom sequence generator

[^3] https://web.maths.unsw.edu.au/~fkuo/sobol/
