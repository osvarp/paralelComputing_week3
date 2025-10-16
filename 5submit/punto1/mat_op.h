#ifndef MAT_OP_H
#define MAT_OP_H

#include<vector>

std::vector<std::vector<int>> mat_mult(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b
		);
std::vector<std::vector<int>> mat_add(
		std::vector<std::vector<int>>&a,
		std::vector<std::vector<int>>&b
		);
std::vector<std::vector<int>> mat_transp(
		std::vector<std::vector<int>>&a
		);

#endif//#ifndef MAT_OP_H