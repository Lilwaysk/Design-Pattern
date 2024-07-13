#include <bits/stdc++.h>
using namespace std;

/*
    Observer Pattern
    简单来说就是定义了⼀种⼀（被观察类）对多（观察类）的关系，让多个观察对象同时监听⼀个被观察对象，
    被观察对象状态发⽣变化时，会通知所有的观察对象，使他们能够更新⾃⼰的状态。

    观察者模式中存在两种⻆⾊：
    1.观察者： 内部包含被观察者对象，当被观察者对象的状态发⽣变化时，更新⾃⼰的状态。（接收通知更新状态）
    2.被观察者： 内部包含了所有观察者对象，当状态发⽣变化时通知所有的观察者更新⾃⼰的状态。（发送通知）

    为什么使用观察者模式
    1.当⼀个对象的改变需要同时改变其他对象，且不知道具体有多少对象有待改变时，应该考虑使⽤观察者模式
    2.⼀个抽象模型有两个⽅⾯，其中⼀⽅⾯依赖于另⼀⽅⾯，
      这时可以⽤观察者模式将这两者封装在独⽴的对象中使它们各⾃独⽴地改变和复⽤。

    实现步奏
    1.提供一个抽象的目标类：被观察的对象，抽象基本的属性状态及其他操作

    2.提供一个具体的目标类：被观察的对象具体实现

    3.提供一个抽象观察类：抽象观察类的具体的业务逻辑处理

    4.提供一个具体观察类：观察者的具体实现，得到通知后将完成一些具体的业务逻辑处理
*/

class Subject;

// 观察者的基类 内部实例化了被观察者的对象sub
class Observer 
{
public:
    Observer (string name, Subject* sub) : name(name), sub(sub) {}
    virtual void update() = 0;
    virtual ~Observer() {}
protected:
    string name;
    Subject* sub;
};

class StockObserver : public Observer
{
public:
    StockObserver(string name, Subject* sub) : Observer(name, sub) {}
    void update();
};

class NBAObserver : public Observer
{
public:
    NBAObserver(string name, Subject* sub) : Observer(name, sub) {}
    void update();
};

class TBObserver : public Observer
{
public:
    TBObserver(string name, Subject* sub) : Observer(name, sub) {}
    void update();
};

// 被观察者基类 内部存放了所有的观察者对象，以便状态发生变化时，给观察者发通知
class Subject
{
public:
    string action;    // 被观察者对象的状态
    virtual void attach(Observer* ) = 0;
    virtual void detach(Observer* ) = 0;
    virtual void notify() = 0;
protected:
    list<Observer *> observers;
};

class Secretary : public Subject
{
public:
    void attach(Observer* ob) override 
    {
        observers.push_back(ob);
    }

    void detach(Observer* ob) override
    {
        observers.remove(ob);
    }

    void notify() override
    {
        for(auto ob : observers)
            ob->update();
    }
};

void StockObserver::update()
{
    cout << name << "收到消息：" << sub->action << endl;
    if(sub->action == "老板来了")
        cout << name << "赶紧关闭股票软件，离开工位" << endl;
}

void NBAObserver::update()
{
    cout << name << "收到消息：" << sub->action << endl;
    if(sub->action == "老板来了")
        cout << name << "赶紧关闭NBA，离开工位" << endl;
}

void TBObserver::update()
{
    cout << name << "收到消息：" << sub->action << endl;
    if(sub->action == "老板来了")
        cout << name << "赶紧关闭淘宝，离开工位" << endl;
}

int main()
{
    Subject* BOSS = new Secretary();
    Observer* ob1 = new StockObserver("张三", BOSS);
    Observer* ob2 = new NBAObserver("李四", BOSS);
    Observer* ob3 = new TBObserver("王五", BOSS);

    BOSS->attach(ob1);
    BOSS->attach(ob2);
    BOSS->attach(ob3);

    BOSS->action = "老板来了";
    BOSS->notify();
    cout<<endl;
    BOSS->action = "老板走了";
    BOSS->notify();
    return 0;
}