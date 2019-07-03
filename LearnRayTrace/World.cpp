#include "stdafx.h"
#include "World.h"
#include "BoundingBox.h"
#include "Checker.h"
#include "Cylinder.h"
#include "Emissive.h"
#include "GlossyReflector.h"
#include "Material.h"
#include "Matte.h"
#include "MeshObject.h"
#include "PerfectReflect.h"
#include "Plane.h"
#include "Ray.h"
#include "ShadeInfo.h"
#include "Sphere.h"
#include "Acceleration.h"

#define MATERIAL Matte

World::World() : camera_( *this ) {
    max_depth_ = 2;
    buildScene2();
}

World::~World() {}

//--------------------------------------------------Y 向上， 右手
void World::buildScene1() {
    Plane* plane = nullptr;

    plane            = new Plane( Vec3( 0, 2, 0 ), Vec3( 0, -1, 0 ) );  //上
    plane->_material = new MATERIAL( g::Cyan );
    shapes_.push_back( plane );

    plane            = new Plane( Vec3( 0, 2 - 1e-5, 0 ), Vec3( 0, -1, 0 ) );  //灯
    plane->_material = new Emissive;
    plane->x_min = -.5, plane->x_max = .5;
    plane->z_min = -5, plane->z_max = -4;
    shapes_.push_back( plane );

    plane            = new Plane( Vec3( 0, -2, 0 ), Vec3( 0, 1, 0 ) );  //下
    plane->_material = new MATERIAL( g::Blue );
    shapes_.push_back( plane );

    plane            = new Plane( Vec3( -2, 0, 0 ), Vec3( 1, 0, 0 ) );  //左
    plane->_material = new MATERIAL( g::Green );
    shapes_.push_back( plane );

    plane            = new Plane( Vec3( 0, 0, -6 ), Vec3( 0, 0, 1 ) );  //后
    plane->_material = new MATERIAL( g::Yellow );
    shapes_.push_back( plane );

    plane            = new Plane( Vec3( 2, 0, 0 ), Vec3( -1, 0, 0 ) );  //右
    plane->_material = new MATERIAL( g::Cyan );
    shapes_.push_back( plane );

    //--------------------------------------------------Sphere
    Sphere* sphere    = new Sphere( Vec3( 0, -1.5, -5 ), .5 );
    sphere->_material = new MATERIAL( g::Red );
    shapes_.push_back( sphere );

    sphere            = new Sphere( Vec3( -1, -1.5, -5 ), .5 );
    sphere->_material = new MATERIAL( g::Red );
    shapes_.push_back( sphere );

    sphere            = new Sphere( Vec3( 1, -1.5, -5 ), .5 );
    sphere->_material = new MATERIAL( g::Red );
    shapes_.push_back( sphere );

    sphere            = new Sphere( Vec3( 0, -1.5, -4 ), .5 );
    sphere->_material = new MATERIAL( g::Yellow );
    shapes_.push_back( sphere );
}

//--------------------------------------------------Y 向上， 右手
void World::buildScene2() {
    Plane* plane = nullptr;

    plane            = new Plane( Vec3( 0, -25, 0 ), Vec3( 0, 1, 0 ) );
    plane->_material = new Checker();
    //shapes_.push_back(plane);

    //--------------------------------------------------Sphere
    Shape* shape = new Sphere( Vec3( 0, -1.5, -11 ), .5 );
    // shape->_material = new MATERIAL(g::Red);
    //_shapes.push_back(shape);

    // shape = new Sphere(Vec3(-1, -1.5, -10), .5);
    // shape->_material = new MATERIAL(g::Red);
    //_shapes.push_back(shape);

    // shape = new Sphere(Vec3(1, -1.5, -9), .5);
    // shape->_material = new MATERIAL(g::Red);
    //_shapes.push_back(shape);

    // shape = new Sphere(Vec3(0, -1.5, -8), .5);
    // shape->_material = new MATERIAL(g::Yellow);
    //_shapes.push_back(shape);

	int i = 1;
	for (i = 0; i < 2; i++)
	{
		{
			MeshObject* bunny = new MeshObject("../bunny.obj");
			bunny->offset = Vec3(-10, -10, -40 + i * 2);
			bunny->magnify = 50;
			bunny->_material = new MATERIAL(g::Blue);
			shapes_.push_back(bunny);
		}

		{
			MeshObject* bunny = new MeshObject("../bunny.obj");
			bunny->offset = Vec3(0, -10, -40 + i * 3);
			bunny->magnify = 50;
			bunny->_material = new MATERIAL(g::Blue);
			shapes_.push_back(bunny);
		}

		{
			MeshObject* bunny = new MeshObject("../bunny.obj");
			bunny->offset = Vec3(10, -10, -40 + i);
			bunny->magnify = 50;
			bunny->_material = new MATERIAL(g::Blue);
			shapes_.push_back(bunny);
		}
	}

}

ShadeInfo World::intersection( const Ray& ray ) {

	if (accel_)
		return accel_->intersect(ray);

    ShadeInfo info;

    for ( Shape* s : shapes_ ) {
        ShadeInfo value = s->intersect( ray );
        if ( value.shape ) {
            if ( value.distance < info.distance ) {
                info = value;
            }
        }
    }

    return info;
}

//返回最终颜色
Color World::trace_ray( const Ray ray, int depth ) {
    ShadeInfo info( this->intersection( ray ) );

    if ( info.valid() ) {
        info.depth = depth;
        info.ray   = ray;

        Color c = info.material->shade( info );
        return c;
    }

    return bgColor_;
}

Color World::trace_ray_direct( const Ray ray, int depth ) {
    ShadeInfo info( this->intersection( ray ) );

    if ( info.valid() ) {
        info.depth = depth;
        info.ray   = ray;

        Color c = info.material->getColor( info );
        return c;
    }

    return bgColor_;
}

void World::max_to_one( Color& c ) const {
    if ( c.r() > 1 || c.g() > 1 || c.b() > 1 ) {
        float maxV = std::max( { kEpsilon, c.r(), c.g(), c.b() } );

        c /= maxV;
    }
}

void World::clamp_to_color( Color& c, const Color& clamto /*= g::Red*/ ) const {
    if ( c.r() > 1 || c.g() > 1 || c.b() > 1 ) {
        c = clamto;
    }
}
