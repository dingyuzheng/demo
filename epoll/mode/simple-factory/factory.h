#ifndef FACTORY__H
#define FACTORY__H
#include <stdio.h>
namespace mode {
//产品抽象类
class Product {
private:
public:
	virtual ~Product() {}
	virtual void Show() = 0;	
};
//产品的具体实现
class ProductA : public Product {
private:
public:
	~ProductA() {
		printf("delete Product A!\n");
	}
	void Show() {
		printf("This is Product A!\n");
	}
};
class ProductB : public Product {
private:
public:
	~ProductB() {
		printf("delete Product B!\n");
	}
	void Show() {
		printf("This is Product B!\n");
	}
};
class ProductC : public Product {
private:
public:
	~ProductC() {
		printf("delete Product C!\n");
	}
	void Show() {
		printf("This is Product C!\n");
	}
};
//工厂类
class Factory {
private:
public:
	enum PRODUCT_TYPE {
		PRODUCT_A,
		PRODUCT_B,
		PRODUCT_C 
		};

	Product* CreateProduct(PRODUCT_TYPE type) {
		switch ( type )
		{
			case PRODUCT_A:
				return new ProductA();
				break;
			case PRODUCT_B:
				return new ProductB();
				break;
			case PRODUCT_C:
				return new ProductC();
				break;
			default:
				break;
		}
	}
};
}
#endif
