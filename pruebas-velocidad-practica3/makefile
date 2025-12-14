
COMP=g++
OPT=-std=c++11 -O3

main: Velocidad.o CadenaADN.o ListaCadenasADN.o
	$(COMP) $(OPT) -o main Velocidad.o CadenaADN.o ListaCadenasADN.o

Velocidad.o: Velocidad.cc CadenaADN.h
	$(COMP) $(OPT) -c  Velocidad.cc

CadenaADN.o: CadenaADN.cc CadenaADN.h
	$(COMP) $(OPT) -c CadenaADN.cc

ListaCadenasADN.o: ListaCadenasADN.cc ListaCadenasADN.h CadenaADN.h
	$(COMP) $(OPT) -c ListaCadenasADN.cc


clean:
	rm *.o main
