# Ben LeVeque
# 2013
# MapleScript.sh

# This script loops through values of different parameters for Grobner basis
# computation over Z, including the degree of the polynomials f and g
# (the secret polynomials in our multivariate encryption scheme -- note that
# the degree of encryptions will be roughly twice as large as deg(f), deg(g)),
# the base-2 log of the size of the coefficients of f and g, and the number of
# encryptions of zero we send into the Grobner basis function fgb_gbasis in Maple.
# This function is part of the FGb package, written by Jean-Charles Faugere.

# The script first calls make to compile the latest version of the C++ implementation
# of our encryption schemes (we just need the methods to create polynomials). Then, we
# loop as mentioned above, and within each loop, we call
#    ./enc grob $i $j $k
# to generate encryptions of zero using the specified parameters. We then create a file
# ./MapleParams.txt, to which we save said parameters for use by Maple. Then, we
# write a Maple script to a file (MapleTest.txt). The script uses the encryptions of
# zero to create a list (polylist) of polynomials, and then times a call to
#    fgb_gbasis([polylist],[x, y])
# Then the parameters and runtime are saved to the file MapleResults.txt. Finally,
# Maple is called with MapleTest.txt as an argument.


make
for ((i=10;i<=20;i+=2));do             # degree of f,g
	for ((j=20;j<=60;j+=10));do        # log-size of the coefficients of f,g
		for ((k=10;k<=100;k+=30));do   # number of polynomials fed to the fgb_gbasis function
			for ((l=1;l<=5;l++));do    # five iterations to get a decent average
				echo degree=$i, log-size=$j, numpolys=$k, iteration=$l
				./enc grob $i $j $k
				echo $i > ./MapleParams.txt
				((sizecoeffs=2**j))
				echo $sizecoeffs >> ./MapleParams.txt
				echo $k >> ./MapleParams.txt
				echo 'with(fgbrs):
				polysfile:="./Polys.txt":
				fopen(polysfile,READ,TEXT):
				polylist:=parse(readline(polysfile)):
				fclose(polysfile):
				t1:=time(): a:=fgb_gbasis([polylist],[x, y]): t2:=time():
				T:=t2-t1;
				resultsfile:="./MapleResults.txt":
				fopen(resultsfile,APPEND,TEXT):
				paramsfile:="./MapleParams.txt":
				fopen(paramsfile,READ,TEXT):
				fprintf(resultsfile,"%s|%s|%s|%f|\n",readline(paramsfile),readline(paramsfile),readline(paramsfile),T):
				fclose(paramsfile):
				fclose(resultsfile):' > MapleTest.txt
				maple -q MapleTest.txt
				# sleep 1
				echo ""
			done
		done
	done
done
echo ""
echo ""
echo ""
echo 'copy MapleResults.txt to backup file! run ./MapleCpres.sh'
echo ""