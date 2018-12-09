#pragma once
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

  private:
    bool isTraversable(const Pose& pose);

    template <typename T>
    void handleModule(T const* module, const ID id);

  private:
    std::unordered_map<ID, ModuleInfo> m_modules;
    std::queue<std::function<void()>> m_changeQueue;
    uint32_t m_stepsTaken;
};
