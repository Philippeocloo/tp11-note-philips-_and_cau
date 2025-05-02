#pragma once

#include <vector>
#include <iostream>

#include "enums/Border.h"
#include "Target.h"

class Case {
private:
    int m_x;
    int m_y;
    Border m_border;
    Target m_target;

public:
    Case() : m_x(0), m_y(0) {};
    Case(int m_x, int m_y);

    void setBorder(Border m_border);
    Target getTarget();
};
