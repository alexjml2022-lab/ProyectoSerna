#pragma once
#include "formato.h++"
#include <raylib.h>
#include <iostream>

void capturarPregunta(formatoPregunta *, int &);
void capturarResepuesta(formatoPregunta *, int &, int);
void capuitraRC(formatoPregunta *, int);
void capturaPA(formatoPregunta *);