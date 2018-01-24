CC = gcc
CFLAGS = -std=gnu99 -lm
SRCS = source/Main.c source/RGB.c source/LightPhysics.c source/PPM.c source/Vector3D.c source/QuadraticSolution.c
OBJS = bin/Main.o bin/RGB.o bin/LightPhysics.o bin/PPM.o bin/Vector3D.o bin/QuadraticSolution.o

main.exe : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o bin/main.exe

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	-rm edit $(OBJS)
