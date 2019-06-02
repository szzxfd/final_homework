#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &picture = QPixmap(":/image/tower_position.png"));
    void setHasTower(bool hasTower = true);
    bool hasTower() const;
    void setHasShow(bool hasShow = true);
    bool hasShow() const;
    bool inRange(const QPoint &pos) const;
    QPoint getPos();

    void draw(QPainter *painter) const;

private:
    bool _hasTower;
    bool _hasShow;
    QPoint _pos;
    QPixmap _picture;



    static const QSize _fixedSize;
};

#endif // TOWERPOSITION_H
