#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QTimer>

class WayPoint;
class QPainter;
class MainWindow;
class BasicTower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/enemy.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    QPoint pos() const;
//************************//
    void gotLostSight(BasicTower *attacker);
    void getAttacked(BasicTower *attacker);

    void slow(bool slowed = true);      //设置是否被减速
    bool showSlow() const;              //返回是否被减速

public slots:
    void doActivate();
    void recover();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    bool m_slowed = false;       //记录当前是否是减速状态
    QTimer * m_slowTimer;           //调整减速时间


    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    QList<BasicTower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;


};

#endif // ENEMY_H
