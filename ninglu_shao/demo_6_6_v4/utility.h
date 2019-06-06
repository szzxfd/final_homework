#ifndef UTILITY_H
#define UTILITY_H

#include <QPoint>
#include <cmath>

inline bool collisionWithCircle(QPoint point_1, double radius_1, QPoint point_2, double radius_2)
{
    const double deltaX = point_1.x() - point_2.x();
    const double deltaY = point_1.y() - point_2.y();
    const double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if(distance < radius_1 + radius_2)
        return true;

    return false;
}

#endif // UTILITY_H
