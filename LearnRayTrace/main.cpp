#include "stdafx.h"
#include "World.h"
#include "BVH.h"
#include "Setting.h"
#include "PhotonMap.h"

int main()
{
//	{
//		string path = g::getResDir() + "setting.json";
//#if 0
//		std::ofstream os(path);
//		cereal::JSONOutputArchive ar(os);
//		ar(*Setting::Instance());
//#else
//		std::ifstream os(path);
//		cereal::JSONInputArchive ar(os);
//		ar(*Setting::Instance());
//#endif
//	}

	//World::Instance()->accel_ = new BVH;
	
	World::Instance()->build_photon_map(1e5);
	PhotonMap::Instance()->build_kd_tree();

	World::Instance()->camera_.render();
	system("pause");
    return 0;
}

