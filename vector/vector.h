// Vector.h -- header file for Vector data structure project



#pragma once
#ifndef _Vector_h
#define _Vector_h

#include <cstdint>
#include"iostream"
#include <stdexcept>
#include <new>

namespace epl{
    
    template <typename T>
    class vector {
    private:
        uint64_t start;
        uint64_t end;
        uint64_t capacity;
        T *buffer;
    public:
        vector(void);
        explicit vector(uint64_t n);
        vector(const vector &lhs);
        vector(vector &&rhs);
        ~vector(void);
        void destroy();
        uint64_t size(void) const;
        void resize(uint64_t _capacity);
        T& operator[](uint64_t index);
        const T& operator[](uint64_t index) const;
        void push_back(const T&);
        //        void push_back(T&&);   partB
        void push_front(const T&);
        //        void push_front(T&&);  partB
        void pop_back(void);
        void pop_front(void);
        vector<T> & operator=(const vector<T> &);
    };
    
    template<typename T>
    vector<T>::vector(void){
        //        std::cout<<"no parameter constructor called"<<std::endl;
        capacity = 8;
        start = capacity/2;
        end = capacity/2;
        buffer = (T*)operator new(sizeof(T)*capacity);
        
    }
    
    template<typename T>
    vector<T>::vector(uint64_t n){
        //        std::cout<<"constructor with n called"<<std::endl;
        int k = n;
        if(k<0){
            std::cout<<"n<0"<<std::endl;    // ???
        }
        if(2*n+5>8){
            capacity = 2*n+5;
        }
        else{
            capacity = 8;
        }
        start = capacity/2;
        end = capacity/2+n;
        buffer = (T*)operator new(sizeof(T)*capacity);
        for (uint64_t i=start; i<end; i++) {
            new (buffer+i) T{};
        }
        
    }
    
    template<typename T>
    vector<T>::vector(const vector &lhs){
        //        std::cout<<"copy constructor called"<<std::endl;
        capacity = lhs.capacity;
        start = lhs.start;
        end = lhs.end;
        buffer = (T*)operator new(capacity * sizeof(T));
        for(uint64_t i=start; i<end; i++){
            new (buffer+i) T{lhs.buffer[i]};           // ???
        }
        
    }
    
    template<typename T>
    vector<T>::~vector(void){
        //        std::cout<<"destructor called"<<std::endl;
        destroy();
    }
    
    template<typename T>
    void vector<T>:: destroy(void){
        for(uint64_t i=start; i<end; i++){
            buffer[i].~T();
        }
        operator delete(buffer);
    }
    
    template<typename T>
    uint64_t vector<T>::size(void) const{
        return end - start;
    }
    
    template<typename T>
    T& vector<T>::operator[](uint64_t index){
        index += start;
        if(index<start || index>=end ){
            throw std::out_of_range{"index out of range"};
        }
        return buffer[index];
    }
    
    template<typename T>
    const T& vector<T>::operator[](uint64_t index) const{
        index += start;
        if(index<start || index>=end ){
            throw std::out_of_range{"index out of range"};
        }
        return buffer[index];
    }
    
    template<typename T>
    void vector<T>::resize(uint64_t _capacity){
        capacity = _capacity;
        T* tmp = (T*)operator new(capacity * sizeof(T));
        uint64_t _start = capacity/2;
        uint64_t i;
        for(i = start; i<end; i++){
            new (tmp+_start+i-start) T{buffer[i]};
        }
        end = _start+i-start;
        start = _start;
        destroy();      // ???buffer is actually an array, but why errors with delete[]
        buffer = tmp;
    }
    
    template<typename T>
    void vector<T>::push_back(const T &tmp){
        //        std::cout<<"copy push back"<<std::endl;
        if(end >= capacity)
            resize(2*capacity+20);
        new(buffer+end)T{tmp};
        end++;
        
        
    }
    
    template<typename T>
    void vector<T>::push_front(const T& tmp){
        //        std::cout<<"move push forward"<<std::endl;
        if(start<1){
            resize(2*capacity+20);
        }
        start--;
        new (buffer+start) T{tmp};
        
    }
    
    template<typename T>
    void vector<T>:: pop_back(void){
        if( start == end){
            std::out_of_range("no element to pop back");
            return;
        }
        end--;
        buffer[end].~T();
    }
    
    
    template<typename T>
    void vector<T>:: pop_front(void){
        if(start == end){
            std::out_of_range("no element to pop front");
        }
        buffer[start].~T();
        start++;
    }
    
    template<typename T>
    vector<T> & vector<T>::operator=(const vector<T> &lhs){
        destroy();
        start = lhs.start;
        end = lhs.end;
        capacity = lhs.capacity;
        T* buffer = (T*)operator new(capacity * sizeof(T));
        for(uint64_t i=start; i<end; i++){
            new (buffer + i)T{lhs.buffer[i]};
        }
        
    }
    
} //namespace epl


#endif /* _Vector_h */
