//Andrew Gair (GAIRAD)
//csci422 Project

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "../hdr/file_management.h"
#include "../hdr/D_type_functions.h"

using namespace std;

//--Display the graph, represented as a bunch of adjacency lists.
void D_displayGraph(int n, D_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << nodeArray[i].ID << " 's neighbours are: ";
    for(int j = 0; j < nodeArray[i].neighbours.size(); j++){
      cout << nodeArray[i].neighbours[j] << " ";
    }
    cout << endl;
  }
}

//--Display just the pointsToMe vector, similar to displayGraph above.
void D_displayPointsToMe(int n, D_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << nodeArray[i].ID << " 's pointsToMe are: ";
    for(int j = 0; j < nodeArray[i].pointsToMe.size(); j++){
      cout << nodeArray[i].pointsToMe[j] << " ";
    }
    cout << endl;
  }
}

//--Display the degree (in-degree and out-degree) of each node in the graph.
void D_displayDegree(int n, D_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << nodeArray[i].ID << "'s in_degree is: " << nodeArray[i].in_degree << "  |  ";
    cout << nodeArray[i].ID << "'s out_degree is: " << nodeArray[i].out_degree;
    cout << endl;
  }
}

//--Display marks value for each and every node in graph.
void D_displayMarks(int n, D_node* nodeArray){
  for(int i = 0; i < n; i++){
    cout << "node: " << nodeArray[i].ID << "'s mark is " << nodeArray[i].marked << endl;
  }
}


//--OLD UNPAINTING METHOD:
//--Return true if a cycle is found, false otherwise.
//--  will paint each node with 'marked' variable.
//--go through each neighbour of the current node
//--  and for each neighbour, if its not already painted, run isCycle() on that neighbour.
//--  this process repeats until no more neighbours remain, in which case the node
//--  that just checked all neighbours returns false and recursion begins again on the
//--  node that previously called isCycle().
bool D_isCycle_OLD(int prevNode, int crntNode, D_node* nodeArray){
  bool cycleFound = false;
  nodeArray[crntNode].marked = mark;
 /*debug*/ if(debug){ cout << crntNode << " started isCycle" << endl; }
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
 /*debug*/ if(debug){ cout << crntNode << " is checking " << nodeArray[crntNode].neighbours[i] << endl; }
    if(nodeArray[nodeArray[crntNode].neighbours[i]].marked == mark && prevNode != nodeArray[crntNode].neighbours[i]){
 /*debug*/ if(debug){ cout << "cycle terminates at " << nodeArray[crntNode].neighbours[i] << endl; }
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode && nodeArray[nodeArray[crntNode].neighbours[i]].trvsed != mark){
      cycleFound = D_isCycle(crntNode, nodeArray[crntNode].neighbours[i], nodeArray);
    }
    if(cycleFound){
      return true;
    }
//    //--if the neighbour that just finished returned false (if it returned true wouldn't get to here...)
//    //--  check if there is a path to get from that neighbour to crntNode
//    if(!(D_isAdjacent(nodeArray[crntNode].neighbours[i], crntNode, nodeArray))){
//      nodeArray[nodeArray[crntNode].neighbours[i]].marked = 0;
//    }
  }
  
//--if the neighbour that just finished returned false (if it returned true wouldn't get to here...)
//--  check if there is a path to each node that points to this node
//--  if there is no path, unmark crntNode.
//--  if there is a path to each and every pointsToMe node, then leave crntNode marked.
  for(int j = 0; j < nodeArray[crntNode].pointsToMe.size(); j++){
    if(!(D_isPath(prevNode, crntNode, nodeArray[crntNode].pointsToMe[j], nodeArray))){
      nodeArray[crntNode].marked = 0; //--remove the mark
      /*debug*/ if(debug){ cout << "set " << crntNode << "'s mark to " << nodeArray[crntNode].marked << endl; }
      break;  //--no need to keep checking, node will remain unpainted.
    }
    p_mark++; //--increment so next isPath run can fully traverse the graph
  }
  return false;
}

