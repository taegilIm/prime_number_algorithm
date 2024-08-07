import random as rd
import time as t

from collections import Counter


def Miller_Rabin_Primality_Test(target: int) -> bool | None:
    if target == 1:
        return None

    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]

    def Operation(prime: int, expo: int) -> int:
        prime %= target

        result = 1
        while expo:
            if expo % 2 == 1:
                result = (prime * result) % target
            prime = (prime**2) % target
            expo //= 2
        return result

    for i in primes:
        expo = target - 1
        while True:
            result = Operation(i, expo)
            if result == target - 1:
                return True
            if expo % 2 == 1:
                return result == 1
            expo //= 2


def gcd(x: int, y: int) -> int:
    if x < y:
        x, y = y, x

    while y != 0:
        temp = x % y
        x = y
        y = temp
    return x


def Pollard_Rho_Function(target: int) -> int | None:
    start = t.time()

    if target == 1:
        return None
    if target % 2 == 0:
        return 2
    if target == 25:
        return 5

    def Fn(x: int, c: int) -> int:
        return (x**2 + c) % target

    x = y = rd.randint(2, target - 1)
    c = rd.randint(1, target - 1)

    factor = 1
    while factor == 1:
        x = Fn(x, c)
        y = Fn(Fn(y, c), c)
        factor = gcd(abs(x - y), target)

        end = t.time()
        if (end - start) > 20:
            print("falied to find factors")
            return None

    if Miller_Rabin_Primality_Test(factor):
        return factor
    else:
        return Pollard_Rho_Function(factor)


def Euler_Phi_Function(target: int) -> int | None:
    if target == 1:
        return None

    factors = []

    def Find_Prime_Factors(target: int) -> None:
        while target > 1:
            temp = Pollard_Rho_Function(target)
            factors.append(temp)
            target //= temp

    print("calculating...")
    Find_Prime_Factors(target)

    result = 1
    for item, count in Counter(factors).items():
        result *= (item ** (count - 1)) * (item - 1)

    return result
