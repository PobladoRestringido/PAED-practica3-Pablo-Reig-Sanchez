cd old-tests/1st-practice-tests/
pwd
cp {../../CadenaADN.h,../../CadenaADN.cc} .
g++ -o testCadenaADN test_CadenaADN.cc CadenaADN.cc
valgrind ./testCadenaADN
rm testCadenaADN CadenaADN.h CadenaADN.cc

cd ../2nd-practice-tests
cp {../../CadenaADN.h,../../CadenaADN.cc,../../ListaCadenasADN.cc,../../ListaCadenasADN.h} .
make
valgrind ./main
make clean
rm CadenaADN.h CadenaADN.cc ListaCadenasADN.cc ListaCadenasADN.h
cd ../../