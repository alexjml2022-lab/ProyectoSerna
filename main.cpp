#include <raylib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
    int textX = (500 - textWidth) / 2 ;
    DrawText(text, textX, y, fontSize, color);
}
int main()
{
    const int screenWidth = 700;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Exams");
    SetTargetFPS(60);
    estados estadoJ = MENU;

    //  Botones del menu
    Rectangle botonAplicar = {(float)(screenWidth / 2 - 125), 250, 250, 50};
    Rectangle botonGenerar = {(float)(screenWidth / 2 - 125), 350, 250, 50};
    Rectangle botonModificar = {(float)(screenWidth / 2 - 125), 450, 250, 50};
    Rectangle botonSalir = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    // Botones extras
    Rectangle botonCalificar = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    while (!WindowShouldClose())
    {
        Vector2 ratonPos = GetMousePosition();
        bool ratonSobreAplicar = CheckCollisionPointRec(ratonPos, botonAplicar);
        bool ratonSobreGenerar = CheckCollisionPointRec(ratonPos, botonGenerar);
        bool ratonSobreModificar = CheckCollisionPointRec(ratonPos, botonModificar);
        bool ratonSobreSalir = CheckCollisionPointRec(ratonPos, botonSalir);
        bool ratonSobreCalificar = CheckCollisionPointRec(ratonPos, botonCalificar);

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

            break;

        case GENERAR:

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
            DrawTextCentered("Generar", botonAplicar, 28, WHITE);

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

            break;

        case GENERAR:

            break;

        default:
            break;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}