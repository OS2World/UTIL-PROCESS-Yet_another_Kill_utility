# This makefile written for IBM VisualAge C++ 3.0

all: kill.exe

kill.exe: kill.c
	icc -Gd- -Wcnd- -O -Oc -B"/OPTFUNC" kill.c

clean:
	del *.obj
