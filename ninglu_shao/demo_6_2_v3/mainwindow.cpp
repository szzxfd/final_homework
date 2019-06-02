#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QXmlStreamReader>
#include <qmessagebox>
#include <QtGlobal>
#include "waypoint.h"
#include "pListReader.h"
#include "enemy.h"
#include "basicbullet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _waves(0)
    , _playerHp(4)    //暂时4点血
    , _playrGold(99999) //无敌
    , _gameEnded(false)
    , _gameWin(false)
{
    ui->setupUi(this);

    loadTowerPosition();

    preLoadWavesInfo();
    addWayPoints();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    //设置300ms后启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTowerPosition()
{
    QPoint pos[] =
    {
        //写一大堆点，maybe以后会用xml
        //first line
        QPoint(130, 100),
        QPoint(230, 100),
        QPoint(400, 100),
        QPoint(500, 100),
        //second line
        QPoint(140, 215),
        QPoint(240, 215),
        QPoint(390, 215),
        QPoint(490, 215),
        //third line
        QPoint(80, 320),
        QPoint(230, 320),
        QPoint(315, 320),
        QPoint(400, 320),
        QPoint(540, 320),
        //fourth line
        QPoint(225, 445),
        QPoint(405, 445)
    };
    int num = sizeof(pos) / sizeof(pos[0]);

    for(int i = 0; i < num; ++ i)
        this->_TowerPositionList.push_back(TowerPosition(pos[i]));
    //update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //下面是有关游戏胜利or游戏失败
    if(_gameEnded || _gameWin)
    {
        QString text = _gameEnded ? "Game Over!" : "You Win!";
        QPainter painter(this);
        painter.setPen((QPen(Qt::black)));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    //下面是加载地图
    QPixmap map_1(":/image/map_1.bmp");

    QPainter mapPainter(&map_1);
    for(auto &towerPosition: this->_TowerPositionList)
    {
        if(towerPosition.hasShow())
            towerPosition.draw(&mapPainter);
    }
    for(auto &basicTower: this->_BasicTowerList)
    {
        basicTower->draw(&mapPainter);
        if(basicTower->hasShowRange())
            basicTower->drawRange(&mapPainter);
    }
    for(auto &enemy: this->_enemyList)
    {
        enemy->draw(&mapPainter);
    }

//************** zcy bullet ***********//
    for(auto &bullet: this->_BulletList)
    {
        bullet->draw(&mapPainter);
    }

/*
    WayPoint *p = new WayPoint(QPoint(500, 500));
    Enemy *target = new Enemy(p, this);

    BasicBullet *bullet1 = new BasicBullet(QPoint(200,200), QPoint(400, 400), 3,target, this);
    bullet1->draw(&mapPainter);

*/

    QPainter painter(this);
    painter.drawPixmap(0, 0, map_1);


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();

    //正经实现基类的放置
    auto curPos = _TowerPositionList.begin();
    while(curPos != _TowerPositionList.end())
    {
        if(curPos->hasShow() && curPos->inRange(pressPos) && !curPos->hasTower())  //以后要添加金币条件
        {
            curPos->setHasTower();
            BasicTower *tower = new BasicTower(curPos->getPos(), this);
            this->_BasicTowerList.push_back(tower);
            update();
            break;
        }
        if(curPos->hasTower() && curPos->inRange(pressPos))
        {
            for(auto &it: this->_BasicTowerList)
            {
                if(it->getPos() == curPos->getPos())
                {
                    if(!it->hasShowRange())
                        it->setHasShowRange();
                    else
                        it->setHasShowRange(false);
                    update();
                    break;
                }
            }
        }

        ++ curPos;
    }
    //鼠标恢复
    this->setCursor(Qt::ArrowCursor);

    //位点变暗
    for(auto &temp: this->_TowerPositionList)
    {
        temp.setHasShow(false);
    }

    /*
     *写着玩的（0.0）
    BasicTower *tower = new BasicTower(pressPos, this);
    this->_BasicTowerList.push_back(tower);
    update();
    */
}



void MainWindow::on_pushButton_clicked()
{
    //改变鼠标形状
    QCursor *myCursor = new QCursor(QPixmap(":/image/move_basic_tower.png"),-1,-1);
    this->setCursor(*myCursor);

    for(auto &temp: this->_TowerPositionList)
    {
        temp.setHasShow();
        update();
    }
}

void MainWindow::getHpDamage(int damage)
{
    //音频相关
    //audioplayer->playSound();
    this->_playerHp -= damage;
    if(this->_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    _enemyList.removeOne(enemy);
    delete enemy;

    if (_enemyList.empty())
    {
        ++ _waves;
        if (!loadWave())
        {
            _gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
/*
void MainWindow::awardGold(int gold)
{
    _playrGold += gold;
    update();
}
*/

QList<Enemy *> MainWindow::enemyList() const
{
    return this->_enemyList;
}

void MainWindow::addWayPoints()
{
    WayPoint *wayPoint11 = new WayPoint(QPoint(340, 650));
    _wayPointsList.push_back(wayPoint11);
    WayPoint *wayPoint10 = new WayPoint(QPoint(340, 500));
    _wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint11);
    WayPoint *wayPoint112= new WayPoint(QPoint(300, 390));
    _wayPointsList.push_back(wayPoint112);

    wayPoint112->setNextWayPoint(wayPoint10);
    WayPoint *wayPoint1 = new WayPoint(QPoint(200, 390));
    _wayPointsList.push_back(wayPoint1);
    wayPoint1->setNextWayPoint(wayPoint112);
    WayPoint *wayPoint21 = new WayPoint(QPoint(170, 330));
    _wayPointsList.push_back(wayPoint21);
    wayPoint21->setNextWayPoint(wayPoint1);
    WayPoint *wayPoint2 = new WayPoint(QPoint(150, 300));
    _wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint21);
    WayPoint *wayPoint3 = new WayPoint(QPoint(110, 260));
    _wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);
    WayPoint *wayPoint43 = new WayPoint(QPoint(110, 220));
    _wayPointsList.push_back(wayPoint43);
    wayPoint43->setNextWayPoint(wayPoint3);
    WayPoint *wayPoint4 = new WayPoint(QPoint(120, 200));
    _wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint43);
    WayPoint *wayPoint412 = new WayPoint(QPoint(150, 190));
    _wayPointsList.push_back(wayPoint412);
    wayPoint412->setNextWayPoint(wayPoint4);
    WayPoint *wayPoint41 = new WayPoint(QPoint(200, 180));
    _wayPointsList.push_back(wayPoint41);
    wayPoint41->setNextWayPoint(wayPoint412);
    WayPoint *wayPoint5 = new WayPoint(QPoint(320, 160));
    _wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint41);
    WayPoint *wayPoint6 = new WayPoint(QPoint(340, 80));
    _wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);
}

