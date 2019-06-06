#include "magictower.h"
#include "basicbullet.h"
#include "mainwindow.h"



MagicTower::MagicTower(QPoint pos, MainWindow *game, const QPixmap &picture, const QSize fixedSize, int damage, int attackRange, int attackSpeed, int cost)
    :BasicTower(pos, game, picture, fixedSize, damage, attackRange, attackSpeed, cost)
{

}

MagicTower::~MagicTower()
{

}

void MagicTower::shootWeapon()
{
    BasicBullet *bullet = new BasicBullet(getPos(), _chosenEnemy->pos(), _damage, _chosenEnemy, _game);
    bullet->move();
    _game->addBullet(bullet);
}
