./simK > tmp.out
DIFF=$(diff tmp.out ../data/simK.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(simK)\tpass\n"
else
    printf "Test(simK)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
