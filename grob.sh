#
# read file from first input and write singular and M2 results
# the first input is the singular file to be read
# the second is the M2 file to be read
#


make
for ((i=3;i<=5;i+=1));do             # degree of f,g
	for ((j=3;j<=10;j+=1));do        # log-size of the coefficients of f,g
		for ((k=2;k<=10;k+=1));do    # number of polynomials fed to the gb function
			for ((l=0;l<5;l++));do   # five values to get a decent average
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