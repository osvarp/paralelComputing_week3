/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Para mis pruebas
*/
#ifndef RANDSTUFF_H
#define RANDSTUFF_H

#include<vector>
#include<random>
#include<chrono>

class Generator{
private:
	std::mt19937 rng;
	int sd;
public:
	Generator();
	Generator(int seed);
	std::vector<int> gen(int sz);
	int get_seed();
};

#endif // RANDSTUFF_H