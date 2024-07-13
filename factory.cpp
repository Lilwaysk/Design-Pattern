#include <bits/stdc++.h>
using namespace std;

// Factory Design Pattern
// 实现产品的父类
class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {};
};

class SheepSmile : public AbstractSmile
{
public:
    void transform() { cout << "I am a Sheep smile" << endl; }
    void ability() { cout << "I can make you feel warm" << endl; }
};

class BatSmile : public AbstractSmile
{
public:
    void transform() { cout << "I am a Bat smile" << endl; }
    void ability() { cout << "I can make you feel dark" << endl; }
};

class LionSmile : public AbstractSmile
{
public:
    void transform() { cout << "I am a Lion smile" << endl; }
    void ability() { cout << "I can make you feel scary" << endl; }
};

// 定义工厂类 - 父类
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory() {};  
};


// 每个产品对应着自己的一个工厂
class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile * createSmile() { return new SheepSmile; }
    ~SheepFactory() { cout << "sp我被析构了" << endl; };
};

class LionFactory : public AbstractFactory
{
public:
    AbstractSmile * createSmile() { return new LionSmile; }
    ~LionFactory() { cout << "ln我被析构了" << endl; };
};

class BatFactory : public AbstractFactory
{
public:
    AbstractSmile * createSmile() { return new BatSmile; }
    ~BatFactory() { cout << "bt我被析构了" << endl; };
};

int main()
{
    AbstractFactory * factory = new SheepFactory;
    AbstractSmile * obj = factory->createSmile();
    obj->transform();
    obj->ability();
    delete obj;
    delete factory;
    return 0;
}