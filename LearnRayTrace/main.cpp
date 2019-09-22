#include "stdafx.h"
#include "World.h"
#include "BVH.h"
#include "Setting.h"
#include "PhotonMap.h"
#include "MultiJittered.h"

int main()
{
	MultiJittered::instance()->sample_hemisphere();

	//World::Instance()->accel_ = new BVH;

	World::Instance()->build_photon_map(2e5);
	PhotonMap::Instance()->build_kd_tree();

	World::Instance()->camera_.render();
	system("pause");
    return 0;
}