bool MainWindow::loadWave()
{
    if (_waves >= _wavesInfo.size())
        return false;
    WayPoint *startWayPoint = _wayPointsList.back();
    QList<QVariant> curWavesInfo = _wavesInfo[_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++ i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();
        Enemy *enemy = new Enemy(startWayPoint, this);
        _enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

void MainWindow::doGameOver()
{
    if (!_gameEnded)
    {
        _gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void MainWindow::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    _wavesInfo = reader.data();

    file.close();
}

void MainWindow::updateMap()
{
    //foreach (Enemy *enemy, _enemyList)
    //    enemy->move();
    for(auto &enemy: this->_enemyList)
        enemy->move();
    //增加塔的更新
    for(auto &tower: this->_BasicTowerList)
        tower->checkEnemyInRange();

    update();
}

void MainWindow::gameStart()
{
    loadWave();
}


//******************************************//
// zcy's Bullet part //
void MainWindow::removedBullet(BasicBullet *bullet)
{
   //Q_ASSERT(bullet);

   if (this->_BulletList.indexOf(bullet) != -1)   // Qlist::indexOf(A)  find A in the list

       _BulletList.removeOne(bullet);
   delete bullet;
}


void MainWindow::addBullet(BasicBullet *bullet)
{
   Q_ASSERT(bullet);
   _BulletList.push_back(bullet);
}
