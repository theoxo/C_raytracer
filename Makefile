CC = gcc
CFLAGS = -std=gnu99 -lm
SRCS = Main.c RGB.c LightPhysics.c PPM.c Vector3D.c QuadraticSolution.c
OBJS = Main.o RGB.o LightPhysics.o PPM.o Vector3D.o QuadraticSolution.o

main.exe : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main.exe

%.o : %.c
	$(CC) $(CFLAGS) -c $<
