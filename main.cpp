#include "GenEx.h++"
#include "ApEx.h++"
enum estados
{
    MENU,
    SELEX,
    APLICAR,
    GENERAR,
    MODIFICAR,
    SALIR

};
void DrawTextCentered(const char *text, Rectangle btn, int fontSize, Color color)
{
    int textWidth = MeasureText(text, fontSize);
    int textX = btn.x + (btn.width - textWidth) / 2;
    int textY = btn.y + (btn.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, color);
}

void DrawTitleCentered(const char *text, int y, int fontSize, Color color)
{
    int textWidth = MeasureText(text, fontSize);
    int textX = (700 - textWidth) / 2;
    DrawText(text, textX, y, fontSize, color);
}
int main()
{
    const int screenWidth = 700;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Exams");
    SetTargetFPS(60);
    estados estadoJ = MENU;
    char nombreExamen[50] = "\0"; // Aquí guardaremos el nombre (ej. "matematicas")
    int letrasExamen = 0;         // Contador de caracteres para el nombre
    int subModo = 0;

    // variables para generar preguntas

    formatoPregunta *nuevaPregunta;
    nuevaPregunta = new formatoPregunta;
    for (int i = 0; i < 4; i++)
    {
        nuevaPregunta->pregunta[0] = '\0';
        nuevaPregunta->respuestaTexto[i][0] = '\0';
        nuevaPregunta->respuestaCorrecta[i] = 0;
    }
    nuevaPregunta->puntajeAsignado = 0;
    int contadorDeCaracteres = 0;
    int contadorCaractersR[4] = {0, 0, 0, 0};
    int indice = -1;

    // Variables de aplicar
    formatoPregunta *lista = NULL;
    formatoPregunta *preguntaActual = NULL;
    int numP = 1;
    int puntuacion = 0, puntuacionTot = 0;
    bool calificar = false, calificacion = false;

    //  Botones del menu
    Rectangle botonAplicar = {(float)(screenWidth / 2 - 125), 250, 250, 50};
    Rectangle botonGenerar = {(float)(screenWidth / 2 - 125), 350, 250, 50};
    Rectangle botonModificar = {(float)(screenWidth / 2 - 125), 450, 250, 50};
    Rectangle botonSalir = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    // Botones generar
    Rectangle botonGuardarYSalir = {50.0f, 700.0f, 260.0f, 50.0f};
    Rectangle botonGuardarYSiguiente = {390.0f, 700.0f, 260.0f, 50.0f};

    // bototnes aplicar
    Rectangle botonCalificar = {400, 550, 250, 50};
    Rectangle botonOpcA = {70, 220 + (0 * 40), 20, 25};
    Rectangle botonOpcB = {70, 220 + (1 * 40), 20, 25};
    Rectangle botonOpcC = {70, 220 + (2 * 40), 20, 25};
    Rectangle botonOpcD = {70, 220 + (3 * 40), 20, 25};

    // botones epseciales
    Rectangle botonRegresar = {(float)(screenWidth / 3 - 125), 550, 250, 50};
    Rectangle botonContinuar = {(float)(screenWidth / 2 - 125), 450, 250, 50};

    while (!WindowShouldClose())
    {
        Vector2 ratonPos = GetMousePosition();
        //--MENU--
        bool ratonSobreAplicar = CheckCollisionPointRec(ratonPos, botonAplicar);
        bool ratonSobreGenerar = CheckCollisionPointRec(ratonPos, botonGenerar);
        bool ratonSobreModificar = CheckCollisionPointRec(ratonPos, botonModificar);
        bool ratonSobreSalir = CheckCollisionPointRec(ratonPos, botonSalir);

        //--GENERAR--
        bool ratonSobreGuardarYSalir = CheckCollisionPointRec(ratonPos, botonGuardarYSalir);
        bool ratonSobreGuardarYSiguiente = CheckCollisionPointRec(ratonPos, botonGuardarYSiguiente);

        //--APLICAR--
        bool ratonSobreCalificar = CheckCollisionPointRec(ratonPos, botonCalificar);
        bool ratonSobreOpcA = CheckCollisionPointRec(ratonPos, botonOpcA);
        bool ratonSobreOpcB = CheckCollisionPointRec(ratonPos, botonOpcB);
        bool ratonSobreOpcC = CheckCollisionPointRec(ratonPos, botonOpcC);
        bool ratonSobreOpcD = CheckCollisionPointRec(ratonPos, botonOpcD);

        //--Especiales--
        bool ratonSobreRegresar = CheckCollisionPointRec(ratonPos, botonRegresar);
        bool ratonSobreContinuar = CheckCollisionPointRec(ratonPos, botonContinuar);

        switch (estadoJ)
        {
        case MENU:
            if (ratonSobreAplicar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                subModo = 1; // Guardamos que queremos Aplicar
                nombreExamen[0] = '\0';
                letrasExamen = 0;
                estadoJ = SELEX; // Vamos a la pantalla de escribir nombre
            }
            if (ratonSobreGenerar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                subModo = 2; // Guardamos que queremos Generar
                nombreExamen[0] = '\0';
                letrasExamen = 0;
                estadoJ = SELEX; // Vamos a la pantalla de escribir nombre
            }
            if (ratonSobreModificar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoJ = MODIFICAR;
            }
            if (ratonSobreSalir && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                CloseWindow();
                return 0;
            }

            break;

        case SELEX:
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || key == '_')
                {
                    if (letrasExamen < 40)
                    {
                        nombreExamen[letrasExamen] = (char)key;
                        nombreExamen[letrasExamen + 1] = '\0';
                        letrasExamen++;
                    }
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && letrasExamen > 0)
            {
                letrasExamen--;
                nombreExamen[letrasExamen] = '\0';
            }

            if (ratonSobreContinuar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (letrasExamen > 0)
                {
                    // Construimos el nombre completo del archivo: "nombre.txt"
                    char archivoFinal[60];
                    sprintf(archivoFinal, "%s.txt", nombreExamen);

                    if (subModo == 1) // Modo Aplicar
                    {
                        // Limpiamos lista anterior si existe
                        while (lista != NULL)
                        {
                            formatoPregunta *aux = lista;
                            lista = lista->sig;
                            delete aux;
                        }
                        lista = cargar(archivoFinal); // <--- Usamos el archivo dinámico

                        puntuacion = 0;
                        puntuacionTot = 0;
                        if (lista != NULL)
                        {
                            formatoPregunta *aux = lista;
                            while (aux != NULL)
                            {
                                puntuacionTot += aux->puntajeAsignado;
                                aux->opcionSeleccionada = -1;
                                aux->contestadaCorrecta = false;
                                aux = aux->sig;
                            }
                            preguntaActual = lista;
                            numP = 1;
                            estadoJ = APLICAR;
                            calificacion=false;
                            calificar=false;
                        }
                    }
                    else if (subModo == 2) // Modo Generar
                    {
                        estadoJ = GENERAR;
                    }
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
                estadoJ = MENU; // Opción para cancelar
            break;
        }
        case APLICAR:
            if (preguntaActual != NULL && calificacion != true)
            {
                if (IsKeyPressed(KEY_RIGHT))
                {
                    if (preguntaActual->sig != NULL)
                    {
                        preguntaActual = preguntaActual->sig;
                        numP++;
                        if (preguntaActual->sig == NULL)
                        {
                            calificar = true;
                        }
                        else
                            calificar = false;
                    }
                }
                else if (IsKeyPressed(KEY_LEFT))
                {
                    if (preguntaActual->ant != NULL)
                    {
                        preguntaActual = preguntaActual->ant;
                        numP--;
                        if (preguntaActual->sig == NULL)
                        {
                            calificar = true;
                        }
                        else
                            calificar = false;
                    }
                }

                if (ratonSobreCalificar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    calificacion = true;
                }

                Rectangle botonesOpc[4] = {botonOpcA, botonOpcB, botonOpcC, botonOpcD};

                for (int i = 0; i < 4; i++)
                {
                    if (CheckCollisionPointRec(ratonPos, botonesOpc[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        // Comparamos contra la opción seleccionada DE ESTA PREGUNTA específicamente
                        if (preguntaActual->opcionSeleccionada != i)
                        {
                            // 1. Si ya estaba contestada correctamente, restamos los puntos antes de cambiar
                            if (preguntaActual->contestadaCorrecta)
                            {
                                puntuacion -= preguntaActual->puntajeAsignado;
                                preguntaActual->contestadaCorrecta = false;
                            }

                            // 2. Registramos la NUEVA opción en esta pregunta
                            preguntaActual->opcionSeleccionada = i;

                            // 3. Si la nueva opción es la correcta, sumamos el puntaje
                            if (preguntaActual->respuestaCorrecta[i] == 1)
                            {
                                puntuacion += preguntaActual->puntajeAsignado;
                                preguntaActual->contestadaCorrecta = true;
                            }
                        }
                    }
                }
            }

            if (ratonSobreRegresar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoJ = MENU;
            }
            break;

        case GENERAR:
            if (IsKeyPressed(KEY_DOWN))
            {
                indice++;
                if (indice > 5)
                    indice = -1;
            }
            if (IsKeyPressed(KEY_UP))
            {
                indice--;
                if (indice < -1)
                    indice = 5;
            }

            if (indice == -1)
            {
                capturarPregunta(nuevaPregunta, contadorDeCaracteres);
            }
            else if (indice >= 0 && indice <= 3)
            {
                capturarResepuesta(nuevaPregunta, contadorCaractersR[indice], indice);
            }
            else if (indice == 4)
            {
                capuitraRC(nuevaPregunta);
            }
            else if (indice == 5)
            {
                capturaPA(nuevaPregunta);
            }
            char archivoFinal[60];
            sprintf(archivoFinal, "%s.txt", nombreExamen);

            if (ratonSobreGuardarYSalir && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                guardar(nuevaPregunta, contadorDeCaracteres, contadorCaractersR, indice, archivoFinal);
                while (GetCharPressed() > 0)
                    ;
                estadoJ = MENU;
            }
            if (ratonSobreGuardarYSiguiente && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                guardar(nuevaPregunta, contadorDeCaracteres, contadorCaractersR, indice, archivoFinal);
                while (GetCharPressed() > 0)
                    ;
                estadoJ = GENERAR;
            }
            break;
        }
        //--dibujar--
        BeginDrawing();
        ClearBackground(WHITE);
        if (estadoJ == MENU)
        {
            if (ratonSobreAplicar)
            {
                DrawRectangleRoundedLines(botonAplicar, 0.3f, 6, WHITE);
            }
            if (ratonSobreGenerar)
            {
                DrawRectangleRoundedLines(botonGenerar, 0.3f, 6, WHITE);
            }
            if (ratonSobreModificar)
            {
                DrawRectangleRoundedLines(botonModificar, 0.3f, 6, WHITE);
            }
            if (ratonSobreSalir)
            {
                DrawRectangleRoundedLines(botonSalir, 0.3f, 6, WHITE);
            }
        }
        else if (estadoJ == APLICAR)
        {
            if (ratonSobreCalificar)
            {
                DrawRectangleRoundedLines(botonCalificar, 0.3f, 6, WHITE);
            }
        }
        switch (estadoJ)
        {
        case MENU:
            DrawTitleCentered("Exams", 100, 50, GREEN);
            //----------------Boton aplicar--------------
            DrawRectangleRounded(botonAplicar, 0.3f, 6, ratonSobreAplicar ? LIGHTGRAY : RED);
            DrawTextCentered("Aplicar", botonAplicar, 28, WHITE);

            //----------------Boton aplicar--------------
            DrawRectangleRounded(botonGenerar, 0.3f, 6, ratonSobreGenerar ? LIGHTGRAY : RED);
            DrawTextCentered("Generar", botonGenerar, 28, WHITE);

            //----------------Boton aplicar--------------
            DrawRectangleRounded(botonModificar, 0.3f, 6, ratonSobreModificar ? LIGHTGRAY : RED);
            DrawTextCentered("Modificar", botonModificar, 28, WHITE);

            //----------------Boton aplicar--------------
            DrawRectangleRounded(botonSalir, 0.3f, 6, ratonSobreSalir ? LIGHTGRAY : RED);
            DrawTextCentered("Salir", botonSalir, 28, WHITE);
            break;

        case SELEX:
        {
            DrawTitleCentered("Escribe el nombre del Examen", 150, 28, GREEN);
            DrawText("No incluyas espacios ni el '.txt'", 180, 210, 18, DARKGRAY);

            // Caja de texto
            DrawRectangle(150, 260, 400, 50, LIGHTGRAY);
            DrawRectangleLines(150, 260, 400, 50, DARKGRAY);
            DrawText(nombreExamen, 170, 272, 24, BLACK);

            // Efecto de cursor parpadeante
            if ((int)(GetTime() * 2) % 2 == 0)
                DrawText("_", 170 + MeasureText(nombreExamen, 24), 272, 24, BLACK);

            DrawRectangleRounded(botonContinuar, 0.3f, 6, ratonSobreContinuar ? LIGHTGRAY : RED);
            DrawTextCentered("Continuar", botonContinuar, 24, WHITE);
            DrawText("Presiona ESC para volver al menú", 210, 520, 16, GRAY);
            break;
        }
        case APLICAR:
            DrawTitleCentered("Examen", 30, 32, GREEN);
            DrawText("Usa FLECHAS IZQUIERDA/DERECHA para moverte entre opciones", 10, 75, 20, DARKGRAY);
            if (preguntaActual != NULL) // Cambiado a preguntaActual
            {
                char numPP[4];
                sprintf(numPP, "%d", numP);
                DrawText(numPP, 40, 150, 30, BLACK);
                DrawText(preguntaActual->pregunta, 65, 150, 30, BLACK);
                char PPuntTot[4];
                sprintf(PPuntTot, "%d", puntuacionTot);
                DrawText(PPuntTot, 500, 110, 20, BLACK);
                DrawText("pts totales", 540, 110, 20, BLACK);

                // Mostrar las opciones leídas de la lista
                for (int i = 0; i < 4; i++)
                {
                    DrawText(preguntaActual->respuestaTexto[i], 150, 220 + (i * 40), 20, DARKGRAY);
                }
                if (preguntaActual->opcionSeleccionada != 0)
                    DrawRectangleRounded(botonOpcA, 0.9f, 1, ratonSobreOpcA ? LIGHTGRAY : RED);
                if (preguntaActual->opcionSeleccionada != 1)
                    DrawRectangleRounded(botonOpcB, 0.9f, 1, ratonSobreOpcB ? LIGHTGRAY : RED);
                if (preguntaActual->opcionSeleccionada != 2)
                    DrawRectangleRounded(botonOpcC, 0.9f, 1, ratonSobreOpcC ? LIGHTGRAY : RED);
                if (preguntaActual->opcionSeleccionada != 3)
                    DrawRectangleRounded(botonOpcD, 0.9f, 1, ratonSobreOpcD ? LIGHTGRAY : RED);
            }
            else
            {
                DrawText("No hay preguntas cargadas en el examen.txt", 55, 150, 20, RED);
            }

            if (calificar == true)
            {
                DrawRectangleRounded(botonRegresar, 0.3f, 6, ratonSobreRegresar ? LIGHTGRAY : RED);
                DrawTextCentered("Regresar", botonRegresar, 28, WHITE);
                DrawRectangleRounded(botonCalificar, 0.3f, 6, ratonSobreCalificar ? LIGHTGRAY : RED);
                DrawTextCentered("Calificar", botonCalificar, 28, WHITE);
                if (calificacion == true)
                {
                    char PPunt[4];
                    sprintf(PPunt, "%d", puntuacion);
                    DrawText(PPunt, screenWidth / 2, 650, 30, BLACK);
                }
            }
            break;

        case GENERAR:
            DrawTitleCentered("Creador de Preguntas", 30, 32, GREEN);
            DrawText("Usa FLECHAS ARRIBA/ABAJO para moverte entre opciones", 50, 75, 20, DARKGRAY);

            DrawText("Pregunta:", 50, 110, 18, BLACK);
            DrawRectangle(50, 135, 600, 35, LIGHTGRAY);
            DrawText(nuevaPregunta->pregunta, 60, 142, 18, BLACK);
            if (indice == -1 && (int)(GetTime() * 2) % 2 == 0)
                DrawText("_", 60 + MeasureText(nuevaPregunta->pregunta, 18), 142, 18, BLACK);

            for (int i = 0; i < 4; i++)
            {
                int posYLabel = 185 + (i * 75);
                int posYBox = 210 + (i * 75);

                char prefijo[12] = {'O', 'p', 'c', 'i', 'o', 'n', ' ', (char)('A' + i), ':', '\0'};
                DrawText(prefijo, 50, posYLabel, 18, BLACK);
                DrawRectangle(50, posYBox, 600, 35, LIGHTGRAY);
                DrawText(nuevaPregunta->respuestaTexto[i], 60, posYBox + 7, 18, BLACK);

                if (indice == i && (int)(GetTime() * 2) % 2 == 0)
                    DrawText("_", 60 + MeasureText(nuevaPregunta->respuestaTexto[i], 18), posYBox + 7, 18, BLACK);
            }

            DrawText("Presiona la tecla (A, B, C, D) para la respuesta correcta:", 50, 495, 18, BLACK);
            DrawRectangle(50, 520, 200, 35, LIGHTGRAY);

            char opcCorr[2] = {'-', '\0'};
            for (int i = 0; i < 4; i++)
            {
                if (nuevaPregunta->respuestaCorrecta[i] == 1)
                    opcCorr[0] = 'A' + i;
            }
            DrawText(opcCorr, 140, 527, 20, BLACK);

            DrawText("Asigna un puntaje (Tecla num. 0-9):", 50, 570, 18, BLACK);
            DrawRectangle(50, 595, 200, 35, LIGHTGRAY);

            char puntajeTxt[4];
            sprintf(puntajeTxt, "%d", nuevaPregunta->puntajeAsignado);
            DrawText(puntajeTxt, 140, 602, 20, BLACK);

            DrawRectangleRounded(botonGuardarYSalir, 0.3f, 6, ratonSobreGuardarYSalir ? DARKGREEN : GREEN);
            DrawTextCentered("Guardar y salir", botonGuardarYSalir, 24, WHITE);
            DrawRectangleRounded(botonGuardarYSiguiente, 0.3f, 6, ratonSobreGuardarYSiguiente ? DARKGREEN : GREEN);
            DrawTextCentered("Guardar y siguiente", botonGuardarYSiguiente, 24, WHITE);
            break;
        }

        EndDrawing();
    }
    while (lista != NULL)
    {
        formatoPregunta *aux = lista;
        lista = lista->sig;
        delete aux;
    }
    delete nuevaPregunta;
    CloseWindow();
    return 0;
}