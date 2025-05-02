#pragma once

#include "Shape.h"
#include "Color.h"

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
