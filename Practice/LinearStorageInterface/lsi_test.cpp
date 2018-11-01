#include <gtest/gtest.h>
#include <pyu/array.h>
#include <pyu/iterator.h>
#include <pyu/linked_list.h>
#include <pyu/vector.h>
#include <pyu_test/LinearStorageInterfaceCreator.h>

using namespace pyu;

template <class T>
class LinearStorageInterfaceTests : public ::testing::Test, public internal::LinearStorageInterfaceCreator<T>
{
};

typedef testing::Types<pyu::Vector<int>, pyu::LinkedList<int>, pyu::Array<int, 10>> Implementations;
TYPED_TEST_CASE(LinearStorageInterfaceTests, Implementations);

TYPED_TEST(LinearStorageInterfaceTests, InsertTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    ASSERT_FALSE(p->insert(1, 3));

    for(uint32_t i = 0; i < 8; ++i)
    {
        ASSERT_TRUE(p->insert(i, i));
        ASSERT_EQ(p->length(), i + 1);
    }

    for(uint32_t i = 0; i < p->length(); ++i)
    {
        ASSERT_EQ(p->at(i), i);
    }

    ASSERT_TRUE(p->insert(5, 10));
    ASSERT_EQ(p->length(), 9);
    ASSERT_EQ(p->at(5), 10);

    for(uint32_t i = 6; i < p->length(); ++i)
    {
        ASSERT_EQ(p->at(i), i - 1);
    }

    ASSERT_FALSE(p->insert(10, 9));
}

TYPED_TEST(LinearStorageInterfaceTests, RemoveTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    ASSERT_FALSE(p->remove(0));

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert(i, i));
        ASSERT_EQ(p->at(i), i);
        ASSERT_EQ(p->length(), i + 1);
    }

    ASSERT_TRUE(p->remove(3));
    ASSERT_EQ(p->length(), 4);

    for(uint32_t i = 0; i < 3; ++i)
    {
        ASSERT_EQ(p->at(i), i);
    }

    ASSERT_EQ(p->at(3), 4);
}

TYPED_TEST(LinearStorageInterfaceTests, InsertFrontTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_front(i * 2));
        ASSERT_EQ(p->front(), i * 2);
        ASSERT_EQ(p->length(), i + 1);
    }

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(p->at(i), (4 - i) * 2);
    }
}

TYPED_TEST(LinearStorageInterfaceTests, RemoveFrontTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    ASSERT_FALSE(p->remove_front());

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_front(i * 2));
        ASSERT_EQ(p->front(), i * 2);
        ASSERT_EQ(p->length(), i + 1);
    }

    for(uint32_t i = 5; i > 0; --i)
    {
        ASSERT_EQ(p->front(), (i - 1) * 2);
        ASSERT_TRUE(p->remove_front());
        ASSERT_EQ(p->length(), i - 1);
    }
}

TYPED_TEST(LinearStorageInterfaceTests, InsertBackTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i * 3));
        ASSERT_EQ(p->length(), i + 1);
    }

    for(uint32_t i = 0; i < p->length(); ++i)
    {
        ASSERT_EQ(p->at(i), i * 3);
    }
}

TYPED_TEST(LinearStorageInterfaceTests, RemoveBackTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    ASSERT_FALSE(p->remove_front());

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i * 3));
        ASSERT_EQ(p->back(), i * 3);
        ASSERT_EQ(p->length(), i + 1);
    }

    for(uint32_t i = 5; i > 0; --i)
    {
        ASSERT_EQ(p->back(), (i - 1) * 3);
        ASSERT_TRUE(p->remove_back());
        ASSERT_EQ(p->length(), i - 1);
    }
}

TYPED_TEST(LinearStorageInterfaceTests, ClearTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    for(uint32_t i = 0; i < 5; ++i)
    {
        p->insert_back(5);
    }

    ASSERT_EQ(p->length(), 5);

    p->clear();
    ASSERT_TRUE(p->empty());
    ASSERT_EQ(p->length(), 0);
}

TYPED_TEST(LinearStorageInterfaceTests, AtTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    for(uint32_t i = 0; i < 8; ++i)
    {
        p->insert_back(8);
    }

    p->at(4) = 5;
    ASSERT_EQ(p->at(4), 5);
    p->front() = 1;
    ASSERT_EQ(p->front(), 1);
    p->back() = 10;
    ASSERT_EQ(p->back(), 10);
}

TYPED_TEST(LinearStorageInterfaceTests, ContainsTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    for(uint32_t i = 0; i < 5; ++i)
    {
        p->insert_back(i + 1000);
    }

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->contains(i + 1000));
    }

    ASSERT_FALSE(p->contains(5));
}

TYPED_TEST(LinearStorageInterfaceTests, FindTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();
    ASSERT_EQ(p->find(0), -1);

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i));
    }

    // Find succeeds if able to find index of given value
    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(p->find(i), i);
    }

    ASSERT_TRUE(p->insert(2, 4));

    // Find will return the index of first instance of value
    ASSERT_EQ(p->find(4), 2);

    // If unable to find index of given value, Find fails and returns -1
    ASSERT_EQ(p->find(8), -1);
}

TYPED_TEST(LinearStorageInterfaceTests, EqualityTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i));
    }

    shared_ptr<LinearStorageInterface<int>> r = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(r->insert_back(i * 2));
    }

    shared_ptr<LinearStorageInterface<int>> s = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 6; ++i)
    {
        ASSERT_TRUE(s->insert_back(i));
    }

    ASSERT_EQ(p, p);
    ASSERT_NE(p, r);
    ASSERT_NE(p, s);
}

TYPED_TEST(LinearStorageInterfaceTests, AssignmentTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i));
    }

    shared_ptr<LinearStorageInterface<int>> q = this->CreateTestableInterface();
    *q = *p;
    ASSERT_EQ(q, p);

    p->clear();
    ASSERT_NE(q, p);

    shared_ptr<LinearStorageInterface<int>> r = this->CreateTestableInterface();
    ASSERT_NE(q, r);
    ASSERT_TRUE(r->empty());

    *q = *r;
    ASSERT_EQ(q, r);
}

TYPED_TEST(LinearStorageInterfaceTests, CopyTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i));
    }

    shared_ptr<LinearStorageInterface<int>> q = this->CreateTestableInterface(p);
    ASSERT_EQ(q, p);

    p->clear();
    ASSERT_NE(q, p);

    shared_ptr<LinearStorageInterface<int>> r = this->CreateTestableInterface(p);
    ASSERT_EQ(p, r);
    ASSERT_TRUE(r->empty());
}

TYPED_TEST(LinearStorageInterfaceTests, IteratorUseTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i * 2));
    }

    int val = 0;

    for(Iterator<int> it = p->begin(); it != p->end(); ++it)
    {
        ASSERT_TRUE(*it == val * 2);
        ++val;
    }
}

TYPED_TEST(LinearStorageInterfaceTests, IteratorBoundsTest)
{
    shared_ptr<LinearStorageInterface<int>> p = this->CreateTestableInterface();

    for(uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_TRUE(p->insert_back(i * 2));
    }

    Iterator<int> it2 = p->end();
    it2 = it2 + 5;
    ASSERT_TRUE(it2 == p->end());
}
