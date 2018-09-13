#include <pyu/test_lib.h>
#include "lsi_test.h"
#include <pyu/linear_storage_interface.h>

using namespace pyu;

bool LinearStorageInterfaceTests::InsertTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    VERIFY_FALSE(pLsi->insert(1, 3));

    for (uint32_t i = 0; i < 8; ++i)
    {
        VERIFY_TRUE(pLsi->insert(i, i));
        VERIFY_EQ(pLsi->length(), i + 1);
    }

    for (uint32_t i = 0; i < pLsi->length(); ++i)
    {
        VERIFY_EQ(pLsi->at(i), i);
    }

    VERIFY_TRUE(pLsi->insert(5, 10));
    VERIFY_EQ(pLsi->length(), 9);
    VERIFY_EQ(pLsi->at(5), 10);

    for (uint32_t i = 6; i < pLsi->length(); ++i)
    {
        VERIFY_EQ(pLsi->at(i), i - 1);
    }
    
    VERIFY_FALSE(pLsi->insert(10, 9));
    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::RemoveTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    VERIFY_FALSE(pLsi->remove(0));

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert(i, i));
        VERIFY_EQ(pLsi->at(i), i);
        VERIFY_EQ(pLsi->length(), i + 1);
    }

    VERIFY_TRUE(pLsi->remove(3));
    VERIFY_EQ(pLsi->length(), 4);
    
    for (uint32_t i = 0; i < 3; ++i)
    {
        VERIFY_EQ(pLsi->at(i), i);
    }

    VERIFY_EQ(pLsi->at(3), 4);
    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::InsertFrontTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert_front(i * 2));
        VERIFY_EQ(pLsi->front(), i * 2);
        VERIFY_EQ(pLsi->length(), i + 1);
    }
    
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_EQ(pLsi->at(i), (4 - i) * 2);
    }

    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::RemoveFrontTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    VERIFY_FALSE(pLsi->remove_front());

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert_front(i * 2));
        VERIFY_EQ(pLsi->front(), i * 2);
        VERIFY_EQ(pLsi->length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; --i)
    {
        VERIFY_EQ(pLsi->front(), (i - 1) * 2);
        VERIFY_TRUE(pLsi->remove_front());
        VERIFY_EQ(pLsi->length(), i - 1);
    }

    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::InsertBackTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert_back(i * 3));
        VERIFY_EQ(pLsi->length(), i + 1);
    }

    for (uint32_t i = 0; i < pLsi->length(); ++i)
    {
        VERIFY_EQ(pLsi->at(i), i * 3);
    }

    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::RemoveBackTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    VERIFY_FALSE(pLsi->remove_front());

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert_back(i * 3));
        VERIFY_EQ(pLsi->back(), i * 3);
        VERIFY_EQ(pLsi->length(), i + 1);
    }

    for (uint32_t i = 5; i > 0; --i)
    {
        VERIFY_EQ(pLsi->back(), (i - 1) * 3);
        VERIFY_TRUE(pLsi->remove_back());
        VERIFY_EQ(pLsi->length(), i - 1);
    }

    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::ClearTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        pLsi->insert_back(5);
    }

    VERIFY_EQ(pLsi->length(), 5);

    pLsi->clear();
    VERIFY_TRUE(pLsi->empty());
    VERIFY_EQ(pLsi->length(), 0);
    delete pLsi;
    
    return true;
}

bool LinearStorageInterfaceTests::AtTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    for (uint32_t i = 0; i < 8; ++i)
    {
        pLsi->insert_back(8);
    }

    pLsi->at(4) = 5;
    VERIFY_EQ(pLsi->at(4), 5);
    pLsi->front() = 1;
    VERIFY_EQ(pLsi->front(), 1);
    pLsi->back() = 10;
    VERIFY_EQ(pLsi->back(), 10);
    delete pLsi;

    return true;
}

bool LinearStorageInterfaceTests::ContainsTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();
    for (uint32_t i = 0; i < 5; ++i)
    {
        pLsi->insert_back(i);
    }

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->contains(i));
    }

    VERIFY_FALSE(pLsi->contains(5));
    delete pLsi;

    return true;

}

bool LinearStorageInterfaceTests::FindTest()
{
    LinearStorageInterface<int>* pLsi = createTestLSI();

    VERIFY_EQ(pLsi->find(0), -1);

    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_TRUE(pLsi->insert_back(i));
    }

    // Find succeeds if able to find index of given value
    for (uint32_t i = 0; i < 5; ++i)
    {
        VERIFY_EQ(pLsi->find(i), i);
    }
    
    VERIFY_TRUE(pLsi->insert(2, 4));

    // Find will return the index of first instance of value
    VERIFY_EQ(pLsi->find(4), 2);

    // If unable to find index of given value, Find fails and returns -1
    VERIFY_EQ(pLsi->find(8), -1);
    delete pLsi;

    return true;
}