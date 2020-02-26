//Andrew Gair (GAIRAD)
//csci422 Project

#ifndef U_TYPE_FUNCTIONS_H
#define U_TYPE_FUNCTIONS_H

//--mark is global variable in main.cpp
extern int mark;
extern int p_mark;
extern bool debug;

void U_displayGraph(int n, U_node* nodeArray);
void U_displayDegree(int n, U_node* nodeArray);
bool U_isCycle(int prevNode, int crntNode, U_node* nodeArray);
bool U_isPath(int prevNod, int crntNode, int trgtNode, U_node* nodeArray);
bool U_isPathInclusive(int frstNode, int crntNode, int nextNode, U_node* nodeArray);
void U_createPath(int instNode, int bookNode, U_node* nodeArray);
void U_deleteNode(int trgtNode, int n, U_node* nodeArray);
void U_reduceDegree(int trgtNode, U_node* nodeArray);
void U_removeReplace(int crntNode, int n, U_node* nodeArray);
void U_deleteConnections(int deletedNode, int n, U_node* nodeArray);
bool U_isAdjacent(int crntNode, int trgtNode, U_node* nodeArray);

#endif
