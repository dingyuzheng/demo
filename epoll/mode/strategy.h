#ifndef STRATEGY__H
#define STRATEGY__H
#include <stdio.h>
#include <assert.h>
namespace mode {
class StrategyBase {
private:
public:
	virtual ~StrategyBase(){}
	virtual void InterFace() = 0;
};
class StrategyMan {
private:
	StrategyBase* obj_;
public:
	StrategyMan(StrategyBase* obj) {
		assert(obj != NULL);
		obj_ = obj;
	}
	~StrategyMan() {
		delete obj_;
	}
	void PublicInterFace() {
		obj_->InterFace();
	}
};
//具体实现
class Man : public StrategyBase {
private:
public:
	~Man() {
		printf("delete man!\n");
	}
	void InterFace() {
		printf("I'm a man!\n");
	}
};
class Dog : public StrategyBase {
private:
public:
	~Dog() {
		printf("delete dog!\n");
	}
	void InterFace() {
		printf("I'm a dog!\n");
	}
};
class Cat : public StrategyBase {
private:
public:
	~Cat() {
		printf("delete cat!\n");
	}
	void InterFace() {
		printf("I'm a cat!\n");
	}
};
class Baby : public StrategyBase {
private:
public:
	~Baby() {
		printf("delete baby!\n");
	}
	void InterFace() {
		printf("I'm a baby!\n");
	}
};
class Elephant : public StrategyBase {
private:
public:
	~Elephant() {
		printf("delete elephant!\n");
	}
	void InterFace() {
		printf("I'm an elephant!\n");
	}
};
}
#endif
