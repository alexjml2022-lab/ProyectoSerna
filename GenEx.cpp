#include "GenEx.h++"

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
void capuitraRC(formatoPregunta *p)
{
    int key = GetCharPressed();
    if (key > 0)
    {
        if (key >= 'a' && key <= 'd')
            key -= 32;

        if (key >= 'A' && key <= 'D')
        {
            int indice = key - 'A';
            for (int i = 0; i < 4; i++)
                p->respuestaCorrecta[i] = 0;
            p->respuestaCorrecta[indice] = 1;
        }
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

void guardar(formatoPregunta *p, int &contadorDeCaracteres, int *contadorCaractersR, int &indice)
{
    FILE *examen = fopen("examen.txt", "a");
    if (examen != NULL)
    {
        // Guardamos usando delimitadores de tabulación (\t) perfectos
        fprintf(examen, "Pregunta:%s\t", p->pregunta);
        for (int i = 0; i < 4; i++)
        {
            fprintf(examen, "Opcion%c:%s\t%s\t",
                    'A' + i,
                    p->respuestaTexto[i],
                    (p->respuestaCorrecta[i] == 1) ? "CORRECTA" : "INCORRECTA");
        }
        fprintf(examen, "Puntaje:%d\n", p->puntajeAsignado);
        fclose(examen);
    }
    p->pregunta[0] = '\0';
    for (int i = 0; i < 4; i++)
    {
        p->respuestaTexto[i][0] = '\0';
        p->respuestaCorrecta[i] = 0;
        contadorCaractersR[i] = 0;
    }
    p->puntajeAsignado = 0;
    contadorDeCaracteres = 0;
    indice = -1;
}