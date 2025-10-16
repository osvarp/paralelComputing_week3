#ifndef MAT_OP_H
#define MAT_OP_H

#include<vector>
#include<array>
#include<functional>

const std::vector<std::array<int,2>> mov={{0,1},{0,-1},{1,0},{-1,0}};

std::vector<std::vector<double>> simul( int n, int m, std::array<int,2> init );

#endif//#ifndef MAT_OP_H