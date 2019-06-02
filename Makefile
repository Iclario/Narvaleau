Navaleau.exe : main.o interfaceText.o interfaceGraphic.o file.o save.o game.o utils.o
	gcc `pkg-config --cflags gtk+-3.0` -Wall build/main.o build/interfaceText.o build/interfaceGraphic.o build/file.o build/save.o build/game.o build/utils.o -o out/Navaleau.exe `pkg-config --libs gtk+-3.0`

main.o : src/main.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/main.c -o build/main.o `pkg-config --libs gtk+-3.0`

interfaceText.o : src/interfaceText.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/interfaceText.c -o build/interfaceText.o `pkg-config --libs gtk+-3.0`

interfaceGraphic.o : src/interfaceGraphic.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/interfaceGraphic.c -o build/interfaceGraphic.o `pkg-config --libs gtk+-3.0`

file.o : src/file.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/file.c -o build/file.o `pkg-config --libs gtk+-3.0`

save.o : src/save.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/save.c -o build/save.o `pkg-config --libs gtk+-3.0`

game.o : src/game.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/game.c -o build/game.o `pkg-config --libs gtk+-3.0`

utils.o : src/utils.c
	gcc `pkg-config --cflags gtk+-3.0` -Wall -c src/utils.c -o build/utils.o `pkg-config --libs gtk+-3.0`

run : Navaleau.exe
	./out/Navaleau.exe
