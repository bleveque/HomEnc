# 
# read file from first input and write singular and M2 results
# the first input is the singular file to be read
# the second is the M2 file to be read
# we use the primes 11 (smallest prime greater than 10), 101 (smallest prime greater than 100),
# 1009 (smallest prime greater than 1000), and 32749 (largest prime handled by Macaulay2 for a
# finite field Z/p, according to the documentation at
# http://www.math.uiuc.edu/Macaulay2/doc/Macaulay2-1.4/share/doc/Macaulay2/BeginningMacaulay2/html/)
# 

make
for ((i=7;i<=7;i+=1));do                  # degree of f,g
	for ((j=16;j<=16;j+=4));do             # log-size of the coefficients of f,g -- shouldn't matter much here, so just 2^16 > 32749
		for ((k=2;k<=20;k+=8));do          # number of polynomials fed to the gb function
			for p in 11 101 1009 32749;do  # primes we use
				for ((l=0;l<5;l++));do     # five values to get a decent average
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