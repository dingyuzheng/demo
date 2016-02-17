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
//工厂抽象类
class Factory {
private:
public:
	virtual ~Factory() {}
	virtual Product* CreateProduct() = 0;
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
//工厂类具体实现
class FactoryA : public Factory {
private:
public:
	~FactoryA() {
		printf("delete factory A!\n");
	}
	Product* CreateProduct() {
		return new ProductA();
	}
};
class FactoryB : public Factory {
private:
public:
	~FactoryB() {
		printf("delete factory B!\n");
	}
	Product* CreateProduct() {
		return new ProductB();
	}
};
class FactoryC : public Factory {
private:
public:
	~FactoryC() {
		printf("delete factory C!\n");
	}
	Product* CreateProduct() {
		return new ProductC();
	}
};
}
#endif
