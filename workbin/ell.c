/*
 *	ell [-f] [-hx] [-rstring] [-sstring] [file ...]
 *	prints each file like ed's 'l' (list) command.
 *	If no files are given, the standard input is printed.
 *	A file named "-" causes stdin to be printed at that point.
 *	Characters in the string following -r are treated as
 *	regular characters; characters in the string following -s
 *	are treated as special characters.
 *
 *      -h OR -x means HEX output, not octal
 *
 *	build:
 *		cc ell.c -lPW
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>


#define	RESERVE(cnt)	if( fold && (col+cnt>79) ) { *lp++ = '\\'; *lp++ = '\n'; col = 1; }

char	*clist[] = {
	"abcdefghijklmnopqrstuvwxyz",
	"0123456789",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	" !\"#$%&\'()=~|-^\\`{@[_+*};:]<>?,./\n",
	0
};
char	isgraphic[256];
int	fold = 0;
int	hex = 0;

void ell(FILE *fp);
void putexp(unsigned char c);

int main(int argc, char **argv)
{
	char	*cp;	/* character pointer for arg processing */
	char	*np;
	int	i;
	int	j;
	FILE	*fp;
	int	c;

	for( i = 0; clist[i] != 0; i++ )
		for( j = 0; (c = clist[i][j]); j++ )
			isgraphic[c] = c;

	for( i = 1; i < argc && argv[i][0] == '-'; i++ ) {
		switch( argv[i][1] ) {
		case 's':
			for( cp = &argv[i][2]; *cp; cp++ ) {
				isgraphic[ *cp ] = '\0';
			}
			break;
		case 'r':
			for( cp = &argv[i][2]; *cp; cp++ ) {
				isgraphic[ *cp ] = *cp;
			}
			break;
		case 'f':
			fold = 1;
			break;
		case 'x':
		case 'h':
			hex = 1;
			break;
		}
	}
	if ((argc - i) == 0) {
		ell(stdin);
	}else{
		for (j = 1; j < argc; j++) {
			if (strcmp(argv[j],"-") == 0) {
				fp = stdin;
				ell(fp);
			}else{
				fp = fopen(argv[j],"r");
				if (fp != NULL) {
					ell(fp);
					fclose(fp);
				}
			}
		}
	}
	exit(0);
}


void ell(FILE *fp)
{
	register int c;

	while ((c = fgetc(fp)) != EOF)
		putexp(c);
}


char hexchar[] = "0123456789ABCDEF";

void putexp(register unsigned char c)
{
	static	int	col = 1;
	char	line[16];
	register	char	*lp;

	lp = line;
	if( isgraphic[c] ) {
		if( c == '\n' ) {
			*lp++ = c;
			col = 1;
		}else{
			RESERVE(1);
			*lp++ = c;
			col++;
		}
	} else
		switch(c) {
		case '\t':
			RESERVE(2);
			*lp++ = '\\';
			*lp++ = 't';
			col++;
			break;
		case '\b':
			RESERVE(2);
			*lp++ = '\\';
			*lp++ = 'b';
			col++;
			break;
		case '\r':
			RESERVE(2);
			*lp++ = '\\';
			*lp++ = 'r';
			col++;
			break;
		default:
			RESERVE(4);
			if (hex) {
				*lp++ = '\\';
				*lp++ = 'x';
				*lp++ = hexchar[c>>4];
				*lp++ = hexchar[c & 0x0F];
			} else {
				*lp++ = '\\';
				*lp++ = ((c>>6) & 03)+'0';
				*lp++ = ((c>>3) & 07)+'0';
				*lp++ = (c & 07)+'0';
			}
			col += 4;
		}
	*lp++ = '\0';
	for( lp = line; *lp; lp++ )
		putc( *lp, stdout );
}
