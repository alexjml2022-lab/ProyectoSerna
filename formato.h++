#pragma once
#include <raylib.h>
#include <iostream>

struct formatoPregunta
{
    char pregunta[300];
    char respuestaTexto[4][99];
    bool respuestaCorrecta[4];
    int puntajeAsignado;
    formatoPregunta *sig;
    formatoPregunta *ant;
};

enum PE{
    PREGUNTA, 
    REPUESTA,
    RC,//Respuetsa correcta
    PUNTAJE
};
