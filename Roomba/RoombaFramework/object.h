#pragma once
#include "colors.h"
#include "environment.h"
#include <cstdlib>
#include <memory>

class Module
{
  public:
    Module() : m_id(GenerateUniqueId()), m_active(false) {}
    virtual ~Module() {}

    const ID& id() const { return m_id; }
    bool isActive() const { return m_active; }
    virtual void On() { m_active = true; }
    virtual void Off() { m_active = false; }
    virtual std::string orientedColoredSymbol(const Rotation& rot) const
    {
        return Color::Modifier(isActive() ? Color::FG_GREEN : Color::FG_RED).to_string() + orientedSymbol(rot) +
               Color::Modifier(Color::FG_DEFAULT).to_string();
    }
    virtual char orientedSymbol(const Rotation& rot) const { return '*'; }
    virtual void step() final
    {
        if(isActive())
            step_action();
    }

    virtual void summary(std::string prefix) const
    {
        std::cout << Color::Modifier(isActive() ? Color::FG_GREEN : Color::FG_RED) << prefix << name() << " id:" << m_id
                  << Color::Modifier(Color::FG_DEFAULT) << std::endl;
    }

  protected:
    virtual const std::string name() const = 0;
    virtual void step_action() = 0;

  private:
    ID m_id;
    bool m_active;
};

class PoweredModules : public Module
{
  public:
    PoweredModules(uint32_t cost) : Module(), m_cost(cost){};

    virtual uint32_t step_cost() const { return m_cost; }

  protected:
    uint32_t m_cost;
};

class BatteryModule : public Module
{
  public:
    BatteryModule(uint32_t power) : Module(), m_power(power) {}

    void power(const std::shared_ptr<PoweredModules> module) { m_connections[module->id()] = module; }

    virtual void summary(std::string prefix) const
    {
        Module::summary(prefix);
        prefix += "\t";
        std::cout << prefix << "Power: " << m_power << std::endl;
        std::cout << prefix << "Wired To:";
        for(auto& obj : m_connections)
        {
            std::cout << " id:" << obj.first;
        }
        std::cout << std::endl;
    }

  protected:
    virtual const std::string name() const { return "BatteryModule"; }

    virtual void step_action()
    {
        bool gavePower = false;
        for(auto& obj : m_connections)
        {
            if(obj.second->isActive())
            {
                auto power = obj.second->step_cost();
                if(power > m_power)
                {
                    m_power = 0;
                    obj.second->Off();
                }
                else
                {
                    gavePower = true;
                    m_power -= power;
                }
            }
        }

        if(m_power == 0 && !gavePower)
            Off();
    }

  private:
    std::unordered_map<ID, std::shared_ptr<PoweredModules>> m_connections;
    uint32_t m_power;
};

class MovementModule : public PoweredModules
{
  public:
    MovementModule(uint32_t power, uint8_t maxSpeed)
        : PoweredModules(power), m_maxSpeed(maxSpeed), m_speed(0), m_rotation(0){};

    virtual uint32_t step_cost() const { return m_cost * (m_speed + m_rotation); }

    void setSpeed(uint8_t speed)
    {
        m_speed = std::max(m_maxSpeed, speed);
        m_rotation = 0;
    }
    void setRotation(uint8_t rotation)
    {
        m_rotation = rotation;
        m_speed = 0;
    }
    Pose getTransform() const { return Pose(Coor(0, m_speed), Rotation(m_rotation * 90)); }

    virtual void summary(std::string prefix) const
    {
        Module::summary(prefix);
        prefix += "\t";
        std::cout << prefix << "Speed: " << (int)m_speed << std::endl;
        std::cout << prefix << "Rotation: " << (int)m_rotation << std::endl;
    }

  protected:
    virtual const std::string name() const { return "MovementModule"; }
    virtual void step_action() {}

  private:
    const uint8_t m_maxSpeed;
    uint8_t m_speed;
    uint8_t m_rotation;
};

