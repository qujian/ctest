// description:
// https://zhuanlan.zhihu.com/p/662637642


#include <iostream>
#include <memory>
#include <functional>

using namespace std;
class A {
public:
	A() { cout << "ctor A" << endl; }
    ~A() { cout << "dtor A" << endl; }
};

class B : public A {
public:
	B() { cout << "ctor B" << endl; }
    ~B() { cout << "dtor B" << endl; }
};


template <typename T>
class _shared_ptr2 {
public:
    template <typename T2>
    _shared_ptr2(T2 *p)
    {
        data_ = p;
        deleter_ = [p](){ delete p;};
    }
    ~_shared_ptr2()
    {
        deleter_();
    }
    T* operator->()
    {
        return data_;
    }
private:
    std::function<void()> deleter_;
    T* data_ = nullptr;
};



struct PtrType
{
    template<typename U>
    static void Destroy(void *p) {
    	delete (U*)p;
    }
};

template<typename T>
class ScopedPtr {
public:
    template<typename U>
    ScopedPtr(U *p) : mP(p) {
        mF = &PtrType::Destroy<U>;
    }

    ~ScopedPtr() {
        (*mF)(mP);
    }

	T* mP = nullptr;
	void (*mF)(void*) = nullptr;
};


int main() {
    ScopedPtr<A> ptr(new B);
    return 0;
}
