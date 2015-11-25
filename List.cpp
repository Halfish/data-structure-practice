/*************************************************************************
	> File Name: List.cpp
	> Author: Bruce Zhang
	> Mail: zhangxb.sysu@gmail.com 
	> Created Time: 2015年11月24日 星期二 17时54分34秒
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

template<class Object>
class List {
private:
    struct Node {
        Object data;
        Node *prev;     // 从这里可以看出来，我们实现的是双向链表
        Node *next;
        Node(const Object & d = Object(), Node *p = NULL, Node *n = NULL)
            :data(d), prev(p), next(n) {}
    };

public:
    class const_iterator {
    public: 
        const_iterator();   // 为什么没有拷贝构造函数？
        const Object & operator * () const;
        const_iterator & operator ++ ();    // ++ i
        const_iterator operator ++ (int);   // i ++
        const_iterator & operator -- ();    // -- i
        const_iterator operator -- (int);   // i -- 
        bool operator == (const const_iterator & rhs) const;
        bool operator != (const const_iterator & rhs) const;
    protected:      // protected下的成员变量和函数，只会对自己和子类开放
        Node *current;
        Object & retrieve() const;
        const_iterator(Node *p);
        friend class List<Object>;      // List为其友元类，可以访问私有变量
    };

    /* iterator为子类，因为多了修改的属性  */
    class iterator : public const_iterator {
    public:
        iterator() {};
        Object & operator * () ;    // 子类多了这个函数
        iterator & operator ++ ();
        iterator operator ++ (int);
        iterator & operator -- ();
        iterator operator -- (int);
    protected:
        iterator(Node *p):const_iterator(p){};
        friend class List<Object>;  // 子类也要声明友元类，否则，你自己试试看！ 
    };

public:
    List();
    List(const List<Object> & rhs);
    const List<Object> & operator = (const List<Object> & rhs);
    ~List();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    int size() const;
    bool empty() const;
    void clear();

    Object & front();
    const Object & front() const;
    Object & back();
    const Object & back() const;

    void push_front(const Object & x);
    void push_back(const Object & x);
    void pop_front();
    void pop_back();

    iterator insert(iterator iter, const Object & x);
    iterator erase(iterator iter);
    iterator erase(iterator start, iterator end);

private:
    int theSize;
    Node *head;
    Node *tail;

    void init();    //这个纯是为了省代码
};


/* 常量遍历器构造函数  */
template<class Object>
List<Object>::const_iterator::const_iterator() {
    current = NULL;
}

/* 取值操作，重载  */
template<class Object>
const Object & List<Object>::const_iterator::operator * () const {
    return retrieve();
}

// ++ i
template<class Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator ++ () {
    current = current->next;
    return *this;
}

// i ++ 
template<class Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator ++ (int) {
    const_iterator old = *this;
    current = current->next;
    return old;
}

// -- i
template<class Object>
typename List<Object>::const_iterator & List<Object>::const_iterator::operator -- () {
    current = current->prev;
    return *this;
}

// i -- 
template<class Object>
typename List<Object>::const_iterator List<Object>::const_iterator::operator -- (int) {
    const_iterator old = *this;
    current = current->prev;
    return old;
}

template<class Object>
bool List<Object>::const_iterator::operator == (const const_iterator & rhs) const {
    return current == rhs.current;
}

template<class Object>
bool List<Object>::const_iterator::operator != (const const_iterator & rhs) const {
    return current != rhs.current;
}

template<class Object>
Object & List<Object>::const_iterator::retrieve() const {
    return current->data;   // current类型是Node，data是Object
}

template<class Object>
List<Object>::const_iterator::const_iterator(Node *p) {
    current = p;  
}

template<class Object>
Object & List<Object>::iterator::operator * () {
    return const_iterator::retrieve(); 
}

// ++ iter
template<class Object>
typename List<Object>::iterator & List<Object>::iterator::operator ++ () {
    const_iterator::current = const_iterator::current->next;    
}

