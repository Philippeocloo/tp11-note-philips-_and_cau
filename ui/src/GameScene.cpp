#include "GameScene.h"

#include <Board.h>

#include <raymath.h>

#include "VectorHelper.h"


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

    m_supervisor.initPlayers(players);
    m_supervisor.changeState(State::START_TOUR);
    m_robotRenderer.setRobots(m_supervisor.getBoard()->getRobots());
    m_robotRenderer.setCamera(&m_camera);
}

GameScene::~GameScene()
{

    UnloadModel(m_crossModel);
    UnloadModel(m_triModel);

}


int GameScene::getPlayerBuzzing()
{
    //Check button presses
    int key = GetCharPressed();

    //Key pressed is A -> Z (https://en.wikipedia.org/wiki/List_of_Unicode_characters)
    if(key >= 97 && key <= 122 ) {
        for (size_t i = 0; i < m_supervisor.getPlayers().size(); i++)
        {
            Player& p = m_supervisor.getPlayers()[i];
            std::cout << p.getLetter() << "  " << key << std::endl;
            if(key == p.getLetter()) {
                return i;
            }
        }
    }

    return -1;
}

void GameScene::Update(float deltaTime)
{
    switch (m_supervisor.getActualState())
    {
    case State::START_TOUR:
    {
        m_robotRenderer.checkSelection();
        int buzzPlayer = getPlayerBuzzing();

        if(buzzPlayer == -1) {
            break;
        }

        std::cout << "youhou" << std::endl;
        //DEMANDER CHOIX
        m_supervisor.changeState(State::PLAYER_PROPOSAL);
        /* code */
        break;
    }
    default:
        break;
    }

    //CHECK FOR BUZZ OF ANY PLAYER

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

        switch (m_supervisor.getActualState())
        {
        case State::START_TOUR:
        case State::WAIT_60SEC:
        case State::PLAYER_PROPOSAL:
        case State::END_60SEC:
        case State::START_PLAYER_PROPOSAL:
        case State:: MOVING_ROBOT:
        case State::END_PLAYER_PROPOSAL:
        {
            Target* target = m_supervisor.getCurrentTarget();
            Color drawColor = getColorFromRColor(target->getColor());

            Vector3 pos = {0.0f, 1.0f, 0.0f};

            switch(target->getShape()) {
                case Shape::CROSS:
                    DrawModel(m_crossModel, pos, 1.0f, drawColor);
                    break;
                case Shape::CIRCLE:
                    DrawCylinder(pos, 0.5f, 0.5f, 0.1f, 8, drawColor);
                    break;
                case Shape::SQUARE:
                    DrawCube(pos, 0.9f, 0.1f, 0.9f, drawColor);
                    break;
                case Shape::TRIANGLE:
                    DrawModel(m_triModel, pos, 1.0f, drawColor);
                    break;
            }
        }
            break;
        default:
            break;
        }

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
        Target* target = currentCell.getTarget();
        Color drawColor = getColorFromRColor(target->getColor());
        switch(target->getShape()) {
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