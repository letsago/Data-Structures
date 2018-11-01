#pragma once

#include <pyu/linear_storage_interface.h>
#include <pyu/shared_ptr.h>

namespace pyu
{
namespace internal
{
    template <class T>
    class LinearStorageInterfaceCreator
    {
      protected:
        virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>> CreateTestableInterface()
        {
            return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new T());
        };

        virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>>
        CreateTestableInterface(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other)
        {
            return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new T(dynamic_cast<const T&>(*other)));
        };
    };
} // namespace internal
} // namespace pyu
