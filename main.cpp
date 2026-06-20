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
int main()
{
    const int screenWidth = 500;
    const int screenHeight = 620;
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);
    estados estadoJ = MENU;

    //  Botones del menu
    Rectangle botonAplicarratonSobreAplicar = {(float)(screenWidth / 2 - 125), 250, 250, 50};
    Rectangle botonGenerarratonSobreGenerar = {(float)(screenWidth / 2 - 125), 350, 250, 50};
    Rectangle botonModificar = {(float)(screenWidth / 2 - 125), 450, 250, 50};
    Rectangle botonSalir = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    //Botones extras
    Rectangle botonCalificar = {(float)(screenWidth / 2 - 125), 550, 250, 50};

    while (!WindowShouldClose())
    {
        Vector2 ratonPos = GetMousePosition();
        bool ratonSobreAplicar = CheckCollisionPointRec(ratonPos, botonAplicarratonSobreAplicar);
        bool ratonSobreGenerar = CheckCollisionPointRec(ratonPos, botonGenerarratonSobreGenerar);
        bool ratonSobreModificar = CheckCollisionPointRec(ratonPos, botonModificar);
        bool ratonSobreSalir = CheckCollisionPointRec(ratonPos, botonSalir);

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
    }
    CloseWindow();
    return 0;
}