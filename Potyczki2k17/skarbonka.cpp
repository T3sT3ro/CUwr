//
// Created by Tooster on 20.11.2017.
//

#include <queue>
#include <cstdio>

using namespace std;

priority_queue<int, vector<int>, greater<int> > Q;


int main() {

    int n;
    scanf("%d", &n);
    while (n--) {
        int a;
        scanf("%d", &a);
        Q.push(a);
    }
    int last = -1;
    while (!Q.empty()) {
        if (last != -1) {
            if (last == Q.top()) {
                Q.pop();
                Q.push(last + 1);
                last = -1;
            } else {
                last = Q.top();
                Q.pop();
            }
        } else {
            last = Q.top();
            Q.pop();
        }
    }
    printf("%d", last);
    return 0;
}
