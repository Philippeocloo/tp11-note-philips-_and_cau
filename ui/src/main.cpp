#include <Board.h>
#include <Cell.h>
#include <raylib.h>

#include "ColorConverter.h"

#include "RobotRenderer.h"

void RenderCell(Cell& currentCell);

Vector3 operator+(Vector3 i, const Vector3 t) {
    return (Vector3){ i.x + t.x, i.y + t.y, i.z + t.z};
}

Model crossModel;
Model triModel;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_WINDOW_HIGHDPI);

    InitWindow(screenWidth, screenHeight, "Robot's Game");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 25.0f, -15.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    // GAME INIT STUFF

    Cell test = Cell(1, 1);
    test.setBorder(Border::SW);

    Board board = Board();
    board.placeAngles();
    RobotRenderer robotRenderer = RobotRenderer(board.getRobots());

    //Load models
    crossModel = LoadModel("res/cross.obj");
    triModel = LoadModel("res/tri.obj");

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetScreenToWorldRay(GetMousePosition(), camera);

                // // Check collision between ray and box
                // collision = GetRayCollisionBox(ray,
                //             (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                //                           (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});

                //TODO: CHECK COLISIONS WITH ROBOTS
            }
            else collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                robotRenderer.render();

                for (size_t x = 0; x < TAILLE_X; x++)
                {
                    for (size_t y = 0; y < TAILLE_Y; y++)
                    {
                        RenderCell(board.getCell(x, y));
                    }
                    
                }

                DrawGrid(16, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


/// @brief Renders a Cell
/// @details Renders the borders and target of a Cell at the correct coordinates (should only be called in 3d mode)
/// @param currentCell The cell that will be drawn
void RenderCell(Cell& currentCell) {
    Vector3 cellPosition = (Vector3){ (float)(-currentCell.getX()) + 7.5f, 0.5f, (float)(currentCell.getY()) - 7.5f};

    //render the border
    switch (currentCell.getBorder())
    {
    case Border::NE:
        DrawCube(cellPosition + (Vector3){0, 0, 0.5f}, 1.0f, 1.0f, 0.1f, BLACK); //North
        DrawCube(cellPosition + (Vector3){-0.5f, 0, 0}, 0.1f, 1.0f, 1.0f, BLACK); //East
        break;
    case Border::NW:
        DrawCube(cellPosition + (Vector3){0, 0, 0.5f}, 1.0f, 1.0f, 0.1f, BLACK); //North
        DrawCube(cellPosition + (Vector3){0.5f, 0, 0}, 0.1f, 1.0f, 1.0f, BLACK); //West
        break;
    case Border::SE:
        DrawCube(cellPosition + (Vector3){0, 0, -0.5f}, 1.0f, 1.0f, 0.1f, BLACK); //South
        DrawCube(cellPosition + (Vector3){-0.5f, 0, 0}, 0.1f, 1.0f, 1.0f, BLACK); //East
        break;
    case Border::SW:
        DrawCube(cellPosition + (Vector3){0, 0, -0.5f}, 1.0f, 1.0f, 0.1f, BLACK); //South
        DrawCube(cellPosition + (Vector3){0.5f, 0, 0}, 0.1f, 1.0f, 1.0f, BLACK); //West
        break;
    default:
        break;
    }

    //render the target
    if(currentCell.hasTarget()) {
        Target target = currentCell.getTarget();
        Color drawColor = getColorFromRColor(target.getColor());
        switch(target.getShape()) {
            case Shape::CROSS:
                DrawModel(crossModel, cellPosition, 1.0f, drawColor);
                break;
            case Shape::CIRCLE:
                DrawCylinder(cellPosition, 0.5f, 0.5f, 0.1f, 8, drawColor);
                break;
            case Shape::SQUARE:
                DrawCube(cellPosition, 0.9f, 0.1f, 0.9f, drawColor);
                break;
            case Shape::TRIANGLE:
                DrawModel(triModel, cellPosition, 1.0f, drawColor);
                break;
        }
    }
}