#pragma once

enum class State {
    INIT_PLAYERS          = 0,
    START_GAME            = 1,
    START_TOUR            = 2,
    WAIT_60SEC            = 3,
    PLAYER_PROPOSAL       = 5,
    END_60SEC             = 6,
    START_PLAYER_PROPOSAL = 7,
    WAIT_FOR_MOVE         = 8,
    MOVING_ROBOT          = 9,
    END_PLAYER_PROPOSAL   = 10,
    END_TOUR              = 11,
    END_GAME              = 12,
};
