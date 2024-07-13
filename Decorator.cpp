#include <bits/stdc++.h>
using namespace std;

/*

    Decorator Pattern
    1.通过采用组合而非继承的手法，Decorator模式实现了在运行时动态扩展对象的能力。而且
      可以根据需要扩展多个功能。避免了使用继承带来的“灵活性差”和“多子类衍生”问题。
    
    2.Decorator类在接口上表现为is-a Component的继承关系，即Decorator类继承了Component类所具有的接口。
      但在实现上又表现为has-a Component的组合关系，即Decorator类又使用了另外一个Component类。

    3，Decorator模式的目的并非解决“多子类衍生的继承问题”，Decorator模式应用的要点在于解决“主题类
       在多个方向上的扩展功能”————是为“装饰”的含义。

*/


// Boy的抽象基类
class Boy
{
public: 
    virtual void wearClothes() = 0;
    virtual ~Boy() {}
};

// Boy的实体类
class ConcreteBoy : public Boy
{
public:
    void wearClothes() override 
    {
        cout << "穿内裤、穿裤子、穿鞋" << endl;
    }
};


// 定义的装饰器
class Decorator : public Boy
{
protected:
    Boy* boy;

public:
    Decorator(Boy* b) : boy(b) {}
    virtual void wearClothes() override
    {
        if(boy != nullptr)
            boy->wearClothes();
    }
};

// 装饰器实体类
class TieDecorator : public Decorator
{
public:
    TieDecorator(Boy* b) : Decorator(b) {}
    void wearClothes() override 
    {
        Decorator::wearClothes();
        cout << "穿领带" << endl;
    }
};

class JacketDecorator : public Decorator
{
public:
    JacketDecorator(Boy* b) : Decorator(b) {}
    void wearClothes() override 
    {
        Decorator::wearClothes();
        cout << "穿夹克" << endl;
    }
};


int main()
{
    Boy* boy = new TieDecorator(new JacketDecorator(new ConcreteBoy()));
    boy->wearClothes();
    delete boy;
    return 0;
}
