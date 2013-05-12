# Ben LeVeque
# 2013
# grob.sh

# This script loops through values of different parameters for Grobner basis
# computation over Z, including the degree of the polynomials f and g
# (the secret polynomials in our multivariate encryption scheme -- note that
# the degree of encryptions will be roughly twice as large as deg(f), deg(g)),
# the base-2 log of the size of the coefficients of f and g, and the number of
# encryptions of zero we send into the Grobner basis function gb in Macaulay2.

# The script first calls make to compile the latest version of the C++ implementation
# of our encryption schemes (we just need the methods to create polynomials). Then, we
# loop as mentioned above, and within each loop, we call
#    ./enc grob $i $j $k
# to generate encryptions of zero using the specified parameters. We then create a file
# ./M2Params.txt, to which we save said parameters for use by Macaulay2. Then, we
# write a Macaulay2 script to a file (M2test.txt). The script uses the encryptions of
# zero to create an ideal I in Z[x,y] and then times a call to gb(I). The generators
# of the basis are saved for reference (just of the most recent iteration, since the
# generators can take up a lot of space). Then the parameters and runtime are saved
# to the file results.txt. Finally, a seemingly nonsensical 1+ ends the script. The
# reason for this line is to force M2 to quit (M2 is called in the line below with
# the --stop flag, which causes it to exit on errors) so we can continue to the next
# iteration.


make
for ((i=6;i<=6;i+=1));do             # degree of f,g
	for ((j=10;j<=10;j+=1));do        # log-size of the coefficients of f,g
		for ((k=4;k<=4;k+=1));do    # number of polynomials fed to the gb function
			for ((l=0;l<5;l++));do   # five iterations to get a decent average
				echo degree=$i, log-size=$j, numpolys=$k, iteration=$l
				./enc grob $i $j $k
				echo totalDegree=$i > ./M2Params.txt
				((sizecoeffs=2**j))
				echo sizeCoeffs=$sizecoeffs >> ./M2Params.txt
				echo numPolysGiven=$k >> ./M2Params.txt
				echo 'R=ZZ[x,y]
				I=ideal(value(get("./Polys.txt")))
				t1=cpuTime();a=gb(I);t2=cpuTime();
				g="./M2Gens.txt"
				g << gens(a) << endl
				T=(t2-t1)
				value(get("./M2Params.txt"))
				g << totalDegree << "|" << sizeCoeffs << "|" <<  numPolysGiven << "|" << T << "|" << endl << endl << close
				f="./results.txt"
				f << get(f)
				f << totalDegree << "|" << sizeCoeffs << "|" <<  numPolysGiven << "|" << T << "|" << endl << close
				1+' > M2test.txt
				M2 --stop --no-backtrace M2test.txt
				# sleep 1
				echo ""
			done
		done
	done
done
echo ""
echo ""
echo ""
echo 'copy results.txt to backup file! run ./cpres.sh'
echo ""