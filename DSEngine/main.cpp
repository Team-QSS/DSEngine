#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"

using namespace std;

class TestGame : public DS::BaseGame
{
	void onInitialize() {}
	void onUpdate() {}
	void onDraw() {}
	void onDestroy() {}
};

int main()
{
	return 0;
}