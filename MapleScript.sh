#
# read file from first input and write singular and M2 results
# the first input is the singular file to be read
# the second is the M2 file to be read
#


make
for ((i=10;i<=20;i+=2));do             # degree of f,g
	for ((j=20;j<=60;j+=10));do        # log-size of the coefficients of f,g
		for ((k=10;k<=100;k+=30));do    # number of polynomials fed to the gb function
			for ((l=1;l<=5;l++));do   # five values to get a decent average
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