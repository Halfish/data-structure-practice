/*************************************************************************
	> File Name: testList.cpp
	> Author: Bruce Zhang
	> Mail: zhangxb.sysu@gmail.com 
	> Created Time: 2015年11月25日 星期三 14时52分29秒
 ************************************************************************/

#include <iostream>
#include "List.cpp"
using namespace std;

int main(int argc, char **argv) {
    List<int> l;
    for (int i = 0; i < 10; ++ i) {
        l.push_back(i * 3);
    }
    l.pop_front();
    l.pop_back();
    cout << l.front() << endl;
    cout << l.back() << endl;
    cout << l.size() << endl;

    for(List<int>::iterator iter = l.begin(); iter != l.end(); ++ iter) {
        cout << *iter << " ";
    }
    cout << endl;

    for(List<int>::iterator iter = l.begin(); iter != l.end(); ++ iter) {
        if (*iter < 10) {
            l.erase(iter);
        }
    }

    for(List<int>::iterator iter = l.begin(); iter != l.end(); ++ iter) {
        cout << *iter << " ";
    }
    cout << endl;
    cout << l.size() << endl;

    return 0;
}

