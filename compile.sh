mkdir build;
gcc src/util/vector2.c -o build/vector2.o -c;
gcc src/cloth.c -o build/cloth.o -c;
gcc src/main.c -o build/main.o -c;

gcc -o program build/main.o build/cloth.o build/vector2.o -lm -lcsfml-graphics -lcsfml-window -lcsfml-system -pthread ; 