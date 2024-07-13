#include <bits/stdc++.h>
using namespace std;

/*
    Strategy Pattern
    定义一系列算法，把他们一个个封装起来，并且使他们可互相替换(变化)。
    该模式使得算法可独立于使用它的客户程序(稳定)而变化(扩展，子类化)。

    要点总结
    1.strategy及其子类为组件提供了一系列可重用的算法。从而可以使得类在运行时方便地
      根据需要在各个算法之间进行切换。
    2.strategy模式提供了用条件判断语句以外的另一种选择，消除条件判断语句，就是在解
      耦合。含有许多条件判断语句的代码通常都需要strategy模式。
    3.如果strategy对象没有实例变量，那么各个上下文可以共享同一个strategy对象，从而
      节省对象开销。

    在策略模式中，通常包括以下几个角色：

    （1）策略接口（Strategy Interface）： 定义了一个策略的公共接口，所有具体的策略类都需要实现这个接口。这个接口声明了策略对象将执行的操作。

    （2）具体策略类（Concrete Strategy Classes）： 实现了策略接口，提供了具体的算法或行为。每个具体策略类都封装了实现特定行为或算法的代码。

    （3）上下文（Context）： 维护一个指向策略对象的引用，并定义一个接口来让策略对象执行其算法。上下文类并不知道具体的策略类，它只知道策略接口。这样，上下文可以将请求转发给当前关联的策略对象来执行。

*/

class TaxStrategy
{
public:
    virtual double Calculate(const Context& context) const = 0;
    virtual ~TaxStrategy() {}
};


class CNTax : public TaxStrategy
{
public:
    double Calculate(const Context& context) override
    {
        cout << "CNTax" << endl;
        return 0;
    }
};

class USTax : public TaxStrategy
{
public:
    double Calculate(const Context& context) override
    {
        cout << "USTax" << endl;
        return 0;
    }
};

class JPTax : public TaxStrategy
{
public:
    double Calculate(const Context& context) override
    {
        cout << "JPTax" << endl;
        return 0;
    }
};

class SaleOrder
{
private:
    TaxStrategy* strategy;

public:
    SaleOrder(TaxStrategy* strategy)
    {
        this->strategy = strategyFactory->CreateStrategy();
    }
    ~SaleOrder()
    {
        delete this->strategy;
    }
    double CalculateTax(const Context& context) 
    {
        Context context();
        double val = strategy->Calculate(context);
    }
};

int main()
{

    return 0;
}