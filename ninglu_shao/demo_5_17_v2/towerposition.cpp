#include "towerposition.h"
#include <QPainter>

const QSize TowerPosition::_fixedSize(72, 46);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &picture)
    : _hasTower(false)
    , _hasShow(false)
    , _pos(pos)
    , _picture(picture)
{
}

void TowerPosition::setHasTower(bool hasTower)
{
    this->_hasTower = hasTower;
}

bool TowerPosition::hasTower() const
{
    return this->_hasTower;
}

bool TowerPosition::hasShow() const
{
    return this->_hasShow;
}

void TowerPosition::setHasShow(bool hasShow)
{
    this->_hasShow = hasShow;
}

bool TowerPosition::inRange(const QPoint &pos) const
{
    bool inX = (this->_pos.x() < pos.x()) && (pos.x() < this->_pos.x() + _fixedSize.width());
    bool inY = (this->_pos.y() < pos.y()) && (pos.y() < this->_pos.y() + _fixedSize.height());
    return inX && inY;
}

QPoint TowerPosition::getPos()
{
    //常数是为了完全覆盖，后期把它改成选择防御塔类型后会显示，不选择时会消失
    QPoint centrePos(this->_pos.x() + this->_fixedSize.width() / 2 - 3, this->_pos.y() + this->_fixedSize.height() / 2 - 20);
    return centrePos;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(this->_pos, this->_picture);
}

