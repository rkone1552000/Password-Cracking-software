exe.out: binaries/dictionary.o binaries/MultiThreadedBruteForce.o binaries/Main.o
	g++ binaries/dictionary.o binaries/MultiThreadedBruteForce.o binaries/Main.o -pthread -o exe.out -ggdb

binaries/dictionary.o: headers/dictionary.cpp
	g++ -c headers/dictionary.cpp -pthread -o binaries/dictionary.o -ggdb

binaries/MultiThreadedBruteForce.o: headers/MultiThreadedBruteForce.cpp
	g++ -c headers/MultiThreadedBruteForce.cpp -pthread -o binaries/MultiThreadedBruteForce.o -ggdb

binaries/Main.o:Main_v2.cpp
	g++ -c Main_v2.cpp -o binaries/Main.o -ggdb

clean: 
	rm binaries/*.o


