//Andrew Gair (GAIRAD)
//csci422 Project

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "../hdr/file_management.h"

using namespace std;

int it = 0;

//--Need to know what type of graph this is.
//--  Will be directed or undirected, which is represented with a D or a U
char getGraphType(char *fileName){
  ifstream fileH; //--file handle
  char c; //--the first char in the file
  
  fileH.open(fileName);
  if(!fileH.is_open()){
    cout << "could not open file: " << fileName << endl;
    return 'E'; //--signal an error to main
  }
  
  fileH >> c;
  return c;
}

//--Need to know how big to make dynamic array, and so this
//--  function just grabs the first value from the file
int getTotalElements(char *fileName){
  ifstream fileH; //--file handle
  int n; //--total count of elements in file
  char throwAway;
  
  fileH.open(fileName);
  if(!fileH.is_open()){
    cout << "could not open file: " << fileName << endl;
    return -1; //--signal an error to main
  }
  
  fileH >> throwAway; //--throw away first result, its a CHAR anyways
  fileH >> n;
  return n; //--return the char 'n' casted to integer type
}

//--function that reads values from the file into the previously
//--  created dynamic array. Therefore it takes such an array
//--  as a parameter (passed by reference of course).
int U_readFromFile(char *fn, U_node *&nodeArray) {
  ifstream fileH; //--file handle
  int n, k, r, j; //--element-count, value-from-file, another-incrementer
  int inc = 0;    //--incrementer variable
  char throwAway;

  fileH.open(fn); //--attempt to open the given file
  if (!fileH.is_open()) { //--if the filehandle failed to be created
    cout << "File not openable." << endl;
    return -1; //--signal an error to main
  }

  fileH >> throwAway; //--throw away first result, its a CHAR anyways
  fileH >> n; //--read total elements in input file
  
  for(int i=0; i < n; i++) { //--go through each row of the input file
    fileH >> k; //--read values into integer type k
    nodeArray[i].ID = k;
    inc = 0;    //--reset increment variable
    do {        //--go through contents of each row
        fileH >> k;  //--read the value from file into k
        if(k == n){  //--do not want to read the 'end-of-line' number
          break;
        }
        nodeArray[i].neighbours.push_back(k); //--start filling out 'neighbours' array with k values
        nodeArray[i].degree++;
        inc++;
    } while(k != n); //--while read value (which is k) doesn't equal n, run the looop
  }

  fileH.close(); //--close the file
  return 1;
}


int D_readFromFile(char *fn, D_node *&nodeArray) {
  ifstream fileH; //--file handle
  int n, k, r, j; //--element-count, value-from-file, another-incrementer
  int inc = 0;    //--incrementer variable
  char throwAway;

  fileH.open(fn); //--attempt to open the given file
  if (!fileH.is_open()) { //--if the filehandle failed to be created
    cout << "File not openable." << endl;
    return -1; //--signal an error to main
  }

  fileH >> throwAway; //--throw away first result, its a CHAR anyways
  fileH >> n; //--read total elements in input file
  
  for(int i=0; i < n; i++) { //--go through each row of the input file
    fileH >> k; //--read values into integer type k
    nodeArray[i].ID = k;
    inc = 0;    //--reset increment variable
    do {        //--go through contents of each row
        fileH >> k;  //--read the value from file into k
        if(k == n){  //--do not want to read the 'end-of-line' number
          break;
        }
        nodeArray[k].in_degree++;
        nodeArray[k].pointsToMe.push_back(i); //--start filling out 'neighbours' array with k values
        nodeArray[i].neighbours.push_back(k); //--start filling out 'neighbours' array with k values
        nodeArray[i].out_degree++;
        inc++;
    } while(k != n); //--while read value (which is k) doesn't equal n, run the looop
  }

  fileH.close(); //--close the file
  return 1;
}
