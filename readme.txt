KILL 1.00 by Viet-Tam Luu
=========================

Yet another kill utility... with a bonus!  (Read on...)



Description
===========

KILL is a command-line process killer utility for OS/2 Warp (and possibly
2.1x).  It includes support for Holger Veit's xf86sup.sys, which (when
used in conjunction with OS/2 Warp FixPak 17 (or later?)) implements a
"HARD KILL" method.

xf86sys is included, in the FX0002.ZIP archive.

KILL is intended for OS/2 power users.  Familiarity with the internals of
the OS/2 system and process management are assumed.

KILL has command-line arguments very similar to the standard Unix kill
command, i.e. "kill [-l] [-signal] PID's".  For example, "kill 130" sends
a SIGTERM to process 130, and "kill -KILL 0x25" uses xf86sup.sys to "hard-
kill" process 0x25 (37).  You can get available signals with "kill -l";
KILL supports OS/2 signals SIGTERM, SIGBREAK, SIGINT, and SIGKILL (the
latter simulated using xf86sup.sys).

xf86sup.sys is not required for operation.  If it is not installed,
SIGKILL ("kill -KILL" or equivalently "kill -9") will not be supported.


Installation
============

0.  Unzip the kill.zip archive to a temporary directory.

1.  Copy/move kill.exe to a directory in your path.

2.  If you don't have xf86sup.sys installed, unzip FX0002.zip, copy/move
    xf86sup.sys to your \os2\boot directory, and add the line
    "DEVICE=\os2\boot\xf86sup.sys" to your CONFIG.SYS file.

3.  If you don't want to tinker with the kill and xf86sup source files,
    delete all files unarchived that you haven't copied/moved to another
    directory (except possible this readme file!).

4.  If you installed xf86sup.sys in step 2, reboot OS/2.

5.  Happy killing!  :-)
    You can try killing non-killable processes using the sample PIG.EXE
    program included in FX0002.zip.


Disclaimer
==========

KILL is provided "as is" and the author makes no claims as to its
suitability for any purpose.  The author cannot be held responsible for
any damages consequential to the use of KILL.

(Bla, bla, bla...  You get the idea.)


Known Bugs and Problems
=======================

SIGINT and SIGBREAK, though they would appear to be implemented correctly
(see the source code, kill.c) don't work on my system (Warp Connect,
FixPak 17), returning SYS0205 (no signal handlers) errors regardless of
the PID I specify.

I whipped it up in a night.  Yeah, there might be bugs...


Distribution
============

KILL is public domain software.  The author forfeits all his copyrights
to the code.  Clone it, modify it, do whatever you want with it, but you
and you only are responsible for whatever damage you incur in doing so.
:-)

If you're feeling nice, give me some acknowledgement, at least...


Contacting the Author
=====================

The author, Viet-Tam Luu, can be reached via Internet E-mail at
vtluu@uwaterloo.ca .  His WWW home page can be found at URL
http://www.csclub.uwaterloo.ca/u/vtluu/ .

