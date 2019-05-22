#include "basictower.h"
#include <QPainter>

const QSize BasicTower::_fixedSize(77, 73);

BasicTower::BasicTower(QPoint pos, MainWindow *game, const QPixmap &picture)
    : _pos(pos)
    , _picture(picture)
    , _damage(99999)  //暂时99999
    , _attackRange(100)
    , _attackSpeed(1000)    //单位ms
    , _cost(0)
    , _hasShowRange(false)
    , _game(game)
{
}

BasicTower::~BasicTower()
{

}

QPoint BasicTower::getPos() const
{
    return this->_pos;
}

bool BasicTower::hasShowRange() const
{
    return this->_hasShowRange;
}

void BasicTower::setHasShowRange(bool hasShowRange)
{
    this->_hasShowRange = hasShowRange;
}

void BasicTower::drawRange(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    //draw attack rage
    painter->drawEllipse(this->_pos, this->_attackRange, this->_attackRange);

    painter->restore();
}

void BasicTower::draw(QPainter *painter) const
{
    painter->save();
//    painter->setPen(Qt::white);
    //draw attack rage
//    painter->drawEllipse(this->_pos, this->_attackRange, this->_attackRange);

    //translate coordinate
    const QPoint newPos(-this->_fixedSize.width() / 2, -this->_fixedSize.height() / 2);
    //draw tower
    painter->translate(this->_pos);
    painter->drawPixmap(newPos, this->_picture);
    //painter->drawPixmap(this->_pos, this->_picture);
    painter->restore();
}

