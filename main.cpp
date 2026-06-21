#include "GenEx.h++"
#include "ApEx.h++"
enum estados
{
    MENU,
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
    int textX = (500 - textWidth) / 2;
    DrawText(text, textX, y, fontSize, color);
}
int main()
{
    const int screenWidth = 700;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Exams");
    SetTargetFPS(60);
    estados estadoJ = MENU;

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

    //  Botones del menu
    Rectangle botonAplicar = {(float)(screenWidth / 2 - 125), 250, 250, 50};
    Rectangle botonGenerar = {(float)(screenWidth / 2 - 125), 350, 250, 50};
    Rectangle botonModificar = {(float)(screenWidth / 2 - 125), 450, 250, 50};
    Rectangle botonSalir = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    // Botones extras
    Rectangle botonCalificar = {(float)(screenWidth / 2 - 125), 550, 250, 50};
    Rectangle botonGuardarYSalir = {(float)(screenWidth / 4 - 125), 700, 250, 50};
    Rectangle botonGuardarYSiguiente = {(float)((screenWidth / 4 - 125) * 8), 700, 250, 50};

    while (!WindowShouldClose())
    {
        Vector2 ratonPos = GetMousePosition();
        bool ratonSobreAplicar = CheckCollisionPointRec(ratonPos, botonAplicar);
        bool ratonSobreGenerar = CheckCollisionPointRec(ratonPos, botonGenerar);
        bool ratonSobreModificar = CheckCollisionPointRec(ratonPos, botonModificar);
        bool ratonSobreSalir = CheckCollisionPointRec(ratonPos, botonSalir);
        bool ratonSobreCalificar = CheckCollisionPointRec(ratonPos, botonCalificar);
        bool ratonSobreGuardarYSalir = CheckCollisionPointRec(ratonPos, botonGuardarYSalir);
        bool ratonSobreGuardarYSiguiente = CheckCollisionPointRec(ratonPos, botonGuardarYSiguiente);

        switch (estadoJ)
        {
        case MENU:
            if (ratonSobreAplicar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoJ = APLICAR;
            }
            if (ratonSobreGenerar && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoJ = GENERAR;
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

        case APLICAR:
            formatoPregunta *lista = new formatoPregunta;
            cargar(lista);
            int presionado;
            if (IsKeyPressed(KEY_LEFT))
            {
                if (lista->ant != NULL)
                {
                    lista = lista->ant;
                    presionado = -1;
                }
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                if (lista->sig != NULL)
                {
                    lista = lista->sig;
                    presionado = -1;
                }
            }
            int puntuacion = 0;
            int rSelect;

            if (rSelect == 1)
            {
                puntuacion += lista->puntajeAsignado;
                presionado = 1;
            }
            else if (rSelect == 0)
            {
                puntuacion -= lista->puntajeAsignado;
                presionado = 0;
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

            if (ratonSobreGuardarYSalir && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                guardar(nuevaPregunta, contadorDeCaracteres, contadorCaractersR, indice);
                estadoJ = MENU;
            }
            if (ratonSobreGuardarYSiguiente && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                guardar(nuevaPregunta, contadorDeCaracteres, contadorCaractersR, indice);
                estadoJ = GENERAR;
            }

            break;

        default:
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

        case APLICAR:
            DrawTitleCentered("Examen", 30, 32, GREEN);
            DrawText("Usa FLECHAS IZQUIERDA/DERECHA para moverte entre opciones", 50, 75, 16, DARKGRAY);
            break;

        case GENERAR:
            DrawTitleCentered("Creador de Preguntas", 30, 32, GREEN);
            DrawText("Usa FLECHAS ARRIBA/ABAJO para moverte entre opciones", 50, 75, 16, DARKGRAY);

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
    CloseWindow();
    return 0;
}