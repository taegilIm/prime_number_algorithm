#pragma once

#include "prime_number_algorithm.cpp"

ull gcd(ull n1, ull n2);
bool millerRabinPrimeTest(ull target);
ull pollardRhoFunction(ull target);
std::vector<ull> findPrimeFactors(ull target);
ull eulerPhiFunction(ull target);