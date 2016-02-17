#ifndef FACTORY__H
#define FACTORY__H
#include <stdio.h>
namespace mode {
//抽象产品类1
class Product1 {
private:
public:
	virtual ~Product1() {}
	virtual void ShowProduct1() = 0;
};
//抽象产品类2
class Product2 {
private:
public:
	virtual ~Product2() {}
	virtual void ShowProduct2() = 0;
};
//抽象工厂类
class Factory {
private:
public:
	virtual ~Factory() {}
	virtual Product1* CreateProduct1() = 0;
	virtual Product2* CreateProduct2() = 0;
};
//具体产品类1-A
class Product1A : public Product1 {
private:
public:
	~Product1A() {
		printf("delete product 1A!\n");
	}
	void ShowProduct1() {
		printf("This is product 1A!\n");
	}
};
//具体产品类1-B
class Product1B : public Product1 {
private:
public:
	~Product1B() {
		printf("delete product 1B!\n");
	}
	void ShowProduct1() {
		printf("This is product 1B!\n");
	}
};
//具体产品类1-C
class Product1C : public Product1 {
private:
public:
	~Product1C() {
		printf("delete product 1C!\n");
	}
	void ShowProduct1() {
		printf("This is product 1C!\n");
	}
};
//具体产品类2-A
class Product2A : public Product2 {
private:
public:
	~Product2A() {
		printf("delete product 2A!\n");
	}
	void ShowProduct2() {
		printf("This is product 2A!\n");
	}
};
//具体产品类2-B
class Product2B : public Product2 {
private:
public:
	~Product2B() {
		printf("delete product 2B!\n");
	}
	void ShowProduct2() {
		printf("This is product 2B!\n");
	}
};
//具体产品类2-C
class Product2C : public Product2 {
private:
public:
	~Product2C() {
		printf("delete product 2C!\n");
	}
	void ShowProduct2() {
		printf("This is product 2C!\n");
	}
};
//具体工厂类A
class FactoryA : public Factory {
private:
public:
	~FactoryA() {
		printf("delete factory A!\n");
	}
	Product1* CreateProduct1() {
		return new Product1A();
	}
	Product2* CreateProduct2() {
		return new Product2A();
	}
};
//具体工厂类B
class FactoryB : public Factory {
private:
public:
	~FactoryB() {
		printf("delete factory B!\n");
	}
	Product1* CreateProduct1() {
		return new Product1B();
	}
	Product2* CreateProduct2() {
		return new Product2B();
	}
};
//具体工厂类C
class FactoryC : public Factory {
private:
public:
	~FactoryC() {
		printf("delete factory C!\n");
	}
	Product1* CreateProduct1() {
		return new Product1C();
	}
	Product2* CreateProduct2() {
		return new Product2C();
	}
};
}
#endif
