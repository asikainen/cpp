#ifndef defs_h
#define defs_h

// Shorthand type defitions
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed char byte;
typedef unsigned char ubyte;

// Switch for choosing the central simulation cell
//#define SIMULATION_CELL_CENTER_AT_ZERO

// Definitions
#ifndef EPS
#define EPS 1.0E-9
#endif

#ifndef MAXIMUM_NUMBER_OF_PARTICLES
#define MAXIMUM_NUMBER_OF_PARTICLES 12000
#endif

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 128
#endif

#ifndef MAX_VALUE_LENGTH
#define MAX_VALUE_LENGTH 32
#endif

#ifndef NUMBER_OF_BINS
#define NUMBER_OF_BINS 32
#endif

#ifndef V_MAX
#define V_MAX 1.0
#endif

#ifndef RDF_LEN
#define RDF_LEN 100
#endif

#ifndef MIN_SYSTEM_SIZE
#define MIN_SYSTEM_SIZE 5
#endif

// Switches for printing during debugging
//#define DBG_PRINTING // print when major routines are entered
//#define DBG_PRINTING_FULL // print coordinates, verlet list etc
//#define PRINT_PE_VALUES
//#define PRINT_T_VALUES

#endif
