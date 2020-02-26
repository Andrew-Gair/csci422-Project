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

using namespace std;

void U_displayGraph(int n, U_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << nodeArray[i].ID << " 's neighbours are: ";
    for(int j = 0; j < nodeArray[i].neighbours.size(); j++){
      cout << nodeArray[i].neighbours[j] << " ";
    }
    cout << endl;
  }
}

void U_displayDegree(int n, U_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << nodeArray[i].ID << "'s degree is: " << nodeArray[i].degree;
    cout << endl;
  }
}

//--loop through each node's neighbours with the for loop.
//--  if the node's neighbour has been marked, and is not the previous node, then there is a cycle!
//--  otherwise, if the node is not the previous node, use recursion and launch this function
//--    again but using the neighbour as the current node now.
//--  return whatever value to cycleFound
//--  so if its true, then can return true, if its false, just loop again with for loop.
//--  if no cycles were found after going through all neighbours, then return false, this node
//--    is not involved in the cycle if there is going to be a cycle at all.
bool U_isCycle(int prevNode, int crntNode, U_node* nodeArray){
  bool cycleFound = false;
  nodeArray[crntNode].marked = mark;
 /*debug*/ if(debug){ cout << crntNode << " started isCycle" << endl; }
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
 /*debug*/ if(debug){ cout << crntNode << " is checking " << nodeArray[crntNode].neighbours[i] << endl; }
    if(nodeArray[nodeArray[crntNode].neighbours[i]].marked == mark && prevNode != nodeArray[crntNode].neighbours[i]){
 /*debug*/ if(debug){ cout << "cycle terminates at: " << crntNode << endl; }
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode){
      cycleFound = U_isCycle(crntNode, nodeArray[crntNode].neighbours[i], nodeArray);
    }
    if(cycleFound){
      return true;
    }
  }
  return false;
}

//--WORKS: Not suuuper efficient though...
//--  checks if the crntNode is adjacent to trgtNode by traversing
//--  through the entire neighbours list.
bool U_isAdjacent(int crntNode, int trgtNode, U_node* nodeArray){
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
    if(nodeArray[crntNode].neighbours[i] == trgtNode){
      return true;
    }
  }
  return false;
}

//--WORKS:
//--loop through each node's neighbours with the for loop
//--  if the target node is found as a neighbour of current node,
//--    then can return true, there is a path!
//--  otherwise launch the function again using a neighbour of current node
//--    as the new starter node so long as it isn't prevNode and isn't marked.
//--  return whatever value to pathFound.
//--  if pathFound is true, then return true.
//--  if not true, then return false after checking all neighbours (and those
//--    node's neighbours as well)
bool U_isPath(int prevNode, int crntNode, int trgtNode, U_node* nodeArray){
  bool pathFound = false;
  for(int i = 0; i < nodeArray[crntNode].degree; i++){
    nodeArray[crntNode].marked = mark;
    if(nodeArray[crntNode].neighbours[i] == trgtNode){
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode && nodeArray[nodeArray[crntNode].neighbours[i]].marked != mark){
      pathFound = U_isPath(crntNode, nodeArray[crntNode].neighbours[i], trgtNode, nodeArray);
    }
    if(pathFound){
      return true;
    }
  }
  return false;
}

//--WORKS:
//--check inclNode if it has crntNode as a neighbour
//--check crntNode if it has trgtNode as a neighbour
//--  if both are true, then crntNode can be removed!
//
//  A -> B -> C
//  check if A goes to B, then check if B goes to C.
//--  if so, can remove B.
bool U_isPathInclusive(int frstNode, int crntNode, int nextNode, U_node* nodeArray){
  bool path2frst = false;
  bool path2next = false;
  bool pathFound = false;
  //--check if frstNode has crntNode as a neighbour
  for(int i = 0; i < nodeArray[frstNode].neighbours.size(); i++){
    if(nodeArray[frstNode].neighbours[i] == crntNode){
      path2frst = true; //--if yes, then check nextNode right away
      break;
    }
  }
  //--check if crntNode has nextNode as a neighbour
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
    if(nodeArray[crntNode].neighbours[i] == nextNode){
      path2next = true;
      break;
    }
  }
  //--if there is a path to both, then can return true
  if(path2frst && path2next){
    return true;
  }
  else{
    return false;
  }
}

