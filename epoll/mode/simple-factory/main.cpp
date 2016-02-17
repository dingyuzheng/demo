#include "factory.h"
using namespace mode;
int main()
{
	Factory factory;
	Product* pa = factory.CreateProduct(Factory::PRODUCT_A);
	pa->Show();
	Product* pb = factory.CreateProduct(Factory::PRODUCT_B);
	pb->Show();
	Product* pc = factory.CreateProduct(Factory::PRODUCT_C);
	pc->Show();

	delete pa;
	delete pb;
	delete pc;
	return 0;
}
