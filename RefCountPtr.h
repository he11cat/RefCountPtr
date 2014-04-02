#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;

class RefCountable
{
    public:
        RefCountable();
        virtual ~RefCountable();

        int addRef();
        int removeRef();
        virtual void release() = 0;

    private:
        volatile int refCount;
        //field 'guard' has an inaccessible copy constructor
        //mutex guard;
};

class My : public RefCountable
{
    public:
        virtual ~My();
        virtual void release();
};

template<class T>
class RefCountPtr
{
    public:
        RefCountPtr(): ptr(NULL) {}

        RefCountPtr(T* p)
        {
            ptr = p;
            ptr->addRef();
        }

        RefCountPtr(const RefCountPtr& another)
        {
            ptr = another.ptr;
            ptr->addRef();
        }

        RefCountPtr& operator = (const RefCountPtr& another)
        {
            if (this == &another)return *this;

            if (ptr != NULL && ptr->removeRef() == 0)
            {
                ptr->release();
                ptr = NULL;
            }

            ptr = another.ptr;
            ptr->addRef();
            return *this;
        }

        ~RefCountPtr()
        {
            if (ptr->removeRef() == 0)
            {
                ptr->release();
                ptr = NULL;
            }
        }

        T* operator&()
        {
            return ptr;
        }

        T& operator*()
        {
            return *ptr;
        }

    private:
        T* ptr;
};