//--NEW UNPAINTING METHOD: Does not make use of pointsToMe vector!
//--Return true if a cycle is found, false otherwise.
//--  will paint each node with 'marked' variable.
//--  will place a paint-chip with 'trvsed' variable.
//--go through each neighbour of the current node
//--  and for each neighbour, if its not already painted, run isCycle() on that neighbour.
//--  this process repeats until no more neighbours remain, in which case the node
//--  that just checked all neighbours returns false and recursion begins again on the
//--  node that previously called isCycle().
bool D_isCycle(int prevNode, int crntNode, D_node* nodeArray){
  bool cycleFound = false;
  nodeArray[crntNode].marked = mark;
  nodeArray[crntNode].trvsed = mark;
 /*debug*/ if(debug){ cout << crntNode << " started isCycle" << endl; }
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
 /*debug*/ if(debug){ cout << crntNode << " is checking " << nodeArray[crntNode].neighbours[i] << endl; }
    if(nodeArray[nodeArray[crntNode].neighbours[i]].marked == mark && prevNode != nodeArray[crntNode].neighbours[i]){
 /*debug*/ if(debug){ cout << "cycle terminates at " << nodeArray[crntNode].neighbours[i] << endl; }
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode && nodeArray[nodeArray[crntNode].neighbours[i]].trvsed != mark){
      cycleFound = D_isCycle(crntNode, nodeArray[crntNode].neighbours[i], nodeArray);
    }
    if(cycleFound){
      return true;
    }
  }
  nodeArray[crntNode].marked = 0;
  return false;
}

//--Checks if the crntNode is adjacent to trgtNode by traversing
//--  through the entire neighbours list.
bool D_isAdjacent(int crntNode, int trgtNode, D_node* nodeArray){
  for(int i = 0; i < nodeArray[crntNode].neighbours.size(); i++){
    if(nodeArray[crntNode].neighbours[i] == trgtNode){
      return true;
    }
  }
  return false;
}

//--Loop through each node's neighbours with the for loop
//--  if the target node is found as a neighbour of current node,
//--    then can return true, there is a path!
//--  otherwise launch the function again using a neighbour of current node
//--    as the new starter node so long as it isn't prevNode and isn't p_marked.
//--  return whatever value to pathFound.
//--  if pathFound is true, then return true.
//--  if not true, then return false after checking all neighbours (and those
//--    node's neighbours as well)
bool D_isPath(int prevNode, int crntNode, int trgtNode, D_node* nodeArray){
 /*debug*/ if(debug){ cout << crntNode << " has started isPath to target " << trgtNode << endl; }
  bool pathFound = false;
  nodeArray[crntNode].p_mark = mark;
  for(int i = 0; i < nodeArray[crntNode].out_degree; i++){
 /*debug*/ if(debug){ cout << crntNode << " is checking path to " << nodeArray[crntNode].neighbours[i] << endl; }
    if(nodeArray[crntNode].neighbours[i] == trgtNode){
//      cout << crntNode << " is adjacent to " << trgtNode << endl;
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode && nodeArray[nodeArray[crntNode].neighbours[i]].p_mark != mark){
      pathFound = D_isPath(crntNode, nodeArray[crntNode].neighbours[i], trgtNode, nodeArray);
    }
    if(pathFound){
      return true;
    }
  }
//  cout << crntNode << " not adjacent to " << trgtNode << endl;
  return false;
}

//--Uses same logic as above, but modified to not allow immediate cycles to neighbours.
//--  IE:  A <-> B is not a cycle (of length 3), but it is a path.
bool D_isPath_cycleDetection(int prevNode, int crntNode, int trgtNode, D_node* nodeArray){
 /*debug*/ if(debug){ cout << crntNode << " has started isPath with target " << trgtNode << endl; }
  bool pathFound = false;
  for(int i = 0; i < nodeArray[crntNode].out_degree; i++){
    nodeArray[crntNode].p_mark = mark;
    if(nodeArray[crntNode].neighbours[i] == trgtNode && nodeArray[crntNode].neighbours[i] != prevNode){
      return true;
    }
    if(nodeArray[crntNode].neighbours[i] != prevNode && nodeArray[nodeArray[crntNode].neighbours[i]].p_mark != mark){
      if(debug){ cout << crntNode << " is checking through " << nodeArray[crntNode].neighbours[i] << endl; }
      pathFound = D_isPath_cycleDetection(crntNode, nodeArray[crntNode].neighbours[i], trgtNode, nodeArray);
    }
    if(pathFound){
      return true;
    }
  }
  return false;
}