//--WORKS:
//--use:   elementArray[bop].neighbours.insert(elementArray[bop].neighbours.begin()+someVal, val2insert);
//--insert instNode into bookNode.
//--  needs to remain sorted (for arbitrary reasons I suppose.)
//--  and so the while-loop incremenets to the appropriate entry
//--  and .insert(begin()+i, instNode) does the rest.
//--  nodes past where instNode were placed get shoved further down the vector
void U_createPath(int instNode, int bookNode, U_node* nodeArray){
  int i = 0;
  while(nodeArray[bookNode].neighbours[i] <= instNode && i < nodeArray[bookNode].neighbours.size()){
    i++;
  }
  if(i < nodeArray[bookNode].neighbours.size()){ //--don't insert if there isnt any nodes after
    nodeArray[bookNode].neighbours.insert(nodeArray[bookNode].neighbours.begin()+i, instNode);
    nodeArray[bookNode].degree++;
    nodeArray[instNode].degree++;
  }
  else{  //--instead just push to back
    nodeArray[bookNode].neighbours.push_back(instNode);
    nodeArray[bookNode].degree++;
    nodeArray[instNode].degree++;
  }
}

//--first reduce the incoming degree for all nodes that trgtNode is neighbours of
//--                                             there should only be 1 such node.
//--then free dynamic memory
//--  then set flags to what a deleted node should be.
//--  trgtNode will still show up in elementArray, its just set to -1 to denote its been deleted
void U_deleteNode(int trgtNode, int n, U_node* nodeArray){
  for(int i = 0; i < nodeArray[trgtNode].neighbours.size(); i++){
    nodeArray[nodeArray[trgtNode].neighbours[i]].degree--;
  }
  vector<int>().swap(nodeArray[trgtNode].neighbours); //--free up dynamic memory
  nodeArray[trgtNode].ID = -1; //--set trgtNode to invalid entry
  nodeArray[trgtNode].degree = 0;
  U_deleteConnections(trgtNode, n, nodeArray);  //--nobody should point to deleted node anymore
}

//--WORKS: -------------------------------------------------------------------------NOT EFFICIENT, NOT EVEN CLOSE!
//--  traverses through the entire graph
//--  deletes all occurances of the deleted node.
void U_deleteConnections(int deletedNode, int n, U_node* nodeArray){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < nodeArray[i].neighbours.size(); j++){
      if(nodeArray[i].neighbours[j] == deletedNode){
        nodeArray[i].neighbours.erase(nodeArray[i].neighbours.begin() + j);
        //------------------------------------------------------------DOESNT reduceDegree HANDLE THIS???
        //nodeArray[i].out_degree--; //--reduce outgoing degree as node no longer exists DO I NEED THIS?
      }
    }
  }
}

//--WORKS: duh, its pretty simple
//--reduce the outgoing degree count for trgtNode
//--  this is called when trgtNode's neighbour was deleted with deleteNode()
void U_reduceDegree(int trgtNode, U_node* nodeArray){
  nodeArray[trgtNode].degree--;
}

//--WORKS: does not delete B in A -> B -> C if A -> C exists, which is good.
//--2 versions, 1 for (U)ndirected, and 1 for (D)irected
//--  first check node degree
//--  then check if there is a path from 1 of its neighbours to the other neighbour
//--  then check that those neighbours arent themselves adjacent (do not remove if they are)
//--  reduce the degree of source node
//--  create the path between the 2 nodes (as there was no path prior)
//--    create the path going the other way also
//--  delete the middle node (crntNode) now, this also reduces degree of trgtNode
void U_removeReplace(int crntNode, int n, U_node* nodeArray){
  if(nodeArray[crntNode].degree == 2){
    if(U_isPathInclusive(nodeArray[crntNode].neighbours[0], crntNode, nodeArray[crntNode].neighbours[1], nodeArray)){
      if(!(U_isAdjacent(nodeArray[crntNode].neighbours[0], nodeArray[crntNode].neighbours[1], nodeArray))){
        U_reduceDegree(nodeArray[crntNode].neighbours[0], nodeArray);
        U_reduceDegree(nodeArray[crntNode].neighbours[1], nodeArray);
        U_createPath(nodeArray[crntNode].neighbours[0], nodeArray[crntNode].neighbours[1], nodeArray);
        U_createPath(nodeArray[crntNode].neighbours[1], nodeArray[crntNode].neighbours[0], nodeArray);
        U_deleteNode(crntNode, n, nodeArray);
      }
    }
  }
}
