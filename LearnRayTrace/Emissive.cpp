#include "stdafx.h"
#include "Emissive.h"


Emissive::Emissive()
{
}


Emissive::~Emissive()
{
}

Vec3 Emissive::shade(ShadeInfo& r)
{
	return _light * 10;
}

Vec3 Emissive::getColor(ShadeInfo& r)
{
	return _light * 10;
}