class Object;

class Controller : public PoweredModules
{
  public:
    Controller() : PoweredModules(1){};
    virtual void configureTo(std::shared_ptr<Object> obj) = 0;

  protected:
    virtual const std::string name() const { return "Controller-" + controller_name(); }
    virtual const std::string controller_name() const = 0;
};

class Object : public Module
{
  public:
    Object(std::shared_ptr<BatteryModule> battery) : Module(), m_batteryId(battery->id()) { insert(battery); };
    virtual char orientedSymbol(const Rotation& rot) const
    {
        if(rot.isForward())
            return '>';
        if(rot.isRight())
            return 'v';
        if(rot.isLeft())
            return '^';
        if(rot.isBackward())
            return '<';

        assert(false);
    }

    void insert(std::shared_ptr<Module> obj)
    {
        assert(!std::dynamic_pointer_cast<Controller>(obj));
        m_modules[obj->id()] = obj;
        if(auto mod = std::dynamic_pointer_cast<PoweredModules>(obj))
        {
            dynamic_cast<BatteryModule*>(m_modules[m_batteryId].get())->power(mod);
        }
    }

    static void PairControllerAndObject(std::shared_ptr<Object> obj, std::shared_ptr<Controller> controller)
    {
        obj->m_controller = controller;
        dynamic_cast<BatteryModule*>(obj->m_modules[obj->m_batteryId].get())->power(controller);
        controller->configureTo(obj);
    }

    virtual void On()
    {
        for(auto& obj : m_modules)
        {
            if(!obj.second->isActive())
                obj.second->On();
        }
        if(!m_controller->isActive())
            m_controller->On();
        Module::On();
    }

    virtual void Off()
    {
        for(auto& obj : m_modules)
        {
            if(obj.second->isActive())
                obj.second->Off();
        }
        if(m_controller->isActive())
            m_controller->Off();
        Module::Off();
    }

    template <typename T>
    ID findFirstByType() const
    {
        for(auto& it : m_modules)
        {
            if(dynamic_cast<T*>(it.second.get()))
                return it.second->id();
        }
        return InvalidID;
    }

    const std::shared_ptr<Module> findById(const ID& id) const { return m_modules.at(id); }
    std::shared_ptr<Module> findById(const ID& id) { return m_modules.at(id); }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj) { return os; }
    virtual void summary(std::string prefix) const
    {
        Module::summary(prefix);
        m_controller->summary(prefix + "\t");
        for(auto& it : m_modules)
        {
            it.second->summary(prefix + "\t");
        }
    }

  protected:
    virtual const std::string name() const { return "Object"; }

    void step_action()
    {
        bool didStep = false;
        m_controller->step();
        for(auto& obj : m_modules)
        {
            obj.second->step();
            didStep |= obj.second->isActive();
        }

        didStep &= m_modules[m_batteryId]->isActive();

        if(!didStep)
            Off();
    }

  private:
    std::unordered_map<ID, std::shared_ptr<Module>> m_modules;
    // Only one controller allowed per object.
    // If you wish to have two Controllers access it, they will have to decide control
    // through an intermediary Controller
    std::shared_ptr<Controller> m_controller;
    const ID m_batteryId;
};

class RandomController : public Controller
{
  public:
    virtual void configureTo(std::shared_ptr<Object> obj)
    {
        m_attachedModule = obj;
        auto MM_id = obj->findFirstByType<MovementModule>();
        m_movementModule = std::dynamic_pointer_cast<MovementModule>(obj->findById(MM_id));
    }

  protected:
    virtual const std::string controller_name() const { return "Random"; }
    void step_action()
    {
        if(rand() % 4 == 0)
            m_movementModule->setRotation(1);
        else
            m_movementModule->setSpeed(1);
    }

  private:
    std::weak_ptr<Object> m_attachedModule;
    std::shared_ptr<MovementModule> m_movementModule;
};
