HomEnc
======
results.txt stores data in the following format:

 totalDegree|sizeCoeffs|numPolysGiven|

where totalDegree is the total degree of the keys f and g (e.g. f.degree(x)+f.degree(y)),
sizeCoeffs is the bound on the (absolute value) of the size of the coefficients of f and
g, and numPolysGiven is the number of polynomials given to the groebner basis function
(gb) in Macaulay2. Note that the degrees of encryptions of zero will be roughly twice
totalDegree, since we are multiplying f and g by random polynomials whose total degree
is also totalDegree, and the size of the coefficients will be roughly bounded by

 (totalDegree+1)*(sizeCoeffs^2)
 
for the same reason (the middle coefficient will be the sum of totalDegree+1 products of
size roughly sizeCoeff^2).

