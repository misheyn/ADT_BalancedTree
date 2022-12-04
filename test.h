#ifndef ADT_BALANCEDTREE_TEST_H
#define ADT_BALANCEDTREE_TEST_H

typedef unsigned long long INT_64;

static INT_64 RRand = 15750;
const INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

void sRand();

INT_64 LineRand();

void test_rand(int n);

void test_ord(int n);

#endif //ADT_BALANCEDTREE_TEST_H
