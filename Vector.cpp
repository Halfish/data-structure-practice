/*************************************************************************
	> File Name: Vector.cpp
	> Author: Bruce Zhang
	> Mail: zhangxb.sysu@gmail.com 
	> Created Time: 2015年11月24日 星期二 09时29分00秒
 ************************************************************************/
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

template<class Object>
class Vector {
public:
    enum { SPARE_CAPACITY = 16 };

    explicit Vector<Object>(int initSize=0);    // 默认参数值只能在这里设置
    Vector<Object>(const Vector<Object> & rhs);
    ~Vector<Object>();

    int size() const;       // 在函数后面加上const，表示此函数不会修改任何的成员变量
    void resize(int newSize);
    int capacity() const;
    void reserve(int newCapacity);
    void clear();
    bool empty();

    void push_back(const Object & x);   // 传进来const的引用，则函数无法改变该参数的值
    void pop_back();
    const Object & back();      // 返回常量引用
    const Object & front();

    /* vector不提供的方法，因为代价太高 */
    // void push_front(const Object & x);
    // void pop_front(const Object & x);

    const Vector<Object> & operator = (const Vector<Object> & rhs);
    Object & operator [] (int index);
    Object & at(int index);

    /* 这里的遍历器，为了方便，直接用指针替代了，实际上一般都是用内嵌函数实现  */
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    Object * objects;       // 实际存放的数组项
    int theSize;            // 数组大小
    int theCapacity;        // 数组容量
};


/* 显式调用构造函数 */
template<class Object>
Vector<Object>::Vector(int initSize):theSize(initSize), theCapacity(initSize+SPARE_CAPACITY) {
    objects = new Object[theCapacity];
}

/* 构造函数，用另一个Vector实例化，和 = 赋值一样，都是深拷贝
    rhs = right hand side 右操作符的参数名  */
template<class Object>
Vector<Object>::Vector(const Vector<Object> & rhs):objects(NULL) {
    operator = (rhs);
}

// 析构函数
template<class Object>
Vector<Object>::~Vector<Object>() {
    delete [] objects; 
}

// Vector数组的实际大小，即实际存放Object的个数
template<class Object>
int Vector<Object>::size() const {
    return theSize;
}

// ?? 为什么要提供这个函数 ??
template<class Object>
void Vector<Object>::resize(int newSize) {
    
}

// Vectir数组的容量，即总的可以允许存放Object的个数
template<class Object>
int Vector<Object>::capacity() const {
    return theCapacity;
}

/* 预先预留好内存 */
template<class Object>
void Vector<Object>::reserve(int newCapacity) {
    if (theSize > newCapacity) {
        return;
    }
    Object * oldObjects = objects;
    objects = new Object[newCapacity];
    for (int i = 0; i < theSize; ++ i) {
        objects[i] = oldObjects[i];
    }
    theCapacity = newCapacity;
    delete [] oldObjects;
}

// 把Vector清空
template<class Object>
void Vector<Object>::clear() {
    theSize = 0;
    theCapacity = SPARE_CAPACITY;
    delete [] objects;
    objects = new Object[theCapacity];
}

// 判断数组是否为空
template<class Object>
bool Vector<Object>::empty() {
    return (theSize == 0);
}

// 在末尾增加一个
template<class Object>
void Vector<Object>::push_back(const Object & x) {
    if (theSize == theCapacity) {
        reserve(theSize * 2 + 1);
    }
    objects[theSize ++] = x;
}

// 把最后一个删除
template<class Object>
void Vector<Object>::pop_back() {
    theSize --; 
}

// 得到最后一个Object的常量值
template<class Object>
const Object & Vector<Object>::back() {
    return objects[theSize - 1];
}

// 得到第一个Object
template<class Object>
const Object & Vector<Object>::front() {
    return objects[0];
}

// vector不提供的方法
// void push_front(const Object & x);
// void pop_front(const Object & x);

// 等于号赋值，深拷贝
template<class Object>
const Vector<Object> & Vector<Object>::operator = (const Vector<Object> & rhs) {
    if (this != &rhs) {
        delete [] objects;
        theSize = rhs.size();
        theCapacity = rhs.capacity();

        objects = new Object[theCapacity];
        for (int i = 0; i < theSize; ++ i) {
            objects[i] = rhs.objects[i];
        }
    }   
    return *this;
}


// 下标索引
template<class Object>
Object & Vector<Object>::operator [] (int index) {
    return objects[index]; 
}


// 索引，有越界检查
template<class Object>
Object & Vector<Object>::at(int index) {
    if (index < 0 || index >= theSize) {
        cout << "out of range!" << endl;
    }
    return objects[index];
}


/* 通过迭代器得到第一个数组项，iterator是个类型名，要显式地告诉编译器  */
template<class Object>
typename Vector<Object>::iterator Vector<Object>::begin() {
    return &objects[0];
}


/* 通过迭代器得到第一个数组项，返回常量。iterator是个类型名，要显式地告诉编译器  */
template<class Object>
typename Vector<Object>::const_iterator Vector<Object>::begin() const {
    return &objects[0];
}

/* 通过迭代器得到最后一个数组项的后面一个，注意不是最后一个 */
template<class Object>
typename Vector<Object>::iterator Vector<Object>::end() {
    return &objects[theSize];
}

/* 通过迭代器得到最后一个数组项的后面一个，返回常量。注意不是最后一个 */
template<class Object>
typename Vector<Object>::const_iterator Vector<Object>::end() const {
    return &objects[theSize];
}

#endif
