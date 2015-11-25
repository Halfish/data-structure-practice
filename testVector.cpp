/*************************************************************************
	> File Name: testVector.cpp
	> Author: Bruce Zhang
	> Mail: zhangxb.sysu@gmail.com 
	> Created Time: 2015年11月24日 星期二 14时55分39秒
 ************************************************************************/

#include <iostream>
#include "Vector.cpp"
using namespace std;

int main(int argc, char **argv) {
    Vector<int> v;
    v.reserve(25);
    for (int i = 0; i < 20; ++ i) {
        v.push_back(i * 3);
    }
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    cout << v.front() << endl;
    cout << v.back() << endl;
    for (Vector<int>::iterator iter = v.begin(); iter != v.end(); ++ iter) {
        cout << "iter = " << *iter << endl;
    }

    Vector<int> v2 = v;
    cout << v2[9] << endl;
    v2.clear();
    v2.push_back(4);
    cout << v2.front() << endl;
    cout << v2.size() << endl;

    return 0;
}
