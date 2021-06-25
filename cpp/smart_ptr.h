#include <utility>  // std::swap/move
template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr = nullptr)
        : ptr_(ptr) {}
    ~smart_ptr()
    {
        delete ptr_;
    }
    smart_ptr(smart_ptr&& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr rhs)
    {
        rhs.swap(*this);
        return *this;
    }
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        std::swap(ptr_, rhs.ptr_);
    }

private:
    T* ptr_;
};
