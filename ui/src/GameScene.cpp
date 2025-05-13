#include "GameScene.h"

#include <Board.h>

#include <raymath.h>

#include "VectorHelper.h"
#include "Consts.h"


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
    m_currentBoard = m_supervisor.getBoard();
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

//Returns true when the guess is validated
bool GameScene::PollGuess()
{
    //Check button presses
    int key = GetCharPressed();
    int phys_key = GetKeyPressed();

    //Key pressed is 0 -> 9 (https://en.wikipedia.org/wiki/List_of_Unicode_characters)
    if(key >= 48 && key <= 57 ) {
        //don't allow the guess to be 00
        if(m_currentGuess.length() == 0 && key == 48) {
            return false;
        } 

        //don't allow more solutions longer than 99 moves (just to avoid trolling)
        if(m_currentGuess.length() == 2) {
            return false;
        }
        m_currentGuess += key;
    }

    //if backspace is pressed
    if(phys_key == KEY_BACKSPACE) {
        if(m_currentGuess.length() > 0) {
            m_currentGuess.pop_back();
        }
    }

    //if enter is pressed
    if(phys_key == KEY_ENTER) {
        if(m_currentGuess.length() > 0) {
            return true;
        }
    }

    return false;
}

void GameScene::RenderCurrentTarget()
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

void GameScene::Update(float deltaTime)
{
    switch (m_supervisor.getActualState())
    {
    case State::START_TOUR:
    {
        m_playerBuzzing = getPlayerBuzzing();

        if(m_playerBuzzing == -1) {
            break;
        }

        //DEMANDER CHOIX
        m_currentGuess.clear();
        m_supervisor.changeState(State::PLAYER_PROPOSAL);
        /* code */
        break;
    }
    case State::PLAYER_PROPOSAL:
    {
        //if a guess has been made
        if(PollGuess()) {
            Player* p = &m_supervisor.getPlayers()[m_playerBuzzing];

            m_supervisor.announceNb(p, std::atoi(m_currentGuess.c_str()));

            //Clear guess for next player
            m_currentGuess.clear();
            m_supervisor.changeState(State::WAIT_60SEC);
        }
        break;
    }
    case State::WAIT_60SEC:
    {
        m_timer -= deltaTime;

        m_playerBuzzing = getPlayerBuzzing();

        if(m_playerBuzzing != -1) {
            Player* p = &m_supervisor.getPlayers()[m_playerBuzzing];

            //If the player hasn't already guessed
            if(!m_supervisor.getAnnouncedMoves().count(p)) {
                m_supervisor.changeState(State::PLAYER_PROPOSAL);
            }
        }

        if(m_timer <= 0.0f) {
            m_supervisor.changeState(State::END_60SEC);
        }

        break;
    }
    case State::END_60SEC:
    {
        m_supervisor.changeState(State::START_PLAYER_PROPOSAL);

        break;
    }
    case State::START_PLAYER_PROPOSAL:
        {
            Player* currentPlayer = m_supervisor.getSortedPlayers()[0];
            m_currentBoard = currentPlayer->getBoard();
            m_robotRenderer.setRobots(m_currentBoard->getRobots());

            m_supervisor.changeState(State::WAIT_FOR_MOVE);
            break;
        }
    case State::WAIT_FOR_MOVE:
        {
            SelectionInformation selection = m_robotRenderer.checkSelection();
            
            if(selection.selectedRobot != nullptr && selection.dir != Direction::NONE) {
                m_supervisor.setRobotDirection(std::pair(selection.selectedRobot, selection.dir));
                m_supervisor.changeState(State::MOVING_ROBOT);
            }
        }
    default:
        break;
    }

    //CHECK FOR BUZZ OF ANY PLAYER

}

void GameScene::Render()
{
    if(m_supervisor.getActualState() == State::WAIT_FOR_MOVE) {
        Player* currentPlayer = m_supervisor.getSortedPlayers()[0];
        
        std::string turnIndicator = "Tour de ";
        turnIndicator += currentPlayer->getLetter();
        std::string remaining = "Coups restants: ";
        remaining += std::to_string(m_supervisor.getAnnouncedMoves()[currentPlayer] - (m_supervisor.getRealMovementsCounter()[currentPlayer]));

        DrawText(turnIndicator.c_str(), WINDOW_SIZE_X/2-100, 40, 20, BLACK);
        DrawText(remaining.c_str(), WINDOW_SIZE_X/2-100, 65, 20, BLACK);
    }

    BeginMode3D(m_camera);

        m_robotRenderer.render();

        for (size_t x = 0; x < TAILLE_X; x++)
        {
            for (size_t y = 0; y < TAILLE_Y; y++)
            {
                RenderCell(m_currentBoard->getCell(x, y));
            }   
        }

        DrawGrid(16, 1.0f);

        switch (m_supervisor.getActualState())
        {
        case State::PLAYER_PROPOSAL:
        case State::START_TOUR:
        case State::WAIT_60SEC:
        
        case State::END_60SEC:
        case State::START_PLAYER_PROPOSAL:
        case State::WAIT_FOR_MOVE:
        case State::MOVING_ROBOT:
        case State::END_PLAYER_PROPOSAL:
        {
            RenderCurrentTarget();
        }
            break;
        default:
            break;
        }

    EndMode3D();

    //If player proposal state, draw the prompt
    if(m_supervisor.getActualState() == State::PLAYER_PROPOSAL) {
        Player& player = m_supervisor.getPlayers()[m_playerBuzzing];

        std::string prompt;
        prompt += player.getLetter();
        prompt += " propose : ";
        prompt += m_currentGuess;

        DrawText(prompt.c_str(), WINDOW_SIZE_X/2-60, WINDOW_SIZE_Y-40, 20, BLACK);
    }

    //If 60sec timer state, draw the remaining time
    if(m_supervisor.getActualState() == State::WAIT_60SEC) {
        std::string time;
        time += "Temps restant: ";
        time += std::to_string(m_timer);

        DrawText(time.c_str(), WINDOW_SIZE_X/2-100, 40, 20, BLACK);
    }

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