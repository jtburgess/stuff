/*
 *	mode file
 *	writes to std. out chars for chmod
    cc mode.c
 */

#include <sys/types.h>
#include <sys/stat.h>

main(argc,argv)
int argc; char **argv;
{
	struct stat sb;
	if (argc != 2) {
		printf("usage: mode file\n");
		exit(1);
	}
	if (stat(argv[1], &sb) == -1) {
		printf("%s: cannot open\n",argv[1]);
		exit(1);
	}
	printf("%o\n", sb.st_mode & 07777);
	exit(0);
}
