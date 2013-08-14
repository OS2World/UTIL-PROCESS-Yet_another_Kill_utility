#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#define INCL_DOS
#define INCL_ERRORS
#define INCL_DOSPROCESS
#define INCL_DOSEXCEPTIONS
#include <os2.h>

#define SIGKILL     9


int main(int argc, char **argv)
{
  int x, retval = 0, signal = SIGTERM;
  ULONG action, plen;
  USHORT param;
  HFILE hdevice;
  APIRET rc;
  PID pid;

  if(argc == 1)
  {
    printf("Syntax:  kill [-l] [-signal] PID's\n\n"
      "         where PID's are in C format (octal/decimal/hexadecimal).\n\n"
      "         Use \"kill -l\" to list available signals.\n");
    return 0;
  }

  if((rc = DosOpen((PSZ) "/dev/fastio$", (PHFILE) &hdevice, (PULONG) &action,
    0L, FILE_SYSTEM, FILE_OPEN, OPEN_SHARE_DENYNONE | OPEN_FLAGS_NOINHERIT |
    OPEN_ACCESS_READONLY, (ULONG) 0L)))
    hdevice = NULL;

  for(x = 1; x < argc; x++)
    switch(*argv[x])
    {
      case '-':
        if(!strcmp(argv[x], "-l"))
        {
          printf("Available signals:\n"
            "         4 (TERM)  - Software termination (default).\n"
            "         6 (INT)   - Interrupt (Ctrl-C).\n");
          if(hdevice)
            printf("         9 (KILL)  - Kill (via xf86sup.sys, "
              "/dev/fastio$).\n");
          printf("        10 (BREAK) - Break (Ctrl-Break).\n");
          break;
        }
        else if((!strcmp(argv[x], "-9")) || (!strcmp(argv[x], "-KILL")))
        {
          if(hdevice)
            signal = SIGKILL;
          else
          {
            printf("Error:  SIGKILL not available, please install "
              "xf86sup.sys.\n");
            retval = (int) rc;
          }
          break;
        }
        else if((!strcmp(argv[x], "-4")) || (!strcmp(argv[x], "-TERM")))
        {
          signal = SIGTERM;
          break;
        }
        else if((!strcmp(argv[x], "-6")) || (!strcmp(argv[x], "-INT")))
        {
          signal = SIGINT;
          break;
        }
        else if((!strcmp(argv[x], "-10")) || (!strcmp(argv[x], "-BREAK")))
        {
          signal = SIGBREAK;
          break;
        }

      default:
        printf("Error:  Unrecognized argument \"%s\".\n", argv[x]);
        rc = -1;
        x = argc;
        break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        pid = (PID) strtol(argv[x], NULL, 0);
        if((!pid) || (pid > 32767))
          printf("Error:  Invalid process ID %s.\n", argv[x]);
        else
        {
          switch(signal)
          {
            case SIGKILL:
              param = (USHORT) pid;
              if((retval = (int) (rc = DosDevIOCtl(hdevice, 0x76L, 0x65L,
                (PULONG*) &param, sizeof(USHORT), &plen, NULL, 0, NULL))))
              {
                if(retval == 87)
                  printf("Error:  Invalid process ID %s.\n", argv[x]);
                else
                  printf("Error:  fastio$ driver error on process %s, "
                    "code %d.\n", argv[1], retval);
              }
              else
                printf("Process %s killed successfully.\n", argv[x]);
              break;
            case SIGTERM:
              if((retval = (int) (rc = DosKillProcess(DKP_PROCESS, pid))))
              {
                if(retval == 303)
                  printf("Error:  Invalid process ID %s.\n", argv[x]);
                else if(retval == 162)
                  printf("Error:  Signal already pending on process %s "
                    "(signal handler hung?).\n", argv[x]);
                else
                  printf("Error:  DosKillProcess() failed on process %s, "
                    "code %d.\n", argv[x], retval);
              }
              else
                printf("Process %s terminated successfully.\n", argv[x]);
              break;
            case SIGINT:
              if((retval = (int) (rc = DosSendSignalException(pid,
                XCPT_SIGNAL_INTR))))
              {
                if(retval == 303)
                  printf("Error:  Invalid process ID %s.\n", argv[x]);
                else if(retval == 162)
                  printf("Error:  Signal already pending on process %s "
                    "(signal handler hung?).\n", argv[x]);
                else
                  printf("Error:  DosSendSignalException() failed on "
                    "process %s, code %d.\n", argv[x], retval);
              }
              else
                printf("Process %s interrupted successfully.\n", argv[x]);
              break;
            case SIGBREAK:
              if((retval = (int) (rc = DosSendSignalException(pid,
                XCPT_SIGNAL_BREAK))))
              {
                if(retval == 303)
                  printf("Error:  Invalid process ID %s.\n", argv[x]);
                else if(retval == 162)
                  printf("Error:  Signal already pending on process %s "
                    "(signal handler hung?).\n", argv[x]);
                else
                  printf("Error:  DosSendSignalException() failed on "
                    "process %s, code %d.\n", argv[x], retval);
              }
              else
                printf("Process %s broken successfully.\n", argv[x]);
              break;
          }
        }
        break;
    }

  if(hdevice)
    DosClose(hdevice);

  return retval;
}

