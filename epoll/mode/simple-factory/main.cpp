#include "factory.h"
#include <vector>
using namespace mode;
int main()
{
	typedef std::vector<Product*> PVec;
	PVec pvec;

	Factory factory;
	pvec.push_back( factory.CreateProduct(Factory::PRODUCT_A) );
	pvec.push_back( factory.CreateProduct(Factory::PRODUCT_B) );
	pvec.push_back( factory.CreateProduct(Factory::PRODUCT_C) );

	PVec::iterator it = pvec.begin(), ie = pvec.end();
	for ( ; it != ie; ++it)
		(*it)->Show();

	it = pvec.begin(), ie = pvec.end();
	for ( ; it != ie; ++it)
		delete *it;
	pvec.clear();

	return 0;
}
