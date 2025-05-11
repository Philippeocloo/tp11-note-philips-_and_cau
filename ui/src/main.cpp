#include <Board.h>
#include <Cell.h>
#include <raylib.h>

#include "main.h"
#include "ColorConverter.h"
#include "RobotRenderer.h"
#include "Consts.h"
#include "Scene.h"
#include "MenuScene.h"

Scene* currentScene = new MenuScene();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = WINDOW_SIZE_X;
    const int screenHeight = WINDOW_SIZE_Y;
    SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_WINDOW_HIGHDPI);

    InitWindow(screenWidth, screenHeight, "Robot's Game");

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        currentScene->Update(GetFrameTime());
        // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        // {
        //     if (!collision.hit)
        //     {
        //         ray = GetScreenToWorldRay(GetMousePosition(), camera);

        //         // // Check collision between ray and box
        //         // collision = GetRayCollisionBox(ray,
        //         //             (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
        //         //                           (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});

        //         //TODO: CHECK COLISIONS WITH ROBOTS
        //     }
        //     else collision.hit = false;
        // }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            currentScene->Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void setCurrentScene(Scene* scene)
{
    delete currentScene;
    currentScene = scene;
}