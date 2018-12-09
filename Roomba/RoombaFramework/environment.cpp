#include "environment.h"
#include "common.h"
#include "object.h"
#include <iostream>

template <typename T>
void Environment::handleModule(T const* module, const ID id)
{
}

template <>
void Environment::handleModule<MovementModule>(MovementModule const* module, const ID id)
{
    Pose movement = module->getTransform();
    Pose newPosition = m_modules.at(id).position + movement;
    if(isTraversable(newPosition))
    {
        m_changeQueue.push([id, newPosition, this]() { m_modules.at(id).position = newPosition; });
    }
    else
    {
        // TODO: handle nearest best point
    }
}

Environment::Environment(const std::string& filename) : m_stepsTaken(0) {}

bool Environment::isActive() const
{
    bool isActive = false;
    for(auto& kv : m_modules)
    {
        isActive |= kv.second.obj->isActive();
    }
    return isActive;
}

void Environment::placeModule(std::shared_ptr<Module> module, const Pose& pose)
{
    // assert(isTraversable(pose));
    m_modules.insert(std::make_pair(module->id(), ModuleInfo(module, pose)));
}

bool Environment::isTraversable(const Pose& pose) { return false; }

void Environment::step()
{
    for(auto& kv : m_modules)
    {
        kv.second.obj->step();
        if(const Object* obj = dynamic_cast<const Object*>(kv.second.obj.get()))
        {
            ID id = obj->findFirstByType<MovementModule>();
            if(id != InvalidID)
            {
                auto movementMod = obj->findById(id);
                handleModule<MovementModule>(dynamic_cast<MovementModule*>(movementMod.get()), kv.first);
            }
        }
    }

    while(!m_changeQueue.empty())
    {
        auto change = m_changeQueue.front();
        m_changeQueue.pop();
        change();
    }
    ++m_stepsTaken;
}

void Environment::summary() const
{
    std::cout << "Environment Statistics:" << std::endl;
    std::cout << "\tSteps Taken: " << m_stepsTaken << std::endl;
    for(auto it : m_modules)
    {
        it.second.obj->summary("\t");
    }
}
