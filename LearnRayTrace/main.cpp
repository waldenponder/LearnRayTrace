#include "stdafx.h"
#include "World.h"
#include "BVH.h"

int main()
{
	World w;
	w.accel_ = new BVH;
	w.camera_.render();

    return 0;
}

