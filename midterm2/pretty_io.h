/*
Fecha: 10/10/2025
Autor: Oscar Vargas Pabon

Para mis necesidades de InputOutput
*/
#ifndef PRETTYIO_H
#define PRETTYIO_H

#include<string>
#include<array>
#include<iostream>
#include<vector>
#include"table.h"


/////////////// IO constants 
const int mv_am=4;
const std::vector<std::string> mv_tp      ={"UP","DOWN","LEFT","RIGHT"};
const std::vector<std::array<int,2>> mv_dl={{-1,0},{1,0},{0,-1},{0,1}};

//////////////// read
std::array<int,2> read_mov();
Table read_table(const std::array<int,2>&bnd);

//////////////// write
void print_mov(const std::array<int,2>&delta);
void print_table(const Table &tbl);

#endif // PRETTYIO_H