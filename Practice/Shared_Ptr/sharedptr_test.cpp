#include <gtest/gtest.h>
#include <pyu/shared_ptr.h>

TEST(SharedPtrTests, FundamentalTypeTest)
{
    pyu::shared_ptr<int> p(new int(42));
    ASSERT_EQ(*p, 42);

    pyu::shared_ptr<int> s(new int(21));
    ASSERT_EQ(*s, 21);

    pyu::shared_ptr<int> q = p;
    ASSERT_EQ(*q, 42);

    pyu::shared_ptr<int> r = s;
    ASSERT_EQ(*r, 21);

    r = p;
    ASSERT_EQ(*r, 42);

    q = r;
    ASSERT_EQ(*q, 42);

    q.reset(new int(23));
    ASSERT_EQ(*q, 23);
}

TEST(SharedPtrTests, ClassTypeTest)
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

    pyu::shared_ptr<Car> p(new Car());
    ASSERT_EQ(p->current_speed(), 0);

    p->new_speed(80);
    ASSERT_EQ(p->current_speed(), 80);

    pyu::shared_ptr<Car> q = p;
    ASSERT_EQ(q->current_speed(), 80);

    pyu::shared_ptr<Car> r = p;
    ASSERT_EQ(r->current_speed(), 80);

    q = r;
    ASSERT_EQ(q->current_speed(), 80);

    q.reset(new Car(50));
    ASSERT_EQ(q->current_speed(), 50);
}

TEST(SharedPtrTests, ScopeTest)
{
    pyu::shared_ptr<int> p(new int(5));
    ASSERT_EQ(*p, 5);
    {
        pyu::shared_ptr<int> q(new int(10));
        ASSERT_EQ(*q, 10);
        {
            pyu::shared_ptr<int> r(new int(15));
            p = q;
            q = r;
            ASSERT_EQ(*r, 15);
        }
        ASSERT_EQ(*q, 15);
    }
    ASSERT_EQ(*p, 10);
}

TEST(SharedPtrTests, MemoryTest)
{
    pyu::shared_ptr<int> p(new int(6));
    p.clear();
    p.reset(new int(8));
    p.clear();
    p.clear();

    pyu::shared_ptr<int> w(new int(8));
    pyu::shared_ptr<int> y = w;
    w.clear();
    ASSERT_EQ(*y, 8);

    pyu::shared_ptr<int> n(new int(8));
    n.reset(new int(10));
    n.reset(new int(12));
}
