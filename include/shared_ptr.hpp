#include <iostream>
#include <utility>

template <typename T>
class shared_ptr {
public:
    shared_ptr();/*noexcept*/
    shared_ptr(T* ptr);/*strong*/
    ~shared_ptr();
    auto operator= (shared_ptr const &)->shared_ptr &;/*noexcept*/
    auto operator =(shared_ptr &&) -> shared_ptr &;/*noexcept*/
  
    auto reset(T *tmp) /* strong */ -> void;
    auto swap(shared_ptr& r) noexcept -> void;/*noexcept*/
  
    shared_ptr(shared_ptr const &); /*noexcept*/
    shared_ptr(shared_ptr &&);/*noexcept*/
    
    auto operator ->() const -> T *;/*strong*/
    auto operator *() const -> T *;/*strong*/
    auto get() const noexcept -> T *;/*noexcept*/
    auto use_count() const->size_t;/*noexcept*/
 
private:
    T* ptr_;
    size_t *count_;
};
