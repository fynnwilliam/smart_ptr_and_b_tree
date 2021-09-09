template <typename T>
class shared_ptr
{
private:
    class counter
    {
    private:
        int count{};
    public:
        counter() : count{0} {}
        void increase() { ++count; }
        int decrease() { return --count; }
    };

    T* ptr;
    counter* reference;

public:
    shared_ptr() : ptr{nullptr}, reference{new counter()}
    {
        reference->increase();
    }

    shared_ptr(T* p) : ptr{p}, reference{new counter()}
    {
        reference->increase();
    }

    shared_ptr(shared_ptr<T> const& s) : ptr{s.ptr}, reference{s.reference}
    {
        reference->increase();
    }

    shared_ptr<T>& operator =(shared_ptr<T> const& s)
    {
        if (this != &s)
        {
            if (reference->decrease() == 0)
            {
                delete ptr;
                delete reference;

                ptr = nullptr;
                reference = nullptr;
            }

            ptr = s.ptr;
            reference = s.reference;
            reference->increase();
        }

        return *this;
    }

    T& operator*() { return *ptr; }
    T const& operator*() const { return *ptr; }

    T* operator->() { return ptr; }

    T& operator[](int const& index) { return ptr[index]; }
    
    T const& operator[](int const& index) const { return ptr[index]; }

    ~shared_ptr()
    {
        if (reference->decrease() == 0)
        {
            delete[] ptr;
            delete reference;

            ptr = nullptr;
            reference = nullptr;
        }
    }
};