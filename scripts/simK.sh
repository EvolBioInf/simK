./simK -l 1000 -s 13 > tmp.out
DIFF=$(diff tmp.out ../data/test.fasta)
if [ "$DIFF" == "" ] 
then
    printf "Test(simK)\tpass\n"
else
    printf "Test(simK)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
