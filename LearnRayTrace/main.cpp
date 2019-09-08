#include "stdafx.h"
#include "World.h"
#include "BVH.h"
#include "Setting.h"
#include "PhotonMap.h"

int main()
{
	//World::Instance()->accel_ = new BVH;
	World::Instance()->build_photon_map(1e5);
	PhotonMap::Instance()->build_kd_tree();

	World::Instance()->camera_.render();
	system("pause");
    return 0;
}

