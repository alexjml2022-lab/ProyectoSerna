#pragma once
#include <raylib.h>
#include <iostream>

struct formatoPregunta
{
    char pregunta[99];
    char respuestaTexto[4][99];
    int respuestaIcono[4];
    int puntajeAsignado;
    formatoPregunta *sig;
    formatoPregunta *ant;
};
