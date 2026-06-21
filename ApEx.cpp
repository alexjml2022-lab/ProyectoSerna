#include "ApEx.h++"

void cargar(formatoPregunta *&lista)
{
    FILE *examen = fopen("examen.txt", "r");
    if (examen == NULL)
    {
        return;
    }
    char preg[300], respA[99], respB[99], respC[99], respD[99];
    char correctaA[20], correctaB[20], correctaC[20], correctaD[20];
    int valor;
    while (fscanf(examen,
                  "Pregunta: %299[^\t]\tOpcion A: %98[^\t] [%19[^]]]\tOpcion B: %98[^\t] [%19[^]]]\tOpcion C: %98[^\t] [%19[^]]]\tOpcion D: %98[^\t] [%19[^]]]\tPuntaje asignado: %d\n",
                  preg, respA, correctaA, respB, correctaB, respC, correctaC, respD, correctaD, valor) != EOF)
    {
        formatoPregunta *p = new formatoPregunta;
        strcpy(p->pregunta, preg);
        strcpy(p->respuestaTexto[0], respA);
        strcpy(p->respuestaTexto[1], respB);
        strcpy(p->respuestaTexto[2], respC);
        strcpy(p->respuestaTexto[3], respD);

        p->respuestaCorrecta[0] = (strcmp(correctaA, "CORRECTA") == 0) ? 1 : 0;
        p->respuestaCorrecta[1] = (strcmp(correctaB, "CORRECTA") == 0) ? 1 : 0;
        p->respuestaCorrecta[2] = (strcmp(correctaC, "CORRECTA") == 0) ? 1 : 0;
        p->respuestaCorrecta[3] = (strcmp(correctaD, "CORRECTA") == 0) ? 1 : 0;

        p->puntajeAsignado = valor;
        p->ant = NULL;
        p->sig = NULL;

        pushBack(lista, p);
    }
    fclose(examen);
}

void pushBack(formatoPregunta *&lista, formatoPregunta *p)
{
    p->sig = NULL;

    if (lista == NULL)
    {
        p->ant = NULL;
        lista = p;
        return;
    }

    formatoPregunta *temp = lista;
    while (temp->sig != NULL)
    {
        temp = temp->sig;
    }

    temp->sig = p;
    p->ant = temp;
}