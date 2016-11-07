#include <iostream>
#include <utility>

template <typename T>
class shared_ptr {
public:
    shared_ptr();/*noexcept*/
    shared_ptr(T* ptr);/*strong*/
    auto operator= (shared_ptr const &)->shared_ptr &;/*noexcept*/
    auto operator =(shared_ptr &&) -> shared_ptr &;/*noexcept*/
  
    auto reset(T *tmp) -> void;/* strong */ 
    auto swap(shared_ptr& r) -> void;/*noexcept*/
  
    shared_ptr(shared_ptr const &); /*noexcept*/
    shared_ptr(shared_ptr &&);/*noexcept*/
    
    auto operator ->() const -> T &;/*strong*/
    auto operator *() const -> T &;/*strong*/
    auto get() const  -> T *;/*noexcept*/
    auto use_count() const->size_t;/*noexcept*/
 
private:
    T* ptr_;
    size_t * counter;
};

template <class T>
shared_ptr<T>::shared_ptr():   ptr_(nullptr),
            counter(nullptr)
{}

template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template <class T>
shared_ptr<T>::shared_ptr(T *tmp) :  ptr_(tmp),
        counter(new size_t(1))
{}

template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & 
{
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<typename T>
auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr &
{
    this->swap(other);
    return *this;
}

template <class T>
void shared_ptr<T>::reset(T *tmp) {
    delete ptr_;
    delete counter;
    ptr_ = tmp;
    counter = new size_t(1);
}

template <class T>
auto shared_ptr<T>::swap(shared_ptr &other) -> void {
    std::swap(ptr_, other.ptr_);
    std::swap(counter, other.counter);
}

template <class T>
shared_ptr<T>::shared_ptr(shared_ptr const  &other): ptr_(other.ptr_),
            counter(other.counter)
{
    if (counter != nullptr) ++(*counter);
}

template <class T>
shared_ptr<T>::shared_ptr(shared_ptr<T> &&other) : ptr_(other.ptr_),
        counter(other.counter)
{
    other.ptr_ = nullptr;
    other.counter = nullptr;
}

template <class T>
auto shared_ptr<T>::operator*() const -> T & {
    return *ptr_;
}

template<typename T>
auto shared_ptr<T>::operator ->() const -> T &{
       return *ptr_;
}

template <typename T>
auto shared_ptr<T>::use_count() const -> size_t {
    return (counter!=nullptr ? *counter : 0);
}

template <class T>
auto shared_ptr<T>::get() const-> T * {
    return ptr_;
}
//просто для пуша
