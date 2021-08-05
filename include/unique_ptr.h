template<typename T>

class unique_ptr
{
private:
    T* ptr;
public:
    unique_ptr(T* p) : ptr{p} {}
    T& operator *() { return *ptr; }
    T* operator ->() { return ptr; }
    T& operator [](int index) { return ptr[index]; }
    ~unique_ptr() { delete ptr; ptr = nullptr; }
};