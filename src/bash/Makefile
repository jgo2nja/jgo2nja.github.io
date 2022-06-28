# James O'Connell jgo2nja
# Last Updated: 01 March 2022

CXX = clang++ $(CXXFLAGS)

CXXFLAGS = -fsanitize=address -fno-omit-frame-pointer -Wall -g

EXECUTABLES = AVLNode.o AVLTree.o AVLPathTest.o

a.out: $(EXECUTABLES)
	$(CXX) $(EXECUTABLES) -o a.out

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

AVLNode.o: AVLNode.cpp AVLNode.h
AVLPathTest.o: AVLPathTest.cpp AVLTree.h AVLNode.h
AVLTree.o: AVLTree.cpp AVLNode.h AVLTree.h
