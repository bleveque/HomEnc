#
# read file from first input and write singular and M2 results
# the first input is the singular file to be read
# the second is the M2 file to be read
#

echo 'R=ZZ[x,y]
I=ideal(value(get("/Users/bleveque/UTRA/HomEnc/Polys.txt")))
t1=cpuTime();a=gb(I);t2=cpuTime();
g="/Users/bleveque/UTRA/HomEnc/M2Gens.txt"
g << gens(a) << endl << close
T=(t2-t1)
value(get("/Users/bleveque/UTRA/HomEnc/M2Params.txt"))
f="/Users/bleveque/UTRA/HomEnc/M2Results.txt"
f << get(f)
f << totalDegree << "|" << sizeCoeffs << "|" <<  numPolysGiven << "|" << T << "|" << endl << close
1+' > M2test.txt
M2 --stop --no-backtrace M2test.txt
# 
# polys=`cat /Users/bleveque/UTRA/HomEnc/Polys.txt`
# 
# echo 'ring r=integer,(x,y),dp;ideal I=(' > SingularTest.txt
# echo "$polys" >> SingularTest.txt
# echo ');I;int t=timer;groebner(I);int T=timer-t;string ST=string(T);
# string params=read("/Users/bleveque/UTRA/HomEnc/SingularParams.txt");
# write("/Users/bleveque/UTRA/HomEnc/SingularResults.txt",params+ST+"|");
# quit;' >> SingularTest.txt
# singular SingularTest.txt --ticks-per-sec 1000