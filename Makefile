CC = gcc
CFLAGS = -std=c11 -lm -O3 -pthread
SRCS = source/Main.c source/RGB.c source/LightPhysics.c source/Vector3D.c source/QuadraticSolution.c source/Sphere.c souce/SpheresNode.c
OBJS = Main.o RGB.o LightPhysics.o Vector3D.o QuadraticSolution.o Sphere.o SpheresNode.o

main.exe : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main.exe

%.o : source/%.c
	$(CC) $(CFLAGS) -c $<

debug : CFLAGS += -g -pg
debug : main.exe

.PHONY : clean
clean :
	-rm $(OBJS)
