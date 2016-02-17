#include "factory.h"
using namespace mode;
int main()
{
	FactoryA fa;
	Product* pa = fa.CreateProduct();
	pa->Show();
	FactoryB fb;
	Product* pb = fb.CreateProduct();
	pb->Show();
	FactoryC fc;
	Product* pc = fc.CreateProduct();
	pc->Show();

	delete pa;
	delete pb;
	delete pc;
	return 0;
}
