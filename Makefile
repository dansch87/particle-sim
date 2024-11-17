particle-sim: .\src\main.c .\src\quadtree.c .\src\arena.c
	gcc -o .\build\particle-sim .\src\main.c .\src\particle.c .\src\quadtree.c .\src\arena.c -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	.\build\particle-sim.exe