#include "stdafx.h"
#include "World.h"

int main()
{
	long t = clock();

	World w;
	w._camera.render();

	cout << "finish " <<  (clock() - t) << endl;

    return 0;
}

