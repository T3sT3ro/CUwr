//
// Created by Tooster on 17.02.2018.
//

// http://www.usaco.org/current/data/sol_cowjog_gold.html

#include "bits/stdc++.h"

using namespace std;

struct Person {
    int t, ID, f;
    bool teacher = false;

    bool operator<(const Person &rhs) const { return t < rhs.t; }

    Person(int t, int ID, int f, bool teacher) : t(t), ID(ID), f(f), teacher(teacher) {}
};

vector<Person> Q;

queue<Person> students;
queue<Person> teachers;

bool departed[101];

int main() {
    int n, w, c, m;
    scanf("%d %d %d %d", &n, &w, &c, &m);
    int _time = 0;
    int _ride = 0;
    for (int i = 0; i < n; ++i) {
        int ID, ti, fl; // fl < 0 for teacher and > 0 for student
        scanf("%d %d %d", &ID, &ti, &fl);
        Q.push_back(Person(ti, i + 1, fl, ID == 2));
    }
    sort(Q.begin(), Q.end());

    int rory_t = 0;
    int last_t = 0;
    int last_id = Q[0].ID;
    int cc = 0;
    vector<Person> passengers;
    int t = 1;
    int wait = -1;
    for (int t = 1; t < 2000; ++t) {
        if (Q.empty() && teachers.empty() && students.empty() && passengers.empty())
            break;
        if (Q.back().t == t) {
            Person p = Q.back();
            Q.pop_back();
            if (p.teacher)
                teachers.push(p);
            else
                students.push(p);
        }
        if(!teachers.empty()){

        }
    }

    return 0;
}