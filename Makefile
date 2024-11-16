particle-sim: .\src\main.c 
	gcc -o .\build\particle-sim .\src\main.c .\src\particle.c -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	.\build\particle-sim.exe