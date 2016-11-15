#include <iostream>

template <typename T>
class shared_ptr {
public:
    shared_ptr();/*noexcept*/
    shared_ptr(T* ptr);/*strong*/
    ~shared_ptr();/*noexcept*/
    auto operator= (shared_ptr const &)->shared_ptr &;/*noexcept*/
    auto operator =(shared_ptr &&) -> shared_ptr &;/*noexcept*/
  
    auto reset(T * tmp) -> void;/* strong */ 
    auto swap(shared_ptr&) -> void;/*noexcept*/
  
    shared_ptr(shared_ptr const &); /*noexcept*/
    shared_ptr(shared_ptr &&);/*noexcept*/
    
    auto operator ->() const -> T *;/*strong*/
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
auto make_shared(Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}

template <class T>
shared_ptr<T>::shared_ptr(T *tmp) :  ptr_(tmp),
        counter(new size_t(1))
{}

template <class T>
shared_ptr<T>::~shared_ptr() {
	if (counter && --(*counter)==0){
		delete ptr_; delete counter;}
	
//     if (counter)
//     {
//         if (*counter == 1) {
//             delete ptr_;
//             delete counter;
//         }      else{
//             --(*counter);
//         };
//     }
}

template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr & 
{
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<typename T>//!!!!!!!!
auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr &
{
	if (this != &other) {
        shared_ptr<T> rval(std::move(other));
        this->swap(rval);
    	}
    	return *this;
// 	if (this != &other) 
//  		swap(other);
// 	return *this;
//     //this->swap(other);
    //return *this;
}

//заменяет объект, которым владеет
// template <class T>
// auto shared_ptr<T>::reset(T *tmp) 
// {
// 	swap(shared_ptr(tmp));
// //     if (counter && --(*counter)==0){
// // 	delete ptr_; delete counter;}
// //     //this->~shared_ptr();
// //     ptr_ = tmp;
// //     counter = new size_t(1);
// }

template <class T>
void shared_ptr<T>::reset(T *tmp) {
    if (ptr != tmp) {
        if (*counter == 1) {
            delete ptr;
            delete counter;
        } else {
            --(*counter);
        }
        ptr = tmp;
        if (ptr != nullptr) {
            counter = new size_t(1);
        } else {
            counter = nullptr;
        }
    }
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
	if (ptr_ == nullptr) 
		throw ("nullptr...");
		//throw std::range_error("ptr_ = nullptr");
	else return *ptr_;
    //return *ptr_;
}

template<typename T>
auto shared_ptr<T>::operator ->() const -> T *{
	if (ptr_ == nullptr) 
		throw ("nullptr...");
		//std::range_error("ptr_ = nullptr");
	return ptr_;
       //return ptr_;
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
