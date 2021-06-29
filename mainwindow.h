#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osg/Material>
#include <QMouseEvent>

#include "draw.h"
#include "OsgQtWidget.h"
#include "PaintBezier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtOSGWidget *osg_widget;
    osg::ref_ptr<osg::Group> root;

    osg::Group * createBall(float x, float y, float z, float tamBall = 10)
    {

        osg::Group* root = new osg::Group;
        Draw draw;
        osg::Geode* c1 = draw.circles(0, 200, tamBall);
        osg::Geode* c2 = draw.circles(1, 200, tamBall);
        osg::Geode* c3 = draw.circles(2, 200, tamBall);



        osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform();
        trans->addChild(c1);
        trans->setMatrix(osg::Matrixd::translate( x, y, z));
        osg::ref_ptr<osg::MatrixTransform> trans2 = new osg::MatrixTransform();
        trans2->addChild(c2);
        trans2->setMatrix(osg::Matrixd::translate( x, y, z));
        osg::ref_ptr<osg::MatrixTransform> trans3 = new osg::MatrixTransform();
        trans3->addChild(c3);
        trans3->setMatrix(osg::Matrixd::translate( x, y, z));

        root->addChild(trans.get());
        root->addChild(trans2.get());
        root->addChild(trans3.get());

        return root;

    }
};
#endif // MAINWINDOW_H
