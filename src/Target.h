#pragma once

#include "enums/Shape.h"
#include "enums/Color.h"

class Target {
    
private:
    Shape m_shape;
    Color m_color;

public:
    Target();
    Target(Shape i_shape, Color i_color);

    Shape getShape() const;
    Color getColor() const;

    void setShape(Shape i_shape);
    void setColor(Color i_color);
};
