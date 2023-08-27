#include <iostream>

template <typename T>
class my_unique_ptr final
{
    private:
        T* m_ptr;
    public:
        my_unique_ptr()
        {
            m_ptr = nullptr;
        }
        my_unique_ptr(T* ptr) : m_ptr(ptr)
        {
        }
        ~my_unique_ptr()
        {
            delete m_ptr;
        }
        // Delete copy ctor
        my_unique_ptr(const my_unique_ptr&) = delete;
        // Delete copy assignment operator
        my_unique_ptr operator=(const my_unique_ptr&) = delete;

        T operator*()
        {
            return *m_ptr;
        }

        T* operator->()
        {
            return m_ptr;
        }
};

int main() 
{
    my_unique_ptr<int> ptr(new int(10));
    std::cout << *ptr << std::endl;
    return 0;
}