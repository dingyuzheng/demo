#include "factory.h"
#include <vector>
using namespace mode;
int main()
{
	typedef std::vector<Product*> PVec;
	PVec pvec;
	pvec.push_back( FactoryA().CreateProduct() );
	pvec.push_back( FactoryB().CreateProduct() );
	pvec.push_back( FactoryC().CreateProduct() );

	PVec::iterator it = pvec.begin(), ie = pvec.end();
	for ( ; it != ie; ++it )
		(*it)->Show();

	it = pvec.begin(), ie = pvec.end();
	for ( ; it != ie; ++it )
		delete *it;
	pvec.clear();

	return 0;
}
