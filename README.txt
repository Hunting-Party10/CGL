------------
For Windows|
------------
Add glut.h (glee.h, glew.h, etc.) to the MinGW include folder (e.g., C:\MinGW\Include\GL)
Add glut32.dll to Your Source code folder (or your executable's folder)
Add glut32.lib (glee.lib, glew.lib, etc.) to your source code folder

gcc -o MyProg.exe -Wall MyProg.c glut32.lib -lopengl32 -lglu32
