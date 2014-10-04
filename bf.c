
// bf.c

#include <stdio.h>

#define PROGLEN 10000
#define BUFSIZE 3000

char buffer[BUFSIZE];
char *bufp;

// We're implementing some functions that are in <string.h>
// to reduce program size
int findLoopEnd (char *prog);
void readfile (FILE *fp, char *c);
void copy (char *dst, char *src, int len);
void substring (char *dst, char *src, int beg, int end);
void parse (char *prog);

// Read a file from top to bottom, including whitespace
void readfile (FILE *fp, char *c)
{
    while (fscanf(fp, "%c", c) == 1) c++;
}

// Find the end of a brainf**k loop, namely the ']' character
int findLoopEnd (char *prog)
{
    for (int i = 0; prog[i] != '\0'; i++) {
        if (prog[i] == '[') {
            i = findLoopEnd(prog + i + 1) + i + 1;
            continue;
        }

        if (prog[i] == ']') return i;
    }

    return -1;
}

// This is basically memcpy
void copy (char *dst, char *src, int len)
{
    for (int i = 0; (i < len) && src[i]; i++)
        dst[i] = src[i];
}

// Get a substring from 'beg' to 'end' in string 'src'
void substring (char *dst, char *src, int beg, int end)
{
    int len = end - beg;
    copy(dst, src + beg, len);
    dst[len] = '\0';
}

// Parse and run a brainf**k program
void parse (char *prog)
{
    for (int i = 0; prog[i] != '\0'; i++) {
        if (prog[i] == '>') bufp++;
        if (prog[i] == '<') bufp--;
        if (prog[i] == '+') (*bufp)++;
        if (prog[i] == '-') (*bufp)--;
        if (prog[i] == '.') putchar(*bufp);
        if (prog[i] == ',') *bufp = getchar();

        if (prog[i] == '[') {
            char subprog[PROGLEN];
            int loopEnd = findLoopEnd(prog + i + 1);
            substring(subprog, prog, i + 1, loopEnd + i + 1);

            while(*bufp != 0) parse(subprog);

            i += findLoopEnd(prog + i + 1);
        }
    }
}

int main (int argc, char const *argv[])
{
    bufp = buffer;

    char program[PROGLEN];

    FILE *progfile = fopen(argv[1], "r");
    readfile(progfile, program);
    fclose(progfile);

    parse(program);

    return 0;
}
