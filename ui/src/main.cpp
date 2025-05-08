#include <Cell.h>
#include <raylib.h>

#undef RED
#undef GREEN
#undef BLUE
#undef YELLOW

#define R_RED (Color){ 230, 41, 55, 255 } 
#define R_GREEN (Color){ 0, 228, 48, 255 } 
#define R_YELLOW (Color){ 253, 249, 0, 255 }
#define R_BLUE (Color){ 0, 121, 241, 255 }

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

    InitWindow(screenWidth, screenHeight, "Bouncing Robots");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 20.0f, -15.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    Cell test = Cell(0, 0);
    test.setBorder(Border::SW);
    test.setTarget(Target(Shape::CROSS, RColor::MULTICOLOR));


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
        if (IsCursorHidden()) UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetScreenToWorldRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                            (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            }
            else collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                RenderCell(test);
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
    Vector3 cellPosition = (Vector3){ (float)currentCell.getX() + 7.5f, 0.5f, (float)currentCell.getY() - 7.5f};

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

        switch(target.getShape()) {
            case Shape::CROSS:
                DrawModel(crossModel, cellPosition, 1.0f, R_RED);
                break;
            case Shape::CIRCLE:
                DrawCylinder(cellPosition, 1.0f, 1.0f, 0.1f, 8, R_RED);
                break;
            case Shape::SQUARE:
                DrawCube(cellPosition, 1.0f, 0.1f, 1.0f, R_RED);
                break;
            case Shape::TRIANGLE:
                DrawModel(triModel, cellPosition, 1.0f, R_RED);
                break;
        }
    }
}