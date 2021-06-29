#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    root = new osg::Group;

    osg_widget = ui->openGLWidget;

    auto _mViewer = osg_widget->getViewer();

//    _mViewer = new osgViewer::Viewer;

//    osg::Cylinder* cylinder    = new osg::Cylinder( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f, 0.5f );
//    osg::ShapeDrawable* sd = new osg::ShapeDrawable( cylinder );
//    sd->setColor( osg::Vec4( 0.8f, 0.5f, 0.2f, 1.f ) );
//    osg::Geode* geode = new osg::Geode;
//    geode->addDrawable(sd);

    SplineControl* pl;
    pl = new SplineControl();

//    SplineControl* pl

    pl->path.points.push_back(Vec3Node(0, 0, 0));
    pl->path.points.push_back(Vec3Node(1000, 0, 0));
    pl->path.points.push_back(Vec3Node(1000, 1000, 0));
    pl->path.points.push_back(Vec3Node(0, 1000, 0));
    pl->path.points.push_back(Vec3Node(0, 1000, 1500));
    pl->path.points.push_back(Vec3Node(1500, 1000, 0));
    pl->path.points.push_back(Vec3Node(0, 0, 1000));
    pl->path.points.push_back(Vec3Node(0, 1000, 1800));


    osg::Vec3Array* v3a = new osg::Vec3Array();

    v3a->push_back({pl->path.points.at(v3a->size()).x, pl->path.points.at(v3a->size()).y, pl->path.points.at(v3a->size()).z});
    v3a->push_back({pl->path.points.at(v3a->size()).x, pl->path.points.at(v3a->size()).y, pl->path.points.at(v3a->size()).z});
    v3a->push_back({pl->path.points.at(v3a->size()).x, pl->path.points.at(v3a->size()).y, pl->path.points.at(v3a->size()).z});
    v3a->push_back({pl->path.points.at(v3a->size()).x, pl->path.points.at(v3a->size()).y, pl->path.points.at(v3a->size()).z});

//    root->addChild(drawLine(v3a));

    PaintBezier::paintCurveBezier(root.get(), pl);

//    gp->addChild(createBall(0, 0, 3));
//    gp->addChild(createBall(0, 5, 0));
//    MainObject mo(root.get());

    osg::Group* gp = new osg::Group;

    for(auto pos : pl->path.points)
    {
        gp->addChild(createBall(pos.x, pos.y, pos.z));
    }


    root->addChild(gp);

//    osg::Group* root = new osg::Group;

//    root->addChild(geode);

    osg_widget->setGeodeSc(root.get());


}

MainWindow::~MainWindow()
{

    delete ui;
}

