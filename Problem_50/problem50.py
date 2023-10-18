from sympy import *

def alg(n):
    primes =[]
    i=2
    while sum(primes)<n:
        if isprime(i):
            primes.append(i)
        i=i+1
    fin_seq=[];l=len(primes);j=l
    while j!= 0:
        i=0
        while i+j<l+1:
            seq = primes[i:i+j]
            if sum(seq)<=n:
                if isprime(sum(seq)):
                    if len(seq)>len(fin_seq):
                        fin_seq = seq
            i=i+1
        j=j-1
    return(sum(fin_seq))
print(alg(1))