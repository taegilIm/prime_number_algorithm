#include <vector>
#include <unordered_map>
#include <ctime>
#include <random>

#define ull unsigned long long

// base ^ multiplier % target
ull _millerRabinOperator(ull base, ull multiplier, ull target)
{
    ull result = 1;

    // if target < base
    base %= target;
    while (multiplier)
    {
        if (multiplier % 2 == 1)
            result = (base * result) % target;
        base = (base * base) % target;
        multiplier /= 2;
    }
    return result;
}

/* this function is judge which target number is prime or not
 * 0 means the number is not prime and 1 means prime
 *
 * - example
 *  cout << millerRabinPrimeTest(2);  // 1
 *  cout << millerRabinPrimeTest(3);  // 1
 *  cout << millerRabinPrimeTest(4);  // 0
 */
bool millerRabinPrimeTest(ull target)
{
    ull _primalityBase[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (ull base : _primalityBase)
    {
        if (base % target == 0)
            return true;
        ull multiplier = target - 1;
        while (true)
        {
            ull temp = _millerRabinOperator(base, multiplier, target);
            if (temp == target - 1)
                return true;
            if (multiplier % 2 == 1)
                return temp == 1;
            multiplier /= 2;
        }
    }
    // end of function pseudo return
    return 0;
}

// gcd(n1, n2)
ull gcd(ull n1, ull n2)
{
    if (n1 < n2)
    {
        ull temp = n2;
        n2 = n1;
        n1 = temp;
    }
    ull temp;
    while (n2 != 0)
    {
        temp = n1 % n2;
        n1 = n2;
        n2 = temp;
    }
    return n1;
}

// (x ^ 2 + c) % N
ull _fn(ull target, ull constant, ull mod)
{
    return (target * target + constant) % mod;
}

/* this function is finding target numbers prime factors
 *
 *  - example
 *  pollardRhoFunction(10) // 2
 *  pollardRhoFunction(30) // 2
 *  pollardRhoFunction(99) // 3
 */
ull pollardRhoFunction(ull target)
{
    if (target == 1)
        return target;
    if (target % 2 == 0)
        return 2;
    if (target == 25)
        return 5;

    // if target is prime number
    if (millerRabinPrimeTest(target))
        return target;

    // random generate number
    std::mt19937_64 mt(time(NULL));
    std::uniform_int_distribution<ull int> xy_dist(2, target - 1);
    std::uniform_int_distribution<ull int> c_dist(1, target - 1);

    ull x, y, c;
    x = y = xy_dist(mt);
    c = c_dist(mt);

    ull factor = 1;
    while (factor == 1)
    {
        x = _fn(x, c, target);
        y = _fn(_fn(y, c, target), c, target);
        factor = gcd(x > y ? x - y : y - x, target);
        if (factor == target)
            return pollardRhoFunction(target);
    }

    // if factor is prime number, factor is prime factor
    if (millerRabinPrimeTest(factor))
        return factor;
    else
        return pollardRhoFunction(factor);
}

/* this function find all of target number's prime factor using pollard rho function
 *
 * - example
 * findPrimeFactors(10) // {2, 5}
 * findPrimeFactors(20) // {2, 2, 5}
 */
std::vector<ull> findPrimeFactors(ull target)
{
    std::vector<ull> factors;

    while (target > 1)
    {
        ull factor = pollardRhoFunction(target);
        factors.push_back(factor);
        target /= factor;
    }
    return factors;
}

ull _power(ull target, ull exponent)
{
    if (exponent == 0)
        return 1;

    ull temp = 1;
    for (int i = 0; i < exponent; i++)
        temp *= target;
    return temp;
}

/* this function find all of target number's primality numbers
 *
 * - example
 * eulerPhiFunction(2) // 1
 * eulerPhiFunction(19) // 18
 * eulerPhiFunction(20) // 8
 */
ull eulerPhiFunction(ull target)
{
    // if target number is prime number, to phi algorithm, result is N -1
    if (millerRabinPrimeTest(target))
        return target - 1;

    // find prime factors
    std::vector<ull> factors = findPrimeFactors(target);

    std::unordered_map<ull, ull> count;
    for (ull i : factors)
        count[i]++;

    ull result = 1;
    for (auto i : count)
    {
        result *= _power(i.first, i.second - 1) * (i.first - 1);
    }
    return result;
}
