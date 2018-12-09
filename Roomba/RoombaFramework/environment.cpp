#include "environment.h"
#include "common.h"
#include "object.h"
#include <fstream>
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

Environment::Environment(const std::string& filename) : m_stepsTaken(0)
{
    std::ifstream inf(filename);

    if(!inf)
    {
        std::cerr << "Uh oh, could not be opened for reading!" << std::endl;
        exit(1);
    }

    inf >> *this;
}

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
    assert(isTraversable(pose));
    m_modules.insert(std::make_pair(module->id(), ModuleInfo(module, pose)));
}

bool Environment::isTraversable(const Pose& pose) const { return getGridUnit(pose).isTraversable; }

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

std::istream& operator>>(std::istream& is, Environment& env)
{
    while(is)
    {
        std::string strInput;
        getline(is, strInput);

        if(!strInput.empty())
        {
            env.m_grid.emplace_back();
            env.m_grid.back().resize(strInput.length());

            for(size_t i = 0; i < strInput.length(); ++i)
            {
                env.m_grid.back()[i].isTraversable = (strInput[i] == ' ');
            }
        }
    }

    env.m_drawBuffer.resize(env.m_grid.size());
    for(size_t row = 0; row < env.m_grid.size(); ++row)
    {
        env.m_drawBuffer[row].resize(env.m_grid[row].size());
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Environment& env)
{
    for(size_t row = 0; row < env.m_grid.size(); ++row)
    {
        for(size_t col = 0; col < env.m_grid[row].size(); ++col)
        {
            env.m_drawBuffer[row][col] = env.getGridUnit(Coor(row, col)).symbol();
        }
    }

    for(auto it : env.m_modules)
    {
        env.m_drawBuffer[it.second.position.m_pos.m_x][it.second.position.m_pos.m_y] =
            it.second.obj->orientedColoredSymbol(it.second.position.m_rot);
    }

    for(size_t row = 0; row < env.m_grid.size(); ++row)
    {
        for(size_t col = 0; col < env.m_grid[row].size(); ++col)
        {
            os << Color::Modifier(env.getGridUnit(Coor(row, col)).color()) << env.m_drawBuffer[row][col];
        }
        os << std::endl;
    }

    os << Color::Modifier(Color::FG_DEFAULT) << Color::Modifier(Color::BG_DEFAULT) << std::endl;
    return os;
}
