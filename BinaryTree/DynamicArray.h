#pragma once

#include <iostream>
#include <cmath>
#include "Exceptions.h"

template<class T> void copyArray(T*,const T*, int);

template <class T>
class DynamicArray {
private:
    T *array;
    int arr_size;
    int capacity;

public:
    //constructors
    DynamicArray(T* items, const int count): arr_size(0), capacity(0),  array(nullptr) {
        if (count > 0) {
            arr_size = count;
            array = new T[count];
            for(int i = 0 ; i < arr_size; ++i) {
                array[i] = items[i];
            }
        }
    };

    explicit DynamicArray(const int size) : arr_size(0), capacity(0), array(nullptr) {//rename arg
        if (size > 0) {
            arr_size= size;
            array = new T[size];
        }
    };

    explicit DynamicArray(const DynamicArray<T> &other): arr_size(other.arr_size), capacity(other.capacity), array(nullptr){
       if (other.arr_size > 0 && other.array!=nullptr) {
           array = new T[other.arr_size];
           for (int i = 0; i < other.arr_size; ++i) {
               array[i] = other.array[i];
           }
       }
    };

    DynamicArray(): array(nullptr), arr_size(0), capacity(0){};

    //destructor
    ~DynamicArray() {
        delete[] array;
    }

    //methods
    const T& get(int index) const{
        if (index >= arr_size || index < 0) {
            throw IndexOutOfRange();
        }
        return (array[index]);
    }

    int getSize() const {
        return arr_size;
    }

    void set(const int index, const T& value) {
        if (index >= arr_size || index < 0) throw IndexOutOfRange();
        array[index] = value;
    }

    //void resize(const int new_size) {
    //    if (new_size < 0) throw IndexOutOfRange();
    //    if (new_size==arr_size) return;
    //    if (new_size == 0) {
    //        delete[] array;
    //        arr_size = 0;
    //        capacity = 0;
    //        array = nullptr;
    //        return;
    //    }

    //    // using more memory than we need to make resize more efficient
    //    if (new_size > capacity) {
    //        if (capacity == 0) capacity = 1;
    //        while (capacity <= new_size + 1) capacity *= 2;
    //        T *new_array = new T[capacity];
    //        if (array != nullptr) {
    //            copyArray<T>(new_array, array, arr_size);
    //            delete[] array;
    //        }
    //        array = new_array;
    //    }
    //    else if (new_size < capacity / 3) {
    //        while (capacity / 3 > new_size + 1) capacity /= 2;
    //        T *new_array = new T[capacity];
    //        if (array != nullptr) {
    //            copyArray<T>(new_array, array, new_size);
    //            delete[] array;
    //        }
    //        array = new_array;
    //    }
    //    arr_size = new_size;
    //}

    //функция resize заменена на обычную для работы дека
    void resize(int new_size) {
        if (new_size < 0) throw IndexOutOfRange();
        if (new_size == arr_size) return;
        T* temp_arr = new T[new_size];
        int min_size = new_size < arr_size ? new_size : arr_size;
        for (int i = 0; i < min_size; ++i) {
            temp_arr[i] = array[i];
        }
        delete[] array;
        array = temp_arr;
        arr_size = new_size;
        if (arr_size == 0) {
            delete[] array;
            array = nullptr;
        }
    }

    void print(){
        for (int i = 0; i < arr_size; i++){
            if (i != arr_size - 1) std::cout << this->get(i) << " ";
            else std::cout << this->get(i);
        }
    }

     T& operator[](int index) {
        if (index < 0 || index > arr_size) throw IndexOutOfRange();
        return array[index];
    }

    const T& operator[](int index) const {
       if (index < 0 || index > arr_size) throw IndexOutOfRange();
        return const_cast<T&>(array[index]);
    }

    bool operator==(const DynamicArray<T>& other) {
        if (this->array == other.array) return true;
        if (this->getSize() == other.getSize()){
            for (int i = 0; i < this->getSize(); ++i) {
                if ((*this)[i] != (other)[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }



    //методы для дека

    friend std::ostream& operator << (std::ostream& out, const DynamicArray<T>& array) {

        for (int i = 0; i < array.getSize() - 1; ++i) {
            out << array[i] << " ";
        }
        out << array[array.getSize() - 1] << "\n";
        return out;
    }

    void append(const T& item) {
        resize(arr_size + 1);
        array[arr_size - 1] = item;
    }

    void prepend(const T& item) {
        T* temp_arr = new T[arr_size + 1];
        for (int i = 1; i < (arr_size + 1); i++) {
            temp_arr[i] = array[i - 1];
        }
        temp_arr[0] = item;

        delete[] array;
        array = temp_arr;
        arr_size += 1;
    }

    void insertAt(int index, const T& item) {
        if (index < 0 || index > arr_size) throw IndexOutOfRange();
        T* temp_arr = new T[arr_size + 1];
        for (int i = 0; i < index; ++i) {
            temp_arr[i] = array[i];
        }
        temp_arr[index] = item;
        for (int i = index; i < arr_size + 1; ++i) {
            temp_arr[i] = array[i - 1];
        }
        delete[] array;
        array = temp_arr;
        arr_size += 1;
    }

};

template <typename T>
void copyArray(T *new_arr,const T* old_arr,int new_size) {
    for(int i = 0; i < new_size; ++i) {
        new_arr[i] = old_arr[i];
    }
};

