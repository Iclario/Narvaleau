Navaleau.exe : main.o interface.o file.o save.o game.o utils.o
	gcc -Wall build/main.o build/interface.o build/file.o build/save.o build/game.o build/utils.o -o out/Navaleau.exe

main.o : src/main.c
	gcc -Wall -c src/main.c -o build/main.o

interface.o : src/interface.c
	gcc -Wall -c src/interface.c -o build/interface.o

file.o : src/file.c
	gcc -Wall -c src/file.c -o build/file.o

save.o : src/save.c
	gcc -Wall -c src/save.c -o build/save.o

game.o : src/game.c
	gcc -Wall -c src/game.c -o build/game.o

utils.o : src/utils.c
	gcc -Wall -c src/utils.c -o build/utils.o

run : Navaleau.exe
	./out/Navaleau.exe
