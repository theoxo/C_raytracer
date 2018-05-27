# C_raytracer

## **UNDER CONSTRUCTION**

Very basic raytracer built in C.
Kind of put on ice right now.

This project is mostly an excuse for me to play around in C, lately specifically regarding concurrency and speed --- hence why the features implemented may seem a bit illogical (ie. multithreading before proper generalized lighting).

Super simple single-source lighting and basic shadows working, only spheres are supported far as shapes go. 

Last seen speeds per branch (1024x1024, 3 spheres, i.e. what is currently defined in the source files):
| master | uglybutfast |
|:------:|:-----------:|
| 0.63s  | 0.48s       |



Note image is heavily jpg'd.

![image showing two spheres floating in front of a larger one in the background](https://raw.githubusercontent.com/theoxo/C_raytracer/master/media/image.jpg)
