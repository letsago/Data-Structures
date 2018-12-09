#pragma once
#include "colors.h"
#include "common.h"
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

class Module;

typedef uint32_t ID;
static const ID InvalidID = 0;
static ID GenerateUniqueId()
{
    static uint32_t counter = 1;
    return counter++;
}

class Environment
{
  private:
    struct ModuleInfo
    {
        ModuleInfo(std::shared_ptr<Module> object, const Pose& pose) : obj(object), position(pose){};

        std::shared_ptr<Module> obj;
        Pose position;
    };

  public:
    Environment(const std::string& filename);
    void placeModule(std::shared_ptr<Module> module, const Pose& pose);
    void summary() const;

    void step();
    bool isActive() const;

    friend std::istream& operator>>(std::istream& is, Environment& env);
    friend std::ostream& operator<<(std::ostream& os, const Environment& env);

  private:
    bool isTraversable(const Pose& pose) const;

    template <typename T>
    void handleModule(T const* module, const ID id);

  private:
    struct GridUnit
    {
        bool isTraversable;
        Color::Code color() const { return isTraversable ? Color::BG_BLUE : Color::BG_DEFAULT; }
        char symbol() const { return isTraversable ? ' ' : '#'; }
    };

    const GridUnit& getGridUnit(const Pose& pose) const { return m_grid[pose.m_pos.m_x][pose.m_pos.m_y]; }
    GridUnit& getGridUnit(const Pose& pose) { return m_grid[pose.m_pos.m_x][pose.m_pos.m_y]; }

    std::vector<std::vector<GridUnit>> m_grid;
    std::unordered_map<ID, ModuleInfo> m_modules;
    std::queue<std::function<void()>> m_changeQueue;
    uint32_t m_stepsTaken;

    // Because we don't care to re-alloc the buffer each and every time we make sure to make this a one time alloc durin
    // the constructor However we allow modifications to this in the << operator as we use this to print
    mutable std::vector<std::vector<std::string>> m_drawBuffer;
};
