# Ben LeVeque
# 2013
# ZpGrob.sh

# This script loops through values of different parameters for Grobner basis
# computation over Z/pZ, including the degree of the polynomials f and g
# (the secret polynomials in our multivariate encryption scheme -- note that
# the degree of encryptions will be roughly twice as large as deg(f), deg(g)),
# the base-2 log of the size of the coefficients of f and g, the number of
# encryptions of zero we send into the Grobner basis function gb in Macaulay2,
# and a collection of primes p. In this case, we use the primes 11 (smallest
# prime greater than 10), 101 (smallest prime greater than 100), 1009 (smallest
# prime greater than 1000), and 32749 (largest prime handled by Macaulay2 for a
# finite field Z/p, according to the documentation at
# http://www.math.uiuc.edu/Macaulay2/doc/Macaulay2-1.4/share/doc/Macaulay2/BeginningMacaulay2/html/).
# Also, since we are working over a finite field, it should not much matter what the
# size of the coefficients of f and g are, so this parameter probably is not very
# significant.

# The script first calls make to compile the latest version of the C++ implementation
# of our encryption schemes (we just need the methods to create polynomials). Then, we
# loop as mentioned above, and within each loop, we call
#    ./enc grob $i $j $k
# to generate encryptions of zero using the specified parameters. We then create a file
# ./ZpM2Params.txt, to which we save said parameters for use by Macaulay2. Then, we
# write a Macaulay2 script to a file (ZpM2test.txt). The script uses the encryptions of
# zero to create an ideal I in Z/pZ[x,y] and then times a call to gb(I). The generators
# of the basis are saved for reference (just of the most recent iteration, since the
# generators can take up a lot of space). Then the parameters and runtime are saved
# to the file ZpResults.txt. Finally, a seemingly nonsensical 1+ ends the script. The
# reason for this line is to force M2 to quit (M2 is called in the line below with
# the --stop flag, which causes it to exit on errors) so we can continue to the next
# iteration.

make
for ((i=3;i<=10;i+=1));do                  # degree of f,g
	for ((j=16;j<=16;j+=1));do             # log-size of the coefficients of f,g -- shouldn't matter much here, so just 2^16 > 32749
		for ((k=2;k<=10;k+=1));do          # number of polynomials sent to the gb function
			for p in 11 101 1009 32749;do  # primes we use
				for ((l=0;l<5;l++));do     # five iterations with the same parameters above to get a decent average
					echo degree=$i, log-size=$j, numpolys=$k, prime=$p, iteration=$l
					./enc grob $i $j $k
					echo totalDegree=$i > ./ZpM2Params.txt
					((sizecoeffs=2**j))
					echo sizeCoeffs=$sizecoeffs >> ./ZpM2Params.txt
					echo numPolysGiven=$k >> ./ZpM2Params.txt
					echo p=$p >> ./ZpM2Params.txt
					echo 'value(get("./ZpM2Params.txt"))
					R=ZZ/p[x,y]
					I=ideal(value(get("./Polys.txt")))
					t1=cpuTime();a=gb(I);t2=cpuTime();
					g="./ZpM2Gens.txt"
					g << gens(a) << endl
					T=(t2-t1)
					g << totalDegree << "|" << sizeCoeffs << "|" <<  numPolysGiven << "|" << p << "|" << T << "|" << endl << endl << close
					f="./ZpResults.txt"
					f << get(f)
					f << totalDegree << "|" << sizeCoeffs << "|" <<  numPolysGiven << "|" << p << "|" << T << "|" << endl << close
					1+' > ZpM2test.txt
					M2 --stop --no-backtrace ZpM2test.txt
					# sleep 1
					echo ""
				done
			done
		done
	done
done
echo ""
echo ""
echo ""
echo 'copy ZpResults.txt to backup file! run ./ZpCpres.sh'
echo ""