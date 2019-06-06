#ifndef BASICBULLET_H
#define BASICBULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPainter>

//class QPainter;
class Enemy;
class MainWindow;

class BasicBullet :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ getCurrentPos WRITE setCurrentPos)

public:
    BasicBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &picture = QPixmap(":/image/bullet/image 2410.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint getCurrentPos() const;

private slots:
    void hitTarget();



private:
    const QPoint _startPos;
    const QPoint _targetPos;
    const QPixmap _picture;
    QPoint _currentPos;
    Enemy *	_targetEnemy;
    MainWindow * _game;
    int	_damage;

    static const QSize ms_fixedSize;
};



#endif // BASICBULLET_H
