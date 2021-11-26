#include"miller_rabin.cpp"
#include<bits/stdc++.h>

//continued from MillerRabin
ll PollardRho(ll n) {
    ll x = rand()%(n-2) + 2;
    ll y = x;
    ll c = rand()%(n-1) + 1;
    while (true) {
        x = (mul(x, x, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        ll d = gcd(abs(x-y), n);
        if (d == 1) continue;
        if (!isPrime(d)) return PollardRho(d);
        else return d;
    }
}

void f(ll n, vector<ll>& v) {
    while (!(n&1)) {
        n >>= 1;
        v.push_back(2);
    }
    if (n == 1) return;
    while (!isPrime(n)) {
        ll d = PollardRho(n);
        while (n%d == 0) {
            v.push_back(d);
            n /= d;
        }
        if (n == 1) break;
    }
    if (n != 1) v.push_back(n);
}