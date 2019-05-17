#ifndef BASICTOWER_H
#define BASICTOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
class MainWindow;

class BasicTower : public QObject
{
    Q_OBJECT
public:
    BasicTower(QPoint pos, MainWindow *game, const QPixmap &picture = QPixmap(":/image/basic_tower.png"));
    ~BasicTower();
    QPoint getPos() const;
    bool hasShowRange() const;
    void setHasShowRange(bool hasShowRange = true);

    void drawRange(QPainter *painter) const;
    void draw(QPainter *painter) const;

signals:

public slots:

private:
    //bool _attacking;
    int _damage;
    int _attackRange;
    int _attackSpeed;
    int _cost;
    bool _hasShowRange;

    MainWindow * _game;     //后期与enemy的接口

    QPoint _pos;
    QPixmap _picture;

    static const QSize _fixedSize;
};

#endif // BASICTOWER_H