//--Check inclNode if it has crntNode as a neighbour
//--Check crntNode if it has trgtNode as a neighbour
//--  if both are true, then crntNode can be removed!
//
//--  A -> B -> C
//--  check if A goes to B, then check if B goes to C.
//--    if so, can remove B.
bool D_isPathInclusive(int frstNode, int crntNode, int nextNode, D_node* nodeArray){
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

//--Insert instNode into bookNode.
//--  needs to remain sorted (for arbitrary reasons).
//--  and so the while-loop incremenets to the appropriate entry
//--  and insert(begin()+i, instNode) does the rest.
//--  nodes past where instNode were placed get shoved further down the vector
void D_createPath(int instNode, int bookNode, D_node* nodeArray){
  int i = 0;
  while(nodeArray[bookNode].neighbours[i] <= instNode && i < nodeArray[bookNode].neighbours.size()){
    i++;
  }
  if(i < nodeArray[bookNode].neighbours.size()){ //--don't insert if there isnt any nodes after
    nodeArray[bookNode].neighbours.insert(nodeArray[bookNode].neighbours.begin()+i, instNode);
    nodeArray[instNode].in_degree++;
    nodeArray[bookNode].out_degree++;
  }
  else{  //--instead just push to back
    nodeArray[bookNode].neighbours.push_back(instNode);
    nodeArray[instNode].in_degree++;
    nodeArray[bookNode].out_degree++;
  }
}

//--First reduce the incoming degree for all nodes that trgtNode is neighbours of
//--                                             there should only be 1 such node.
//--Then free dynamic memory with swap()
//--  then set flags to what a deleted node should be.
//--  trgtNode will still show up in elementArray, its just set to -1 to denote its been deleted
void D_deleteNode(int trgtNode, int n, D_node* nodeArray){
  for(int i = 0; i < nodeArray[trgtNode].neighbours.size(); i++){
    nodeArray[nodeArray[trgtNode].neighbours[i]].in_degree--;
  }
  D_deleteConnections(trgtNode, nodeArray);  //--nobody should point to deleted node anymore
  vector<int>().swap(nodeArray[trgtNode].neighbours); //--free up dynamic memory
  nodeArray[trgtNode].ID = -1; //--set trgtNode to invalid entry
  nodeArray[trgtNode].in_degree = 0;
  nodeArray[trgtNode].out_degree = 0;
}

//--Deletes the connections between dlteNode and all its neighbours.
void D_deleteConnections(int dlteNode, D_node* nodeArray){
  int tempNode;
  tempNode = nodeArray[dlteNode].pointsToMe[0];
  for(int j = 0; j < nodeArray[tempNode].neighbours.size(); j++){ 
    if(nodeArray[tempNode].neighbours[j] == dlteNode){
      nodeArray[tempNode].neighbours.erase(nodeArray[tempNode].neighbours.begin() + j);
      nodeArray[tempNode].out_degree--;
    }
  }
}

//--OUTDATED FUNCTION: never called...
//--Reduce the outgoing degree count for trgtNode
void D_reduceDegree(int trgtNode, D_node* nodeArray){
  nodeArray[trgtNode].out_degree--;
}

//--Organizes and calls the other functions to delete nodes of degree 2.
//--  If the node has degree 2 then will need to determine direction of this path from
//--    one neighbour to the other.
//--    Will do this through calling isPathInclusive and changing the order of parameters.
//--  If there is a path, then can delete the node through calling other functions.
void D_removeReplace(int crntNode, int n, D_node* nodeArray){
  if(nodeArray[crntNode].in_degree == 1 && nodeArray[crntNode].out_degree == 1){
    //--  going one way
    if(D_isPathInclusive(nodeArray[crntNode].pointsToMe[0], crntNode, nodeArray[crntNode].neighbours[0], nodeArray)){
      if(!(D_isAdjacent(nodeArray[crntNode].pointsToMe[0], nodeArray[crntNode].neighbours[0], nodeArray))){
        D_createPath(nodeArray[crntNode].neighbours[0], nodeArray[crntNode].pointsToMe[0], nodeArray);
        D_deleteNode(crntNode, n, nodeArray);
      }
    }
    //--  else going the other way
    else if(D_isPathInclusive(nodeArray[crntNode].neighbours[0], crntNode, nodeArray[crntNode].pointsToMe[0], nodeArray)){
      if(!(D_isAdjacent(nodeArray[crntNode].neighbours[0], nodeArray[crntNode].pointsToMe[0], nodeArray))){
        D_createPath(nodeArray[crntNode].pointsToMe[0], nodeArray[crntNode].neighbours[0], nodeArray);
        D_deleteNode(crntNode, n, nodeArray);
      }
    }
  }
}

