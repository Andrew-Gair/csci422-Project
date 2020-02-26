//Andrew Gair (GAIRAD)
//csci422 Project

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "../hdr/file_management.h"
#include "../hdr/U_type_functions.h"
#include "../hdr/D_type_functions.h"

void U_resetPaint(int n, U_node* nodeArray); //--outdated
void D_resetPaint(int n, D_node* nodeArray); //--outdated

using namespace std;

//--Each time function needs to check if a node has been marked, will compare it
//--  to the value of this integer.
//--Each function needs to increment this integer before running.
//--No need to reset 'marked' status after each function run.
int mark = 0;
int p_mark = 0;

//--debug flag for extra print statements
bool debug = false;

int main(int argc, char* argv[]){

  //----------------------check that there are an appropriate amount of command line args
  if(argc == 1 || argc > 3){
    cout << "Incorrect usage of program, type:  ./project filename {debug-flag [1] or [N/A]}" << endl;
    return 0; //--exit program
  }

  //----------------------check what type of graph the file is, (D)irected or (U)ndirected
  char graphType;
  graphType = getGraphType(argv[1]);
  if(graphType == 'E'){ //--'E' is code for error, see file_management.cpp
    cout << "There was an error opening or reading the file" << endl;
    return 0; //--exit program
  }
  if(graphType != 'D' && graphType != 'U'){
    cout << "Input file has an incorrect 'type' field, see project outline for more information" << endl;
    return 0; //--exit program
  }

  //----------------------get a total count of how many elements are in the graph
  int n; //--total number of elements
  int errorCheck; //--to see if readFromFile actually worked
  n = getTotalElements(argv[1]);
  if(n == -1){
    cout << "There was an error opening or reading the file" << endl;
    return 0; //--exit program
  }
  
  U_node *U_elementArray = NULL;
  D_node *D_elementArray = NULL;
  
  //----------------------check if debug flag is set or not
  if(argc == 3){
    debug = true;
  }
  
  cout << "debug flag set to: " << debug << endl;
  
  
  //----------------------create the elementArray of specified size
  if(graphType == 'U'){
    U_elementArray = new U_node[n];
    errorCheck = U_readFromFile(argv[1], U_elementArray);
  }
  else if(graphType == 'D'){
    D_elementArray = new D_node[n];
    errorCheck = D_readFromFile(argv[1], D_elementArray);
  }
  else{
    cout << "Never should get to here. Error has occured." << endl;
    return 0;
  }

  //----------------------fill up the data structure with data from the file

  if(errorCheck != 1){
    cout << "There was an error opening or reading the file" << endl;
    return 0; //--exit program
  }
  //-----------------------------------------------------------------------------------------------------//
  //--------------------------------------------The Algorithm--------------------------------------------//
  //-----------------------------------------------------------------------------------------------------//
  bool cycle = false;
  int inc = 0;
  int prevMark = 0;
  if(graphType == 'U'){
    //-----------------------------------------------------------------------------------------//
    //--------------------------------------Run all functions related to UNDIRECTED graphs-----//
    //-----------------------------------------------------------------------------------------//
    cout << endl;
    cout << "#   #    ##### #   # ### ### " << endl;
    cout << "#   #      #    # #  # # #   " << endl;
    cout << "#   #  --  #     #   ### ##  " << endl;
    cout << "#   #      #     #   #   #   " << endl;
    cout << " ###       #     #   #   ### " << endl;
    cout << endl << "Before modifications: " << endl;
    U_displayGraph(n, U_elementArray);
    U_displayDegree(n, U_elementArray);
    //-------------------------------------------Run U_cycle detection
    inc = 0;
    prevMark = mark;
    while(!(cycle) && inc < n){ //--keep checking until a cycle is found or run out of nodes to check
      //--only run the algorithm if the node k hasn't yet been marked
      //--  if node has been marked, that means it has been checked for a cycle already
      //--  the point of this while-loop is to check for disconnected graphs with a cycle.
      //--  could run isCycle on every node as start node, but that is inefficient.
      if(U_elementArray[inc].marked <= prevMark){
        /*debug*/if(debug){ cout << "checking node: " << inc << endl; }
        mark++;
        cycle = U_isCycle(-1, inc, U_elementArray);
        inc++;
      }
      else{
        /*debug*/if(debug){ cout << "skipping node: " << inc << endl; }
        inc++;
      }
    }
    if(cycle){
      cout << endl << "There was a cycle!" << endl;
    }
    else{
      cout << endl << "There was no cycle" << endl;
    }
    
    //-------------------------------------------Run U_removeReplace function
    for(int i = 0; i < n; i++){
      U_removeReplace(i, n, U_elementArray);
    }
    
    cout << endl;
    cout << "After modifications: " << endl;
    U_displayGraph(n, U_elementArray);
    U_displayDegree(n, U_elementArray);
  }
    
  else if(graphType == 'D'){
    //-----------------------------------------------------------------------------------------//
    //--------------------------------------Run all functions related to DIRECTED graphs-------//
    //-----------------------------------------------------------------------------------------//
    cout << endl;
    cout << "###      ##### #   # ### ### " << endl;
    cout << "#  #       #    # #  # # #   " << endl;
    cout << "#   #  --  #     #   ### ##  " << endl;
    cout << "#  #       #     #   #   #   " << endl;
    cout << "###        #     #   #   ### " << endl;
    cout << endl << "Before modifications: " << endl;
    D_displayGraph(n, D_elementArray);
    //D_displayPointsToMe(n, D_elementArray);
    D_displayDegree(n, D_elementArray);
    
    cout << endl;
    
    
    //-------------------------------------------Run D_cycle detection
    cycle = false; //--reset cycle detection 
    inc = 0;
    /*debug*/if(debug){ cout << endl << "running with OLD paint:" << endl; }
    while(!(cycle) && inc < n){ //--keep checking until a cycle is found or run out of nodes
      /*debug*/if(debug){ cout << endl << "checking node: " << inc << endl; }
      mark++;
      cycle = D_isCycle_OLD(-1, inc, D_elementArray);
      inc++;
    }
    if(cycle){
      cout << endl << "There was a cycle (with isCycle_OLD)!" << endl;
    }
    else{
      cout << endl << "There was no cycle (with isCycle_OLD)" << endl;
    }
    
    //-------------------------------------------Run D_cycle detection
    cycle = false; //--reset cycle detection 
    inc = 0;
    /*debug*/if(debug){ cout << endl << "running with NEW paint:" << endl; }
    while(!(cycle) && inc < n){ //--keep checking until a cycle is found or run out of nodes
      /*debug*/if(debug){ cout << endl << "checking node: " << inc << endl; }
      mark++;
      cycle = D_isCycle(-1, inc, D_elementArray);
      inc++;
    }
    if(cycle){
      cout << endl << "There was a cycle (with NEW isCycle)!" << endl;
    }
    else{
      cout << endl << "There was no cycle (with NEW isCycle)" << endl;
    }
    
    //-------------------------------------------Run D_cycle detection with isPath
    /*debug*/if(debug){ cout << endl << "running with isPath:" << endl; }
    cycle = false; //--reset cycle detection 
    inc = 0;         //--reset start/end variable
    while(!(cycle) && inc < n){
      /*debug*/if(debug){ cout << "running on node: " << inc << endl; }
      mark++;
      cycle = D_isPath_cycleDetection(inc, inc, inc, D_elementArray);
      inc++;
    }
    if(cycle){
      cout << endl << "There was a cycle (with isPath)!" << endl;
    }
    else{
      cout << endl << "There was no cycle (with isPath)" << endl;
    }
    
    
//    D_displayMarks(n, D_elementArray);

    //-------------------------------------------Run D_removeReplace function
    for(int i = 0; i < n; i++){
      D_removeReplace(i, n, D_elementArray);
    }
    
    cout << endl << endl;
    cout << "After modifications: " << endl;
    D_displayGraph(n, D_elementArray);
    D_displayDegree(n, D_elementArray);
  }

  //----------------------free up dynamically created memory
  if(graphType == 'U'){
    delete[] U_elementArray;
  }
  else if(graphType == 'D'){
    delete[] D_elementArray;
  }
  
  return 0;
} //--end main


//--works, but is not needed
//--obsolete function, see "mark" global variable at top.
void U_resetPaint(int n, U_node* nodeArray){
  for(int i = 0; i < n; i++){
    nodeArray[i].marked = 0;
  }
}
void D_resetPaint(int n, D_node* nodeArray){
  for(int i = 0; i < n; i++){
    nodeArray[i].marked = 0;
  }
}



