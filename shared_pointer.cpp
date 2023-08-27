#include <iostream>

using namespace std;

template<typename T>
class my_shared_ptr final
{
private:
    T* m_ptr;
    static int m_refcnt;
public:
    my_shared_ptr()
    {
    }
    my_shared_ptr(T* ptr) : m_ptr ( ptr )
    {
        my_shared_ptr::m_refcnt = 1;
        cout << "Main constructor called." << endl;
        cout << "ref count = " << m_refcnt << endl;
    }

    my_shared_ptr(const my_shared_ptr& ptr)
    {
        m_ptr = ptr.m_ptr;
        m_refcnt++;
        cout << "Copy constructor invoked." << endl;
        cout << "ref count = " << m_refcnt << endl;
    }

    my_shared_ptr& operator=(const my_shared_ptr& ptr)
    {
        m_ptr = ptr.m_ptr;
        m_refcnt++;
        cout << "Copy assignment operator invoked." << endl;
        cout << "ref count = " << m_refcnt << endl;
        return *this;
    }

    ~my_shared_ptr()
    {
        cout << "Destructor invoked." << endl;
        if(m_ptr != nullptr)
        {
            if (m_refcnt == 1)
            {
                cout << "Only one ref left." << endl;
                if (m_ptr != nullptr)
                    delete m_ptr;
                cout << "Pointer memory was deallocated." << endl;
            }
            else
            {
                m_refcnt--;
                cout << "Ref count was decremented." << endl;
                cout << "Current ref count : " << m_refcnt << endl;
            }
        }
    }

    T operator*()
    {
        return *m_ptr;
    }

    T* operator->()
    {
        return m_ptr;
    }
};

template <typename T>
int my_shared_ptr<T>::m_refcnt = 0;


int main()
{
    my_shared_ptr<int> s_ptr(new int(10));
    {
        my_shared_ptr<int> c_sptr(s_ptr);
        {
            my_shared_ptr<int> ca_sptr;
            ca_sptr = s_ptr;
        }
    }
    return 0;
}