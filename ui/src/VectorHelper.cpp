#include "VectorHelper.h"

Vector3 operator+(Vector3 i, const Vector3 t) {
    return (Vector3){ i.x + t.x, i.y + t.y, i.z + t.z};
}