#include "strategy.h"
#include <vector>
using namespace mode;
int main() {
	typedef std::vector<StrategyMan*> SManVec;
	SManVec objs;
	objs.push_back(new StrategyMan(new Man()));
	objs.push_back(new StrategyMan(new Dog()));
	objs.push_back(new StrategyMan(new Cat()));
	objs.push_back(new StrategyMan(new Baby()));
	objs.push_back(new StrategyMan(new Elephant()));

	SManVec::iterator it = objs.begin(), ie = objs.end();
	for ( ; it != ie; ++it)
		(*it)->PublicInterFace();

	it = objs.begin(), ie = objs.end();
	for ( ; it != ie; ++it)
		delete (*it);

	objs.clear();
	return 0;
}
