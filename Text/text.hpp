/***
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef text_hpp
#define text_hpp

// Definitions
#define NAME_SIZE 64
#define BUFFER_SIZE 1024
#define WORD_SIZE 32
#define MAX_COLS 64

// Prototypes
void WriteFile(char *, char *);
void ReadFile(char *, char *);
void Error(char * = "(default)");

int EditFile(char *, char *, const int = MAX_COLS);

#endif
