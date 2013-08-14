#define INCL_BASE
#define INCL_DOSEXCEPTIONS
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdio.h>

ULONG sighndlr (PEXCEPTIONREPORTRECORD pERepRec,
		PEXCEPTIONREGISTRATIONRECORD pERegRec,
		PCONTEXTRECORD pCtxRec,
		PVOID p);

int main(int argc,char*argv[])
{
	EXCEPTIONREGISTRATIONRECORD xcpt = { 0, &sighndlr };
	ULONG dummy;
	PTIB ptib;
	PPIB ppib;
	ULONG pid;

	/* make me immortile */
	DosError(FERR_DISABLEEXCEPTION|FERR_DISABLEHARDERR);
	DosSetExceptionHandler(&xcpt);
	
	DosGetInfoBlocks(&ptib,&ppib);
	pid = ppib->pib_ulpid;
	printf("My PID is %d (hex 0x%x), kill me!\n",pid,pid);

	DosEnterMustComplete(&dummy);
	while(1) { DosSleep(1); }
}


ULONG sighndlr (PEXCEPTIONREPORTRECORD pERepRec,
		PEXCEPTIONREGISTRATIONRECORD pERegRec,
		PCONTEXTRECORD pCtxRec,
		PVOID p)
{
	return XCPT_CONTINUE_EXECUTION;
}
