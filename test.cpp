#include <ctime>
#include <cmath>
#include <iostream>
#include "Tree23.h"
#include "test.h"

using namespace std;


void sRand() {
    srand(time(0));
    RRand = (INT_64) rand();
}

INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

//Тест трудоёмкости операций случайного BST-дерева

void test_rand(int n) {

    Tree23<INT_64> tree;
    auto *m = new INT_64[n];
    sRand();

    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree.insert(m[i], 1);
    }

    cout << "items count: " << tree.getSize() << endl;

    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {
            tree.remove(LineRand());
            D += tree.getStat();
            tree.insert(m[rand() % n], 1);
            I += tree.getStat();
            try {
                tree.getValue(LineRand());
                S += tree.getStat();
            }
            catch (int) { S += tree.getStat(); }
        } else {
            int ind = rand() % n;
            tree.remove(m[ind]);
            D += tree.getStat();
            INT_64 key = LineRand();
            tree.insert(key, 1);
            I += tree.getStat();
            m[ind] = key;
            try {
                tree.getValue(m[rand() % n]);
                S += tree.getStat();
            }
            catch (int) { S += tree.getStat(); }
        }

    cout << "items count: " << tree.getSize() << endl;
//теоретической оценки трудоёмкости операций BST
    cout << "theoretical: log3(n) - log2(n) = " << (log(n) / log(3.0)) << " - " << (log(n) / log(2.0)) << endl;
//экспериментальной оценки трудоёмкости вставки
    cout << "count insert: " << I / (n / 1.5) << endl;
//экспериментальной оценки трудоёмкости удаления
    cout << "count delete: " << D / (n / 1.5) << endl;
//экспериментальной оценки трудоёмкости поиска
    cout << "count search: " << S / (n / 1.5) << endl;
    delete[] m;
}

//Тест трудоёмкости операций вырожденного BST-дерева

void test_ord(int n) {

    Tree23<INT_64> tree;
    INT_64 *m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.insert(m[i], 1);
    }

    cout << "items count: " << tree.getSize() << endl;

    double I = 0;
    double D = 0;
    double S = 0;
    sRand();

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);
            tree.remove(k);
            D += tree.getStat();
            tree.insert(m[rand() % n], 1);
            I += tree.getStat();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2);
            try {
                tree.getValue(k);
                S += tree.getStat();
            }
            catch (int) { S += tree.getStat(); }
        } else {
            int ind = rand() % n;
            tree.remove(m[ind]);
            D += tree.getStat();
            int k = LineRand() % (10000 * n);
            k = k + k % 2;
            tree.insert(k, 1);
            I += tree.getStat();
            m[ind] = k;
            try {
                tree.getValue(m[rand() % n]);
                S += tree.getStat();
            }
            catch (int) { S += tree.getStat(); }
        }
    }

    cout << "items count: " << tree.getSize() << endl;
//теоретической оценки трудоёмкости операций BST
    cout << "theoretical: log3(n) - log2(n) = " << log(n) / log(3.0) << " - " << (log(n) / log(2.0)) << endl;
//экспериментальной оценки трудоёмкости вставки
    cout << "count insert: " << I / (n / 1.5) << endl;
//экспериментальной оценки трудоёмкости удаления
    cout << "count delete: " << D / (n / 1.5) << endl;
//экспериментальной оценки трудоёмкости поиска
    cout << "count search: " << S / (n / 2.5) << endl;

    delete[] m;
}