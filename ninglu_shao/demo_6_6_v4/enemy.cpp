#include "enemy.h"
#include "waypoint.h"
#include "utility.h"
#include "mainwindow.h"
//#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 50;

const QSize Enemy::ms_fixedSize(74, 62);

Enemy::Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)
    : QObject(0)
    , m_active(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , m_walkingSpeed(3)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
{
    m_slowTimer = new QTimer(this);
    connect(m_slowTimer, SIGNAL(timeout()), this, SLOT(recover()));
}

Enemy::~Enemy()
{
//	m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();

    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    qreal movementSpeed = m_walkingSpeed;
//    if(this->m_slowed)
//        movementSpeed = 1;
//    else
//        movementSpeed = m_walkingSpeed;

    // 向量标准化
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    if(!showSlow())
        m_pos += normalized.toPoint() * movementSpeed;
    else
        m_pos += normalized.toPoint() * 1;
}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();//保存当前状态

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 9 - 9, -ms_fixedSize.height() / 2);
     //绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::yellow);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 3));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void Enemy::getRemoved()
{
    if(m_attackedTowersList.empty())
        return;
    for(auto &attacker: m_attackedTowersList)
        attacker->targetKilled();

    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{
    //m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
        //m_game->audioPlayer()->playSound(EnemyDestorySound);
        //m_game->awardGold(200);
        getRemoved();
    }
}

QPoint Enemy::pos() const
{
    return m_pos;
}
//下补充敌人受到攻击；与塔联系


// ********************  zcy Bullet   or may be attack ??? *************//

void Enemy::gotLostSight(BasicTower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

void Enemy::getAttacked(BasicTower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}
//减速相关
void Enemy::slow(bool slowed)   //更改状态
{
    this->m_slowed = slowed;
    m_slowTimer->start(1000);//just test
}

bool Enemy::showSlow() const
{
    return this->m_slowed;
}

void Enemy::recover()   //从减速状态恢复
{
    if(showSlow())
        slow(false);
    m_slowTimer->stop();
}
