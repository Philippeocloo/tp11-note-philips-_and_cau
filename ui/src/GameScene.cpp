#include "GameScene.h"

#include <Board.h>

Vector3 operator+(Vector3 i, const Vector3 t) {
    return (Vector3){ i.x + t.x, i.y + t.y, i.z + t.z};
}

GameScene::GameScene(std::string players)
{
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 25.0f, -15.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    m_camera = camera;

    //Load models
    m_crossModel = LoadModel("res/cross.obj");
    m_triModel = LoadModel("res/tri.obj");

    //Creating board
    Board board = Board();
    board.placeAngles();

    m_supervisor.setBoard(board);
    m_robotRenderer.setRobots(m_supervisor.getBoard()->getRobots());
}

GameScene::~GameScene()
{

    UnloadModel(m_crossModel);
    UnloadModel(m_triModel);

}

void GameScene::Update(float deltaTime)
{
}

void GameScene::Render()
{
    BeginMode3D(m_camera);

        m_robotRenderer.render();
        Board* board = m_supervisor.getBoard();

        for (size_t x = 0; x < TAILLE_X; x++)
        {
            for (size_t y = 0; y < TAILLE_Y; y++)
            {
                RenderCell(board->getCell(x, y));
            }   
        }

        DrawGrid(16, 1.0f);

    EndMode3D();

    DrawFPS(10, 10);
}

/// @brief Renders a Cell
/// @details Renders the borders and target of a Cell at the correct coordinates (should only be called in 3d mode)
/// @param currentCell The cell that will be drawn
void GameScene::RenderCell(Cell& currentCell) {
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
                DrawModel(m_crossModel, cellPosition, 1.0f, drawColor);
                break;
            case Shape::CIRCLE:
                DrawCylinder(cellPosition, 0.5f, 0.5f, 0.1f, 8, drawColor);
                break;
            case Shape::SQUARE:
                DrawCube(cellPosition, 0.9f, 0.1f, 0.9f, drawColor);
                break;
            case Shape::TRIANGLE:
                DrawModel(m_triModel, cellPosition, 1.0f, drawColor);
                break;
        }
    }
}