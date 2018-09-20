#include "sharedptr_test.h"
#include <pyu/shared_ptr.h>

using namespace pyu;

Test_Registrar<SharedPtrTests> SharedPtrTests::registrar;

bool SharedPtrTests::FundamentalTypeTest()
{
    shared_ptr<int> p(new int(42));
    VERIFY_EQ(*p, 42);

    shared_ptr<int> s(new int(21));
    VERIFY_EQ(*s, 21);

    shared_ptr<int> q = p;
    VERIFY_EQ(*q, 42);

    shared_ptr<int> r = s;
    VERIFY_EQ(*r, 21);

    r = p;
    VERIFY_EQ(*r, 42);

    q = r;
    VERIFY_EQ(*q, 42);

    q.reset(new int(23));
    VERIFY_EQ(*q, 23);
    
    return true;
}

bool SharedPtrTests::ClassTypeTest()
{
    class Car
    {
        public:
            Car()
            {
                m_velocity = new int();
                *m_velocity = 0;
            }

            Car(int initial_v)
            {
                m_velocity = new int();
                *m_velocity = initial_v;
            }

            ~Car()
            {
                delete m_velocity;
            }

            int current_speed()
            {
                return *m_velocity;
            }

            void new_speed(int new_speed)
            {
                *m_velocity = new_speed;
            }

        private:
            int* m_velocity = nullptr;
    };

    shared_ptr<Car> p(new Car());
    VERIFY_EQ(p->current_speed(), 0);

    p->new_speed(80);
    VERIFY_EQ(p->current_speed(), 80);

    shared_ptr<Car> q = p;
    VERIFY_EQ(q->current_speed(), 80);
    
    shared_ptr<Car> r = p;
    VERIFY_EQ(r->current_speed(), 80);

    q = r;
    VERIFY_EQ(q->current_speed(), 80);

    q.reset(new Car(50));
    VERIFY_EQ(q->current_speed(), 50);

    return true;
}

bool SharedPtrTests::ScopeTest()
{
    shared_ptr<int> p(new int(5));
    VERIFY_EQ(*p, 5);
    {
        shared_ptr<int> q(new int(10));
        VERIFY_EQ(*q, 10);
        {
            shared_ptr<int> r(new int(15));
            p = q;
            q = r;
            VERIFY_EQ(*r, 15);
        }
        VERIFY_EQ(*q, 15)
    }
    VERIFY_EQ(*p, 10);
    
    return true;
}

bool SharedPtrTests::MemoryTest()
{
    shared_ptr<int> p(new int(6));
    p.clear();
    p.reset(new int(8));
    p.clear();
    p.clear();

    shared_ptr<int> w(new int(8));
    shared_ptr<int> y = w;
    w.clear();
    VERIFY_EQ(*y, 8);

    shared_ptr<int> n(new int(8));
    n.reset(new int(10));
    n.reset(new int(12));

    return true;
}