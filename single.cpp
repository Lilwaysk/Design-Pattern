/*
复用机制三剑客：
1.继承和组合
2.委托
3.参数化类型(模板)

聚合和相识

聚合：整体由部分组成，部分可以离开整体单独存在，部分与整体的生命周期相同

相识：整体与部分的关系是“has-a”的关系，部分不能离开整体单独存在，部分与整体的生命周期相同

面向对象最困难的部分是将系统分解成对象集合
要考虑许多因素：封装，粒度，依赖关系，灵活性，性能，演化，复用等

针对接口编程，而不是针对显示编程

面向对象功能复用的两种方法：类继承(白箱复用)和对象组合(黑箱复用)
优先使用对象组合，而不是类继承

委托是对象组合的特例，，他告诉你对象组合作为一个代码复用机制可以代替继承

创建型设计模式

类
Abstract Factory        : 抽象工厂模式

对象
Factory Method          : 工厂方法模式
Builder                 : 建造者模式
Prototype               : 原型模式
Singleton               : 单例模式


结构型设计模式

类
Adapter                 : 适配器模式

对象
Adapter                 : 适配器模式
Bridge                  : 桥接模式
Composite               : 组合模式
Decorator               : 装饰模式
Facade                  : 外观模式
Flyweight               : 享元模式
Proxy                   : 代理模式


行为型设计模式

类
Interpreter             : 解释器模式
Template Method         : 模板方法模式

对象
Chain of Responsibility : 责任链模式
Command                 : 命令模式
Iterator                : 迭代器模式
Mediator                : 中介者模式
Memento                 : 备忘录模式
Observer                : 观察者模式
State                   : 状态模式
Strategy                : 策略模式
Visitor                 : 访问者模式

*/

#include <bits/stdc++.h>
#include <mutex>
#include <thread>
#include <atomic>
using namespace std;


// 定义一个单例模式的任务队列
// 单例模式又分为懒汉模式和饿汉模式
// 单例模式的核心思想：一个类只能有一个对象，并且这个对象必须能够被访问到
// 要通过类名来得到一个对象，这个对象一定要是静态的

#if 0
// 饿汉模式：在程序启动的时候就已经创建对象(多线程模式下没有线程安全问题)
class TaskQueue
{
public:
    TaskQueue(const TaskQueue & t) = delete;  // 将拷贝构造函数显示删除
    static TaskQueue * getTaskQ()
    {
        m_taskQ = new TaskQueue();
        return m_taskQ;          
    }

    void print()
    {
        cout << "我是一个单例对象的成员函数..." << endl;
    }
private:
    // 只能通过类名访问静态属性或方法
    TaskQueue() = default;
    // TaskQueue & operater=(const TaskQueue & t) = default;
    static TaskQueue * m_taskQ;  // 静态对象不能在类的内部初始化
};
TaskQueue * TaskQueue::m_taskQ = new TaskQueue ;
#endif

#if 0
// 懒汉模式：在第一次使用的时候才创建对象(在多线程模式下有线程安全问题)
// 在多线程模式下会导致创建出多个类的实例这种问题
// 解决方法：加锁+双重检查锁定+原子操作
class TaskQueue
{
public:
    TaskQueue(const TaskQueue & t) = delete;        // 将拷贝构造函数显示删除
    static TaskQueue * getTaskQ()
    {
        TaskQueue * task = m_tasakQ.load();         // 加载原子对象
        if (taskQ == nullptr)                       // 双重检查锁定，提高代码执行效率
        {
            m_mutex.lock();                         // 加锁和解锁操作必须成对出现
            task = m_tasakQ.load(); 
            if(taskQ == nullptr)
            {
                taskQ = new TaskQueue;
                m_taskQ.store(taskQ);               // 将新创建的对象存储到原子对象中
            }
            m_mutex.unlock();
        }
        return task;
    }

    void print()
    {
        cout << "我是一个单例对象的成员函数..." << endl;
    }
private:
    // 只能通过类名访问静态属性或方法
    TaskQueue() = default;
    // TaskQueue & operater=(const TaskQueue & t) = default;
    // static TaskQueue * m_taskQ;  // 静态对象不能在类的内部初始化
    static mutex m_mutex;
    static atomic<TaskQueue *> m_tasakQ;            // 利用原子变量将taskq指针保存起来，利用原子变量的特性保证程序顺序执行
};
// TaskQueue * TaskQueue::m_taskQ = nullptr ;
atomic<TaskQueue *> TaskQueue::m_taskQ = nullptr ;
mutex TaskQueue::m_mutex ;
#endif

#if 0
// 懒汉模式：在第一次使用的时候才创建对象(在多线程模式下有线程安全问题)
// 使用静态的局部对象解决线程安全问题 -> 编译器必须支持c++11标准
class TaskQueue
{
public:
    TaskQueue(const TaskQueue & t) = delete;        // 将拷贝构造函数显示删除
    static TaskQueue * getTaskQ()
    {
        static TaskQueue task;                                  // 静态的局部对象，在程序运行期间只会被初始化一次
        return &task;
    }

    void print()
    {
        cout << "我是一个单例对象的成员函数..." << endl;
    }
private:
    // 只能通过类名访问静态属性或方法
    TaskQueue() = default;
    // TaskQueue & operater=(const TaskQueue & t) = default;
    // static TaskQueue * m_taskQ;  // 静态对象不能在类的内部初始化
};
#endif

#if 1
// 饿汉模式：在程序启动的时候就已经创建对象(多线程模式下没有线程安全问题)
// 基于饿汉模式写一个任务队列
class TaskQueue
{
public:
    TaskQueue(const TaskQueue & t) = delete;  // 将拷贝构造函数显示删除
    static TaskQueue * getTaskQ()
    {
        m_taskQ = new TaskQueue();
        return m_taskQ;          
    }

    void print()
    {
        cout << "我是一个单例对象的成员函数..." << endl;
    }

    // 判断队列是否为空
    bool isEmpty()
    {
        lock_guard<mutex> locker(m_mutex);    // 使用lock_guard类管理互斥锁，lock_guard类会在构造函数中加锁，在析构函数中解锁
        return m_data.empty();
    }
    // 添加任务
    void addTask(int node)
    {
        lock_guard<mutex> locker(m_mutex);
        m_data.push(node);
    }
    // 删除任务
    bool popTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(!m_data.empty())
        {
            m_data.pop();
            return true;
        }
        return false;
    }
    // 取出一个任务(不删除任务)
    int getTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(m_data.empty()) return -1;
        int data = m_data.front();
        return data;
    }

private:
    // 只能通过类名访问静态属性或方法
    TaskQueue() = default;
    // TaskQueue & operater=(const TaskQueue & t) = default;
    static TaskQueue * m_taskQ;  // 静态对象不能在类的内部初始化
    queue<int> m_data;           // 定义任务队列
    mutex m_mutex;               // 定义互斥锁,防止线程安全问题
};
TaskQueue * TaskQueue::m_taskQ = new TaskQueue ;
#endif









int main()
{
    TaskQueue * taskQ = TaskQueue::getTaskQ();
    
    // 生产者
    thread t1([=]()
    {
        for(int i = 0; i < 100; i++)
        {
            taskQ->addTask(i+100);
            cout<< "生产者添加任务：" << i+100 << ", threadID: " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });
    // 消费者
    thread t2([=]()
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        while(!taskQ->isEmpty())
        {
            int num = taskQ->getTask();
            cout<< "++ take data: " << num << ", threadID: " << this_thread::get_id() << endl;
            taskQ->popTask();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });

    t1.join();
    t2.join();

    system("pause");
    return 0;
}