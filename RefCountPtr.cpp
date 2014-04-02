#include "RefCountPtr.h"

RefCountable::RefCountable() : refCount(0)
{
    cout << "Ctor..." << hex << this << endl;
}

RefCountable::~RefCountable()
{

}

int RefCountable::addRef()
{
    // guard.lock();
    ++refCount;
    // guard.unlock();
    return refCount;
}

int RefCountable::removeRef()
{
    // guard.lock();
    --refCount;
    // guard.unlock();
    return refCount;
}

My::~My()
{
    release();
}

void My::release()
{
    cout << "release..." << hex << this << endl;
}

int main()
{
    RefCountPtr<My> p1 = new My();

    RefCountPtr<My> p2 = new My();

    p2 = p1;

    RefCountPtr<My> p3 = p2 = p2;

    My m;

    My* p = &p1;

    My& pr = *p2;

    RefCountPtr<My> movedLater = new My();
    movedLater = move(p3);

    RefCountPtr<My> moved = move(movedLater);

    return 0;
}