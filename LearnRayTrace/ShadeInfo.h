#pragma once
#include "Ray.h"

//  #define  USING_COUT

class ShadeInfo
{
public:
	meta_name(ShadeInfo);
	ShadeInfo();

	float     dis = 0;
	Shape*    shape = nullptr;
	int       depth = 0;
	Vec3      normal;
	Vec3      position;

	Vec3      color;
	Ray       ray;
	float u = 0;
	float v = 0;

	Material* material = nullptr;

	void setShape(Shape* s);

	bool valid();
};
