Navaleau.o : build/main.o build/interface.o build/file.o build/save.o build/game.o
	gcc -ansi -Wall build/main.o build/interface.o build/file.o build/save.o build/game.o -o out/Navaleau.exe

build/main.o : src/main.c
	gcc -ansi -Wall -c src/main.c -o build/main.o

build/interface.o : src/interface.c
	gcc -ansi -Wall -c src/interface.c -o build/interface.o

build/file.o : src/file.c
	gcc -ansi -Wall -c src/file.c -o build/file.o

build/save.o : src/save.c
	gcc -ansi -Wall -c src/save.c -o build/save.o

build/game.o : src/game.c
	gcc -ansi -Wall -c src/game.c -o build/game.o

run : Navaleau.o
	./out/Navaleau.exe
