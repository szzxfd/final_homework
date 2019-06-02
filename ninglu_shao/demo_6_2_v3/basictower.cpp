
#include "basictower.h"
#include "basicbullet.h"
#include "mainwindow.h"
#include "enemy.h"
#include "utility.h"
#include <QPainter>

const QSize BasicTower::_fixedSize(77, 73);

BasicTower::BasicTower(QPoint pos, MainWindow *game, const QPixmap &picture)
    : _pos(pos)
    , _picture(picture)
    , _damage(1000)  //暂时99999
    , _attackRange(100)
    , _attackSpeed(1000)    //单位ms
    , _cost(0)
    , _hasShowRange(false)
    , _game(game)
    , _chosenEnemy(NULL)
{

//****************************  zcy Bullet  ************//
    _shootTimer = new QTimer(this);
    connect(_shootTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));

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
    painter->setRenderHint(QPainter::Antialiasing, true);//抗锯齿
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


//************************** zcy Bullet ****************//

void BasicTower::shootWeapon()
{
    BasicBullet *bullet = new BasicBullet(_pos, _chosenEnemy->pos(), _damage, _chosenEnemy, _game);
    bullet -> move();
    _game -> addBullet(bullet);
}


void BasicTower::attackEnemy()
{
    _shootTimer->start(500);
}

void BasicTower::checkEnemyInRange()
{
    if (_chosenEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        /*
        QVector2D normalized(_chosenEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;
*/
        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(_pos, _attackRange, _chosenEnemy->pos(), 1))

            lostSightOfEnemy();


    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<Enemy *> enemyList = _game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(_pos, _attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }

   // Q_ASSERT(_chosenEnemy == NULL);   //用来debug的
}


void BasicTower::lostSightOfEnemy()
{
    _chosenEnemy->gotLostSight(this);
    if (_chosenEnemy)
        _chosenEnemy = NULL;

    _shootTimer->stop();
  //  Q_ASSERT(_chosenEnemy == NULL);
    //m_rotationSprite = 0.0;
}

void BasicTower::chooseEnemyForAttack(Enemy *enemy)
{
    _chosenEnemy = enemy;
    attackEnemy();
    _chosenEnemy->getAttacked(this);
}

void BasicTower::targetKilled()
{
    if(_chosenEnemy)
        _chosenEnemy = NULL;

    _shootTimer->stop();
}



