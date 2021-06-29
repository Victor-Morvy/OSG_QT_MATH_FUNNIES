#ifndef PAINTBEZIER_H
#define PAINTBEZIER_H



#include <osg/Camera>
#include <osg/Drawable>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/Object>
#include <osg/PrimitiveSet>
#include <osg/Program>
#include <osg/Shader>
#include <osg/StateSet>
#include <osg/Transform>
#include <osg/Uniform>
#include <osgViewer/Viewer>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>

#include "mathfunies.h"
//#include "draw.h"

#include <QtCore>
#include <QTimer>
#include <QCoreApplication>
//#include "fixedupdate.h"

//#include <mainobject.h>

struct ModelViewProjectionMatrixCallback: public osg::Uniform::Callback
{


    ModelViewProjectionMatrixCallback(osg::Camera* camera) :
            _camera(camera) {
    }

    virtual void operator()(osg::Uniform* uniform, osg::NodeVisitor* nv) {
        osg::Matrixd viewMatrix = _camera->getViewMatrix();
        osg::Matrixd modelMatrix = osg::computeLocalToWorld(nv->getNodePath());
        osg::Matrixd modelViewProjectionMatrix = modelMatrix * viewMatrix * _camera->getProjectionMatrix();
        uniform->set(modelViewProjectionMatrix);
    }

    osg::Camera* _camera;
};

struct ViewportCallback: public osg::Uniform::Callback
{
    ViewportCallback(osg::Camera* camera) :
            _camera(camera) {
    }

    virtual void operator()(osg::Uniform* uniform, osg::NodeVisitor* /*nv*/) {
        const osg::Viewport* viewport = _camera->getViewport();
        osg::Vec2f viewportVector = osg::Vec2f(viewport->width(), viewport->height());
        uniform->set(viewportVector);
    }

    osg::Camera* _camera;
};

const int OSG_WIDTH = 1280;
const int OSG_HEIGHT = 960;

class PaintBezier
{
public:

    PaintBezier(){}

static    osg::Node* drawLine(Vec3Node from, Vec3Node to, float size = 2.f)
    {


        osg::Vec3Array* vertices = new osg::Vec3Array;
        osg::Vec4Array* colors = new osg::Vec4Array;

        vertices->setName("Vertex");
        vertices->push_back(osg::Vec3f(from.x,from.y,from.z));
        vertices->push_back(osg::Vec3f(to.x,to.y,to.z));

        colors->push_back(osg::Vec4(1,0.3,0,1));

        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
        geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vertices->size()));
        geom->setUseDisplayList(false);

        geom->setVertexArray(vertices);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        geode->addDrawable(geom.get());

        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        state->setMode(GL_BLEND, osg::StateAttribute::ON);
        state->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
        osg::LineWidth* lw = new osg::LineWidth;
        lw->setWidth(size);
        state->setAttribute(lw, osg::StateAttribute::ON);
        osg::BlendFunc* blendfunc = new osg::BlendFunc();
        state->setAttributeAndModes(blendfunc, osg::StateAttribute::ON);

        return geode.release();
    }

static    osg::Node* drawLine(osg::Vec3Array* points, float size = 2.f)
    {
        osg::Vec3Array* vertices = points;
        osg::Vec4Array* colors = new osg::Vec4Array;

        vertices->setName("Vertex");
    //    vertices->push_back(osg::Vec3f(from.x,from.y,from.z));
    //    vertices->push_back(osg::Vec3f(to.x,to.y,to.z));

        colors->push_back(osg::Vec4(1,0.3,0,1));

        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
        geom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, vertices->size()));
        geom->setUseDisplayList(false);

        geom->setVertexArray(vertices);
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        geode->addDrawable(geom.get());

        osg::StateSet* state = geode->getOrCreateStateSet();
        state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        state->setMode(GL_BLEND, osg::StateAttribute::ON);
        state->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
        osg::LineWidth* lw = new osg::LineWidth;
        lw->setWidth(size);
        state->setAttribute(lw, osg::StateAttribute::ON);
        osg::BlendFunc* blendfunc = new osg::BlendFunc();
        state->setAttributeAndModes(blendfunc, osg::StateAttribute::ON);

        return geode.release();
    }

static    void paintCurveBezier(osg::ref_ptr<osg::Node> root, SplineControl* pl, int segmentPoints = 8)
    {

    //    int totalSize = 0;
    //    drawLine({-0.5, 0}, {0.5, 0.5});

    //    qDebug() << "\n///////////////////////" ;


        float size = (float)pl->path.points.size();

        float val = 1.f/segmentPoints;


        osg::Vec3Array* v3a = new osg::Vec3Array();


        for(float t = 0; t < size - 0.01; t += val)
        {
            Vec3Node pos;
            pos = pl->path.GetSplinePoint(t, true);

            v3a->push_back({pos.x/2, pos.y/2, pos.z/2});

        }
        v3a->push_back({pl->path.GetSplinePoint(0, true).x,
                        pl->path.GetSplinePoint(0, true).y,
                        pl->path.GetSplinePoint(0, true).z});

        root->asGroup()->addChild(drawLine(v3a));
    }
};
#endif // PAINTBEZIER_H
