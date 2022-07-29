# James O'Connell jgo2nja
# Last Updated: 28 July 2022

CXX = clang++ $(CXXFLAGS)

CXXFLAGS = -fsanitize=address -fno-omit-frame-pointer -Wall -g

EXECUTABLES = city.o randGen.o pairing_heap.o mapSolver.o

a.out: $(EXECUTABLES)
	$(CXX) $(EXECUTABLES) -o a.out

.PHONY clean:
	-rm -f *.o *~ a.out

city.o: city.cpp city.h
mapSolver.o: mapSolver.cpp city.h randGen.h pairing_heap.h
pairing_heap.o: pairing_heap.cpp city.h pairing_heap.h
randGen.o: randGen.cpp randGen.h
