#include "ModEx.h++"

void sobrescribirExamen(formatoPregunta *lista, const char *WMCY)
{
    FILE *examen = fopen(WMCY, "w");
    if (examen == NULL) return;

    formatoPregunta *actual = lista;
    while (actual != NULL)
    {
        fprintf(examen, "Pregunta:%s\t", actual->pregunta);
        for (int i = 0; i < 4; i++)
        {
            fprintf(examen, "Opcion%c:%s\t%s\t",
                    'A' + i,
                    actual->respuestaTexto[i],
                    (actual->respuestaCorrecta[i] == 1) ? "CORRECTA" : "INCORRECTA");
        }
        fprintf(examen, "Puntaje:%d\n", actual->puntajeAsignado);
        
        actual = actual->sig;
    }
    fclose(examen);
}//ModEx.cpp