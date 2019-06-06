#ifndef BASICTOWER_H
#define BASICTOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QTimer>
#include "enemy.h"
class MainWindow;


class BasicTower : public QObject
{
    Q_OBJECT
public:
    //BasicTower(QPoint pos, MainWindow *game, const QPixmap &picture = QPixmap(":/image/basic_tower.png"));
    BasicTower(QPoint pos, MainWindow *game,
         const QPixmap &picture = QPixmap(":/image/basic_tower.png"), const QSize fixedSize = QSize(77, 73),
         int damage = 1, int attackRange = 100, int attackSpeed = 1000, int cost = 0);  //ms
    virtual ~BasicTower();
    QPoint getPos() const;
    bool hasShowRange() const;
    void setHasShowRange(bool hasShowRange = true);

    void attackEnemy();
    void checkEnemyInRange();
    void lostSightOfEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void targetKilled();

    void drawRange(QPainter *painter) const;
    void draw(QPainter *painter) const;

signals:

public slots:

//************************** zcy Bullet ***********************//
private slots:
    virtual void shootWeapon();

private:

//***********  zcy Bullet ************//

    QTimer * _shootTimer;

    QPoint _pos;
    QPixmap _picture;


    const QSize _fixedSize;

    //bool _attacking;

    int _attackRange;
    int _attackSpeed;
    int _cost;
    bool _hasShowRange;

protected:  
    int _damage;
    MainWindow * _game;     //后期与enemy的接口
    Enemy * _chosenEnemy;
};

#endif // BASICTOWER_H
