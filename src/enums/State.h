#pragma once

enum class State {
    INIT_PLAYERS     = 0,
    START_GAME       = 1,
    START_TOUR       = 2,
    WAIT_60SEC       = 3,
    PLAYER_PROPOSAL  = 4,
    END_60SEC        = 5,
    PLAYERS_TRIALS   = 6,
    END_TOUR         = 7,
    END_GAME         = 8,
};;