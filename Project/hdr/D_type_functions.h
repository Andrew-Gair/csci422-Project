//Andrew Gair (GAIRAD)
//csci422 Project

#ifndef D_TYPE_FUNCTIONS_H
#define D_TYPE_FUNCTIONS_H

//--mark is global variable in main.cpp
extern int mark;
extern int p_mark;
extern bool debug;

void D_displayGraph(int n, D_node* nodeArray);
void D_displayPointsToMe(int n, D_node* nodeArray);
void D_displayDegree(int n, D_node* nodeArray);
void D_displayMarks(int n, D_node* nodeArray);

bool D_isCycle_OLD(int prevNode, int crntNode, D_node* nodeArray);
bool D_isCycle(int prevNode, int crntNode, D_node* nodeArray);
bool D_isPath(int prevNod, int crntNode, int trgtNode, D_node* nodeArray);
bool D_isPath_cycleDetection(int prevNode, int crntNode, int trgtNode, D_node* nodeArray);
bool D_isPathInclusive(int frstNode, int crntNode, int nextNode, D_node* nodeArray);

void D_createPath(int instNode, int bookNode, D_node* nodeArray);
void D_deleteNode(int trgtNode, int n, D_node* nodeArray);
void D_reduceDegree(int trgtNode, D_node* nodeArray);
void D_removeReplace(int crntNode, int n, D_node* nodeArray);
void D_deleteConnections(int deletedNode, D_node* nodeArray);
bool D_isAdjacent(int crntNode, int trgtNode, D_node* nodeArray);

#endif
