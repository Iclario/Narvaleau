Navaleau.exe : main.o interfaceText.o interfaceGraphic.o file.o save.o game.o utils.o
	gcc -Wall build/main.o build/interfaceText.o build/interfaceGraphic.o build/file.o build/save.o build/game.o build/utils.o -lSDL2 -lSDL2_ttf -o out/Navaleau.exe

main.o : src/main.c
	gcc -Wall -c src/main.c -lSDL2 -lSDL2_ttf -o build/main.o

interfaceText.o : src/interfaceText.c
	gcc -Wall -c src/interfaceText.c -lSDL2 -lSDL2_ttf -o build/interfaceText.o

interfaceGraphic.o : src/interfaceGraphic.c
	gcc -Wall -c src/interfaceGraphic.c -lSDL2 -lSDL2_ttf -o build/interfaceGraphic.o

file.o : src/file.c
	gcc -Wall -c src/file.c -lSDL2 -lSDL2_ttf -o build/file.o

save.o : src/save.c
	gcc -Wall -c src/save.c -lSDL2 -lSDL2_ttf -o build/save.o

game.o : src/game.c
	gcc -Wall -c src/game.c -lSDL2 -lSDL2_ttf -o build/game.o

utils.o : src/utils.c
	gcc -Wall -c src/utils.c -lSDL2 -lSDL2_ttf -o build/utils.o

run : Navaleau.exe
	cd out && ./Navaleau.exe