// iter ++
template<class Object>
typename List<Object>::iterator List<Object>::iterator::operator ++ (int) {
    iterator old = *this;
    const_iterator::current = const_iterator::current->next;    
    return old;
}

// -- iter
template<class Object>
typename List<Object>::iterator & List<Object>::iterator::operator -- () {
    const_iterator::current = const_iterator::current->prev;    
}

// iter --
template<class Object>
typename List<Object>::iterator List<Object>::iterator::operator -- (int) {
    iterator old = *this;
    const_iterator::current = const_iterator::current->prev;    
    return old;
}

template<class Object>
List<Object>::List() {
    init();
}

template<class Object>
List<Object>::List(const List<Object> & rhs) {
    init();
    *this = rhs;
}

/* 赋值操作  */
template<class Object>
const List<Object> & List<Object>::operator = (const List<Object> & rhs) {
    if (this == &rhs) {
        return rhs;
    }
    clear();
    for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++ iter) {
        push_back(*iter);
    }
    return *this;
}

/* 析构函数  */
template<class Object>
List<Object>::~List() {
    clear();
    delete [] head;
    delete [] tail;
}

/*
 * begin() end() 是 iterator 类型，
 * tail, head 是 Node * 类型，
 * front(), back() 是 Object 类型
 *
 * head后一个节点存放着front，tail前一个节点存放着back
 * 迭代器begin指向front，end则是back的下一个节点，即tail
 */
template<class Object>
typename List<Object>::iterator List<Object>::begin() {
    return iterator(head->next);
}

template<class Object>
typename List<Object>::const_iterator List<Object>::begin() const {
    return const_iterator(head->next);
}

template<class Object>
typename List<Object>::iterator List<Object>::end() {
    return iterator(tail);
}

template<class Object>
typename List<Object>::const_iterator List<Object>::end() const {
    return const_iterator(tail);
}

/* List中存放的数据的个数 */
template<class Object>
int List<Object>::size() const {
    return theSize;
}

/* 判断数组是否为空 */
template<class Object>
bool List<Object>::empty() const {
    return theSize == 0;
}

/* 清空数组 */
template<class Object>
void List<Object>::clear() {
    while(!empty()) {
        pop_front();
    }
}

template<class Object>
Object & List<Object>::front() {
    return *begin(); 
}

template<class Object>
const Object & List<Object>::front() const {
    return *begin();
}

template<class Object>
Object & List<Object>::back() {
    return *(-- end()); 
}

template<class Object>
const Object & List<Object>::back() const {
    return *(-- end()); 
}

/* 在开头加入元素 */
template<class Object>
void List<Object>::push_front(const Object & x) {
    insert(begin(), x);    
}

/* 在尾处加入元素 */
template<class Object>
void List<Object>::push_back(const Object & x) {
    insert(end(), x);
}

/* 去掉第一个元素 */
template<class Object>
void List<Object>::pop_front() {
    erase(begin()); 
}

/* 去掉最后一个元素 */
template<class Object>
void List<Object>::pop_back() {
    erase(-- end());
}

/* 插入操作 */
template<class Object>
typename List<Object>::iterator List<Object>::insert(iterator iter, const Object & x) {
    Node *p = iter.current;
    Node *newNode = new Node(x, p->prev, p);
    p->prev->next = p->prev = newNode;
    theSize ++;
    return iterator(newNode);
}

/* 删除操作 
 * 直接让左右两边的指针互指即可，返回的是占用了当前要抹去的遍历器位置的新遍历器  
 */
template<class Object>
typename List<Object>::iterator List<Object>::erase(iterator iter) {
    Node *p = iter.current;
    iterator retVal(p->next);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize --;

    return retVal; 
}

/* 批量删除 */
template<class Object>
typename List<Object>::iterator List<Object>::erase(iterator start, iterator end) {
    for (iterator iter = start; iter != end;) {
        iter = erase(iter);
    } 
    return end;
}

// 初始化
template<class Object>
void List<Object>::init() {
    theSize = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

#endif
