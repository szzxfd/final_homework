#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "basictower.h"
#include "magictower.h"
#include "enemy.h"
#include "basicbullet.h"
class WayPoint;
//class Enemy;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    //void awardGold(int gold);

//*****************************zcy Bullet *********************//
    void removedBullet(BasicBullet *bullet);
    void addBullet(BasicBullet *bullet);

//	AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

    void on_pushButton_clicked();

//private function
    //void on_label_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_2_clicked();

private:
    void loadTowerPosition();

    void addWayPoints();
    bool loadWave();
    void doGameOver();
    void preLoadWavesInfo();






private:
    Ui::MainWindow *ui;

    int						_waves;
    int						_playerHp;
    int						_playrGold;
    bool					_gameEnded;
    bool					_gameWin;
//	AudioPlayer *			m_audioPlayer;
    QList<QVariant>			_wavesInfo;

    QList<WayPoint *>		_wayPointsList;
    QList<Enemy *>			_enemyList;

    QList<TowerPosition>    _TowerPositionList;
    QList<BasicTower *>     _BasicTowerList;

//**************************************************************//
    QList<BasicBullet *>    _BulletList;

    int _towerType = 0;
};

#endif // MAINWINDOW_H
