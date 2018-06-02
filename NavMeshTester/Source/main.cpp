#include "NavMeshTesterApp.h"

int main() {
	
	auto app = new NavMeshTesterApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}