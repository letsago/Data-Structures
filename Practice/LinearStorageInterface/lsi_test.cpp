#include <pyu/test_lib.h>
#include "lsi_test.h"
#include <pyu/linear_storage_interface.h>
#include <pyu/shared_ptr.h>

using namespace pyu;

bool LinearStorageInterfaceTests::InsertTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    VERIFY_FALSE(p->insert(1, 3));

    for (uint32_t i = 0; i < 8; ++i)
    {
        VERIFY_TRUE(p->insert(i, i));
        VERIFY_EQ(p->length(), i + 1);
    }

    for (uint32_t i = 0; i < p->length(); ++i)
    {
        VERIFY_EQ(p->at(i), i);
    }

    VERIFY_TRUE(p->insert(5, 10));
    VERIFY_EQ(p->length(), 9);
    VERIFY_EQ(p->at(5), 10);

    for (uint32_t i = 6; i < p->length(); ++i)
    {
        VERIFY_EQ(p->at(i), i - 1);
    }
    
    VERIFY_FALSE(p->insert(10, 9));

    return true;
}

bool LinearStorageInterfaceTests::RemoveTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    VERIFY_FALSE(p->remove(0));

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert(i, i));
        VERIFY_EQ(p->at(i), i);
        VERIFY_EQ(p->length(), i + 1);
    }

    VERIFY_TRUE(p->remove(3));
    VERIFY_EQ(p->length(), 4);
    
    for (uint32_t i = 0; i < 3; ++i)
    {
        VERIFY_EQ(p->at(i), i);
    }

    VERIFY_EQ(p->at(3), 4);

    return true;
}

bool LinearStorageInterfaceTests::InsertFrontTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert_front(i * 2));
        VERIFY_EQ(p->front(), i * 2);
        VERIFY_EQ(p->length(), i + 1);
    }
    
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_EQ(p->at(i), (4 - i) * 2);
    }

    return true;
}

bool LinearStorageInterfaceTests::RemoveFrontTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    VERIFY_FALSE(p->remove_front());

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert_front(i * 2));
        VERIFY_EQ(p->front(), i * 2);
        VERIFY_EQ(p->length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; --i)
    {
        VERIFY_EQ(p->front(), (i - 1) * 2);
        VERIFY_TRUE(p->remove_front());
        VERIFY_EQ(p->length(), i - 1);
    }

    return true;
}

bool LinearStorageInterfaceTests::InsertBackTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert_back(i * 3));
        VERIFY_EQ(p->length(), i + 1);
    }

    for (uint32_t i = 0; i < p->length(); ++i)
    {
        VERIFY_EQ(p->at(i), i * 3);
    }

    return true;
}

bool LinearStorageInterfaceTests::RemoveBackTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    VERIFY_FALSE(p->remove_front());

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert_back(i * 3));
        VERIFY_EQ(p->back(), i * 3);
        VERIFY_EQ(p->length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; --i)
    {
        VERIFY_EQ(p->back(), (i - 1) * 3);
        VERIFY_TRUE(p->remove_back());
        VERIFY_EQ(p->length(), i - 1);
    }

    return true;
}

bool LinearStorageInterfaceTests::ClearTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        p->insert_back(5);
    }

    VERIFY_EQ(p->length(), 5);

    p->clear();
    VERIFY_TRUE(p->empty());
    VERIFY_EQ(p->length(), 0);
    
    return true;
}

bool LinearStorageInterfaceTests::AtTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    for (uint32_t i = 0; i < 8; ++i)
    {
        p->insert_back(8);
    }

    p->at(4) = 5;
    VERIFY_EQ(p->at(4), 5);
    p->front() = 1;
    VERIFY_EQ(p->front(), 1);
    p->back() = 10;
    VERIFY_EQ(p->back(), 10);

    return true;
}

bool LinearStorageInterfaceTests::ContainsTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        p->insert_back(i);
    }

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->contains(i));
    }

    VERIFY_FALSE(p->contains(5));

    return true;

}

bool LinearStorageInterfaceTests::FindTest()
{
    shared_ptr<LinearStorageInterface<int>> p = createTestLSI();
    VERIFY_EQ(p->find(0), -1);

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(p->insert_back(i));
    }

    // Find succeeds if able to find index of given value
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_EQ(p->find(i), i);
    }
    
    VERIFY_TRUE(p->insert(2, 4));

    // Find will return the index of first instance of value
    VERIFY_EQ(p->find(4), 2);

    // If unable to find index of given value, Find fails and returns -1
    VERIFY_EQ(p->find(8), -1);

    return true;
}