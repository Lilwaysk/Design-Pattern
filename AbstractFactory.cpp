#include <bits/stdc++.h>
using namespace std;
 
// 船体
class ShipBody
{
public:
    virtual string getBody() = 0;
    virtual ~ShipBody() {}
};

class WoodBody : public ShipBody
{
public:
    string getBody() override { return "木头船体"; }
};

class IronBody : public ShipBody
{
public:
    string getBody() override { return "钢铁船体"; }
};

class MetalBody : public ShipBody
{
public:
    string getBody() override { return "合金船体"; }
};




// 引擎
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine() {}
};

class Human : public Engine
{
public:
    string getEngine() override { return "手动引擎"; }
};

class Diesel : public Engine
{
public:
    string getEngine() override { return "内燃机引擎"; }
};

class Nuclear : public Engine
{
public:
    string getEngine() override { return "核反应堆引擎"; }
};




// 武器
class Weapon 
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon() {}
};

class Gun : public Weapon
{
public:
    string getWeapon()
    {
        return "枪械武器";
    }
};

class Cannon : public Weapon
{
public:
    string getWeapon()
    {
        return "大炮武器";
    }
};

class Laser : public Weapon
{
public:
    string getWeapon()
    {
        return "激光武器";
    }
};





// 船
// 使用的是组合关系
class Ship
{
public:
    Ship(ShipBody * body, Engine * engine, Weapon * weapon) : 
        m_body(body), m_engine(engine), m_weapon(weapon) {}
    
    ~Ship() 
    {
        delete m_body;
        delete m_engine;
        delete m_weapon;
    }

    string getProperty()
    {
        return m_body->getBody() + m_engine->getEngine() + m_weapon->getWeapon();
    }

private:
    ShipBody * m_body;
    Engine * m_engine;
    Weapon * m_weapon;
};





// 抽象工厂类
class AbstractFactory
{
public:
    virtual Ship * createShip() = 0;
    virtual ~AbstractFactory() {}
}; 

class BasicFactory : public AbstractFactory 
{
public:
    Ship * createShip () override
    {
        Ship * ship = new Ship(new WoodBody, new Human, new Gun);
        cout << "基础版型号船只建造完毕" << endl;
        return ship;
    }
};

class StandarFactory : public AbstractFactory 
{
public:
    Ship * createShip () override
    {
        Ship * ship = new Ship(new IronBody, new Diesel, new Cannon);
        cout << "标准版型号船只建造完毕" << endl;
        return ship;
    }
};

class UltimataFactory : public AbstractFactory 
{
public:
    Ship * createShip () override
    {
        Ship * ship = new Ship(new MetalBody, new Nuclear, new Laser);
        cout << "旗舰版型号船只建造完毕" << endl;
        return ship;
    }
};

int main()
{
    AbstractFactory * factory = new UltimataFactory;
    Ship * ship = factory -> createShip();
    cout << ship->getProperty();
    delete ship;
    delete factory;
    // system("pause");
    return 0;
}