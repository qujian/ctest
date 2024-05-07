#include <iostream>
using namespace std;

class BigObject {
public:
    BigObject() {
        cout << "ctor: " << this << endl;
    }
    ~BigObject() {
        cout << "dtor: " << this << endl;
    }
    BigObject(const BigObject& from) {
        cout << "copy ctor from: " << &from << " to: " << this << endl;
    }
    BigObject(BigObject&& from) {
        cout << "move constructor:" << &from << " to: " << this << endl;
    }
};

BigObject foo(int n) {
    BigObject localObj, anotherLocalObj;
    if (n > 2) {
       return std::move(localObj);
    } else {
       return std::move(anotherLocalObj);
    }
}

int main() {
    BigObject obj = foo(3);
}
