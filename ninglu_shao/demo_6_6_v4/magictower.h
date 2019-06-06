#ifndef MAGICTOWER_H
#define MAGICTOWER_H
#include "basictower.h"

class MagicTower : public BasicTower
{
public:
    MagicTower(QPoint pos, MainWindow *game,
               const QPixmap &picture = QPixmap(":/image/magic_tower.png"), const QSize fixedSize = QSize(85, 80),
               int damage = 1, int attackRange = 100, int attackSpeed = 1000, int cost = 0);  //ms
    ~MagicTower();

private slots:
    void shootWeapon();
};
#endif // MAGICTOWER_H
