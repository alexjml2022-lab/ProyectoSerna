#pragma once
#include <raylib.h>
#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
struct formatoPregunta
{
    char pregunta[300];
    char respuestaTexto[4][99];
    int respuestaCorrecta[4];
    int puntajeAsignado;
    int opcionSeleccionada = -1; 
    bool contestadaCorrecta = false;
    formatoPregunta *sig;
    formatoPregunta *ant;
};
enum OPC{
    A,B,C,D
};