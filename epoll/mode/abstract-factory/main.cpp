#include "factory.h"
#include <vector>
using namespace mode;
int main() {
	typedef std::vector<Product1*> P1Vec;
	typedef std::vector<Product2*> P2Vec;
	P1Vec p1vec;
	P2Vec p2vec;

	FactoryA fa;
	p1vec.push_back( fa.CreateProduct1() );
	p2vec.push_back( fa.CreateProduct2() );

	FactoryB fb;
	p1vec.push_back( fb.CreateProduct1() );
	p2vec.push_back( fb.CreateProduct2() );

	FactoryC fc;
	p1vec.push_back( fc.CreateProduct1() );
	p2vec.push_back( fc.CreateProduct2() );

	P1Vec::iterator it1 = p1vec.begin(), ie1 = p1vec.end();
	for ( ; it1 != ie1; ++it1 )
		(*it1)->ShowProduct1();
	P2Vec::iterator it2 = p2vec.begin(), ie2 = p2vec.end();
	for ( ; it2 != ie2; ++it2 )
		(*it2)->ShowProduct2();

	it1 = p1vec.begin(), ie1 = p1vec.end();
	for ( ; it1 != ie1; ++it1 )
		delete *it1;
	it2 = p2vec.begin(), ie2 = p2vec.end();
	for ( ; it2 != ie2; ++it2 )
		delete *it2;
	
	p1vec.clear();
	p2vec.clear();
	return 0;
}
