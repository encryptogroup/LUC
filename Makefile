CC = g++
CFLAGS = -g -Wall -std=c++17
GAMMA = src/gamma/
UC = src/uc/2way/
UTIL = src/util/

UC: UC.o gamma.o valiant.o valiantBase.o valiantMerged.o liu.o parseBench.o utility.o 
	$(CC) $(CFLAGS) -o UC UC.o gamma.o valiant.o valiantBase.o valiantMerged.o liu.o parseBench.o utility.o
	
UC.o: src/UC.cpp $(GAMMA)gamma.h $(UC)valiant.h $(UC)valiantBase.h $(UC)valiantMerged.h $(UC)liu.h $(UTIL)utility.h $(UTIL)parseBench.h
	$(CC) $(CFLAGS) -c src/UC.cpp

gamma.o: $(GAMMA)gamma.cpp $(GAMMA)gamma.h
	$(CC) $(CFLAGS) -c $(GAMMA)gamma.cpp


valiant.o: $(UC)valiant.cpp $(UC)valiant.h
	$(CC) $(CFLAGS) -c $(UC)valiant.cpp

valiantBase.o: $(UC)valiantBase.cpp $(UC)valiantBase.h
	$(CC) $(CFLAGS) -c $(UC)valiantBase.cpp

valiantMerged.o: $(UC)valiantMerged.cpp $(UC)valiantMerged.h
	$(CC) $(CFLAGS) -c $(UC)valiantMerged.cpp

liu.o: $(UC)liu.cpp $(UC)liu.h
	$(CC) $(CFLAGS) -c $(UC)liu.cpp

parseBench.o: $(UTIL)parseBench.cpp $(UTIL)parseBench.h
	$(CC) $(CFLAGS) -c $(UTIL)parseBench.cpp

utility.o: $(UTIL)utility.cpp $(UTIL)utility.h
	$(CC) $(CFLAGS) -c $(UTIL)utility.cpp


clean:
	rm *.o
