#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "text.hpp"

// Main
int main(int argc, char *argv[])
{
  // Check arguments
  if (argc < 3)
    {
      cout << "# usage: text.exe infile outfile [maxcols]" << endl;
      return 1;
    }
  // Pick arguments
  char inFile[NAME_SIZE], outFile[NAME_SIZE];
  strcpy(inFile,argv[1]);
  strcpy(outFile,argv[2]);
  int maxCols = MAX_COLS;
  if (argc == 4)
    maxCols = atoi(argv[3]);
    
  // Testing
  EditFile(inFile,outFile,maxCols);

  // Done
  return 0;
}

// Write a text file
void WriteFile(char *fileName, char *txt)
{
  // File for data
  ofstream fout(fileName);
  if (fout)
    {
      // Printing info on the screen
      cout << "# Writing file " << fileName << "... ";

      // Write
      fout << txt << endl;

      // Close the output file
      fout.close();

      // Printing
      cout << "ok." << endl;
    }
  else
    cout << "# Error in writing file " << fileName << endl;

}

// Read a text file
void ReadFile(char *fileName, char *txt)
{
  // File for data
  ifstream fin(fileName);
  if (fin)
    {
      // Printing info on the screen
      cout << "# Reading file " << fileName << "... ";

      // Read
      fin.getline(txt,BUFFER_SIZE);

      // Close the output file
      fin.close();
      
      // Printing
      cout << "ok." << endl;
    }
  else
    cout << "# Error in reading file " << fileName << endl;
}

// Edit a text file
int EditFile(char *inFile, char *outFile, const int maxCols)
{
  // Checking
  if (strcmp(inFile,outFile) == 0)
    {
      cout << "# inFile and outFile equal! " << endl;
      return 1;
    }

  // File for data
  ifstream fin(inFile);
  ofstream fout(outFile);

  // Checking
  if (!fin)
    {
      cout << "# Error in opening file " << inFile << endl;
      return 2;
    }
  // Checking
  if (!fout)
    {
      cout << "# Error in opening file " << outFile << endl;
      return 3;
    }

  // Printing info on the screen
  cout << "# Editing file " << inFile << "; output to " << outFile << "... ";

  // char
  char ch;

  // Read until the end of file
  int col = 0;
  while (fin.get(ch))
    {
      // Increment columns
      col++;

      // Check if maxCols is exceeded (words separated by space(s)
      if ( (ch == ' ') && (col > maxCols) )
	{
	  col = 0;
	  fout << endl;
	}
      else
	fout << ch;

      // Set column counter zero if a new line
      if (ch == '\n')
	col = 0;
    }

  // Close the io files
  fin.close();
  fout.close();
      
  // Printing
  cout << "ok." << endl;

  // Done
  return 0;
}

// Error handling
void Error(char errorText[])
{
  printf("# Error :%s\n",errorText);
  exit(1);
}
