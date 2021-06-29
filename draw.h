#ifndef DRAW_H
#define DRAW_H



#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Math>
#include <math.h>
#include <osgViewer/Viewer>
#include <osg/Geode>

#include <osg/Vec3>
#include <osg/Node>
#include <osg/Matrix>
#include <osg/FrameStamp>
#include <osg/Matrixd>

#include <osg/Transform>

#include <osg/MatrixTransform>

#include <osg/ValueMap>
#include <osg/ValueStack>
#include <osg/NodeVisitor>
#include <osg/Vec3f>

#include <osgAnimation/Animation>

class Draw
{
public:
    Draw(){};

    osg::Vec3Array*
    circleVerts( int plane, int approx, float radius )
    {
        const double angle( osg::PI * 2. / (double) approx );
        osg::Vec3Array* v = new osg::Vec3Array;
        int idx, count;
        double x(0.), y(0.), z(0.);
        double height;
        double original_radius = radius;

    for(count = 0; count <= approx/4; count++)
    {
        height = original_radius*sin(count*angle);
        radius = cos(count*angle)*radius;


        switch(plane)
        {
        case 0: // X
            x = height;
        break;
        case 1: //Y
            y = height;
        break;
        case 2: //Z
            z = height;
        break;
        }



    for( idx=0; idx<approx; idx++)
    {
        double cosAngle = cos(idx*angle);
        double sinAngle = sin(idx*angle);
        switch (plane)
        {
        case 0: // X
            y = radius*cosAngle;
            z = radius*sinAngle;
        break;
        case 1: // Y
            x = radius*cosAngle;
            z = radius*sinAngle;
        break;
        case 2: // Z
            x = radius*cosAngle;
            y = radius*sinAngle;
        break;
        }
        v->push_back( osg::Vec3( x, y, z ) );
    }
    }
    return v;
    }

    osg::Geode*
    circles( int plane, int approx, float radius )
    {
    osg::Geode* geode = new osg::Geode;
    osg::LineWidth* lw = new osg::LineWidth( 1. );
    geode->getOrCreateStateSet()->setAttributeAndModes( lw,
    osg::StateAttribute::ON );

    osg::Geometry* geom = new osg::Geometry;
    osg::Vec3Array* v = circleVerts( plane, approx, radius );
    geom->setVertexArray( v );

    osg::Vec4Array* c = new osg::Vec4Array;
    c->push_back( osg::Vec4( 1., 1., 1., 1. ) );
    geom->setColorArray( c );
    geom->setColorBinding( osg::Geometry::BIND_OVERALL );
    geom->addPrimitiveSet( new osg::DrawArrays( GL_LINE_LOOP, 0, approx ) );
    osg::StateSet* state = geode->getOrCreateStateSet();
    state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->addDrawable( geom );




    return geode;
    }
};



#endif // DRAW_H
