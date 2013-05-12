HomEnc
======
results.txt stores data in the following format:

 totalDegree|sizeCoeffs|numPolysGiven|

where totalDegree is the total degree of the keys f and g, sizeCoeffs is the bound on
the (absolute value) of the size of the coefficients of f and g, and numPolysGiven is
the number of polynomials given to the groebner basis function (gb) in Macaulay2.
Note that the degrees of encryptions of zero will be roughly twice totalDegree, since
we are multiplying f and g by random polynomials whose total degree is also totalDegree,
and the size of the coefficients will be roughly bounded by

 (totalDegree+1)*(sizeCoeffs^2)
 
for the same reason (the middle coefficient will be the sum of totalDegree+1 products of
size roughly sizeCoeff^2).

ZpResults.txt and MapleResults.txt store analogous data for results of running groebner
basis computations in Macaulay2 over Z/pZ and in Maple over Z, respectively.

To generate these results, you can run grob.sh, ZpGrob.sh, and MapleScript.sh. Parameters
can be changed within these scripts. The scripts first call make to compile main.cpp with
nt_funcs.cpp, llist.cpp, vec.cpp, and common.cpp. The comments in each of these files
contains more information. Calling 'make' and subsequently typing

./enc help

will bring up more options.