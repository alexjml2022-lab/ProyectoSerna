#include "ApEx.h++"

formatoPregunta *cargar(const char *WMCY)
{
    FILE *examen = fopen(WMCY, "r");
    if (examen == NULL)
    {
        return NULL;
    }

    formatoPregunta *listaLocal = NULL;
    char linea[1024];

    char preg[300], respA[99], respB[99], respC[99], respD[99];
    char correctaA[20], correctaB[20], correctaC[20], correctaD[20];
    int valor;

    while (fgets(linea, sizeof(linea), examen) != NULL)
    {
        // Esta máscara extrae todo lo que esté entre los tabuladores sin importar los espacios internos
        int camposLeidos = sscanf(linea,
                                  "Pregunta:%299[^\t]\tOpcionA:%98[^\t]\t%19[^\t]\tOpcionB:%98[^\t]\t%19[^\t]\tOpcionC:%98[^\t]\t%19[^\t]\tOpcionD:%98[^\t]\t%19[^\t]\tPuntaje:%d",
                                  preg,
                                  respA, correctaA,
                                  respB, correctaB,
                                  respC, correctaC,
                                  respD, correctaD,
                                  &valor);

        // Si la línea no coincide con el nuevo formato estandarizado, la salta
        if (camposLeidos < 10)
        {
            continue;
        }

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

        pushBack(listaLocal, p);
    }

    fclose(examen);
    return listaLocal;
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