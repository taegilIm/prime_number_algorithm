#include <iostream>
#include "prime_number_algorithm.h"

int main()
{
    /* you can use eulerPhiFunction, calcualte how many coprime numbers are exist,
    pollardRhoFunction, find priem factors,
    millerRabinPrimeTest, judge whether is prime number or not */
    
    /* infinite loop error
    std::cout << eulerPhiFunction(9999999999998); */

    /* max number that can be calculate (unsigned long long)
    std::cout << eulerPhiFunction(18446744073709551615) << std::endl; */

    return 0;
}