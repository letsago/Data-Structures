#pragma once

#include <gtest/gtest.h>
#include <pyu/linear_storage_interface.h>
#include <pyu/shared_ptr.h>

template<class T>
class LinearStorageInterfaceTests : public testing::Test
{
protected:
    virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>> CreateTestableInterface()
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new T());
    };

    virtual pyu::shared_ptr<pyu::LinearStorageInterface<int>> CreateTestableInterface(pyu::shared_ptr<pyu::LinearStorageInterface<int>>& other)
    {
        return pyu::shared_ptr<pyu::LinearStorageInterface<int>>(new T(dynamic_cast<const T&>(*other)));
    };
};
