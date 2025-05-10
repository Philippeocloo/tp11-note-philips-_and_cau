#pragma once

#include "enums/Shape.h"
#include "enums/Color.h"

class Target {
    
private:
    Shape m_shape;
    RColor m_color;

public:
    Target();
    Target(Shape i_shape, RColor i_color);

    ~Target() = default;

    Shape getShape() const;
    RColor getColor() const;

    void setShape(Shape i_shape);
    void setColor(RColor i_color);

    bool operator==(const Target& other) const;
};
