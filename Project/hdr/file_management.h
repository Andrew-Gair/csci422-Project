//Andrew Gair (GAIRAD)
//csci422 Project

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

struct U_node{
    int ID = -1;
    std::vector<int> neighbours;
    int marked = 0;
    int degree = 0;
};

struct D_node{
    int ID = -1;
    std::vector<int> neighbours;
    std::vector<int> pointsToMe;
    int marked = 0;     //--for cycle detected
    int p_mark = 0;     //--for path detection
    int trvsed = 0;     //--to avoid unecessary traversals
    int in_degree = 0;  //--vertices that point to this node
    int out_degree = 0; //--nodes this vertex points to
};

//--Need to know what type of graph this is.
//--  either directed or undirected, which is
//--  represented with a D or a U
char getGraphType(char *fileName);

//--Need to know how big to make dynamic array, and so this
//--  function just grabs the first value from the file
int getTotalElements(char *fileName);

//--function that reads values from the file into the previously
//--  created dynamic array. Therefore it takes such an array
//--  as a parameter (passed by reference of course).
int U_readFromFile(char *fn, U_node *&nodeArray);

int D_readFromFile(char *fn, D_node *&nodeArray);

#endif
