#include "GenEx.h++"
#include <cstring>
using namespace std;

void capturarPregunta(formatoPregunta *p, int &contadorDeCaracteres)
{
    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32 && key <= 125)
        {
            p->pregunta[contadorDeCaracteres] = (char)key;
            p->pregunta[contadorDeCaracteres + 1] = '\0';
            contadorDeCaracteres++;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        contadorDeCaracteres--;
        if (contadorDeCaracteres < 0)
        {
            contadorDeCaracteres = 0;
        }
        p->pregunta[contadorDeCaracteres] = '\0';
    }
}
void capturarResepuesta(formatoPregunta *p, int &contadorDeCaracteres, int indiceRespuesta)
{
    int key = GetCharPressed();
    if (indiceRespuesta < 0 || indiceRespuesta > 3)
        return;
    while (key > 0)
    {
        if (key >= 32 && key <= 125)
        {
            p->respuestaTexto[indiceRespuesta][contadorDeCaracteres] = (char)key;
            p->respuestaTexto[indiceRespuesta][contadorDeCaracteres + 1] = '\0';
            contadorDeCaracteres++;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        contadorDeCaracteres--;
        if (contadorDeCaracteres < 0)
        {
            contadorDeCaracteres = 0;
        }
        p->respuestaTexto[indiceRespuesta][contadorDeCaracteres] = '\0';
    }
}
void capuitraRC(formatoPregunta *p, int indiceRespuesta)
{
    int key = GetCharPressed();
    if (indiceRespuesta < 0 || indiceRespuesta > 3)
        return;
    if (key > 0)
    {
        p->respuestaCorrecta[indiceRespuesta] = key;
    }
}
void capturaPA(formatoPregunta *p)
{
    int key = GetCharPressed();
    if (key >= '0' && key <= '9')
    {
        
        p->puntajeAsignado = key - '0'; 
    }
}