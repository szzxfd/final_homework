#include "basicbullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize BasicBullet::ms_fixedSize(8, 8);

BasicBullet::BasicBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *targetEnemy,
               MainWindow *game, const QPixmap &picture)
    : _startPos(startPos)
    , _targetPos(targetPoint)
    , _picture(picture)
    , _currentPos(startPos)
    , _targetEnemy(targetEnemy)
    , _game(game)
    , _damage(damage)
{

}

void BasicBullet::draw(QPainter *painter) const
{
    painter->drawPixmap(_currentPos, _picture);
}

void BasicBullet::move()
{
    // 300毫秒内击中敌人
    static const int duration = 300;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(_startPos);
    animation->setEndValue(_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void BasicBullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (_game->enemyList().indexOf(_targetEnemy) != -1) {   // Qlist::indexOf(A)  find A in the list
        _targetEnemy->getDamage(_damage);

        _targetEnemy->slow();       //被减速塔攻击时触发减速，每被攻击一次就刷新一次
    }
    _game->removedBullet(this);    
}

void BasicBullet::setCurrentPos(QPoint pos)
{
    _currentPos = pos;
}

QPoint BasicBullet::getCurrentPos() const
{
    return _currentPos;
}
