CC = gcc
CFLAGS = -std=gnu99 -lm
SRCS = source/Main.c source/RGB.c source/LightPhysics.c source/PPM.c source/Vector3D.c source/QuadraticSolution.c
OBJS = Main.o RGB.o LightPhysics.o PPM.o Vector3D.o QuadraticSolution.o

main.exe : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main.exe

%.o : source/%.c
	$(CC) $(CFLAGS) -c $<


.PHONY : clean
clean :
	-rm $(OBJS)
