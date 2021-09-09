template<typename T>
class unique_ptr
{
private:
    T* ptr;
    
    unique_ptr(unique_ptr<T> const&) = delete;
    unique_ptr<T>& operator =(unique_ptr<T> const&) = delete;
    
public:
    unique_ptr() : ptr{nullptr} {}
    unique_ptr(T* p) : ptr{p} {}

    T&       operator*()       { return *ptr; }
    T const& operator*() const { return *ptr; }
    
    T* operator->() { return ptr; }
    
    T&       operator[](int const& index)       { return ptr[index]; }
    T const& operator[](int const& index) const { return ptr[index]; }

    ~unique_ptr()
    {
        delete[] ptr;
        ptr = nullptr;
    }
};