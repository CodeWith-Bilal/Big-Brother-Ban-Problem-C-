import sys
from typing import List

def solve(N: int, K: int, A: List[int], B: List[int], C: List[int], D: List[int]) -> float:
    """
    Return the best score you can achieve in the Daily Run.
    
    N: number of stages
    K: number of turns each lure lasts
    A: list containing the health points of the first Pokemon in each stage
    B: list containing the turns it takes to beat each stage if it were a singles battle
    C: list containing the health points of the additional Pokemon in each stage
    D: list containing the turns it takes to beat each stage if it were a doubles battle
    """
    # Binary search on the score X
    low, high = 0.0, 1e12
    for _ in range(60):  # Sufficient iterations for 10^-5 precision
        mid = (low + high) / 2
        # Compute benefit for making each stage doubles
        benefit = [0.0] * (N + 1)
        for i in range(2, N + 1):
            benefit[i] = C[i] - mid * (D[i] - B[i])
        
        # Compute prefix sums for benefits
        prefix = [0.0] * (N + 1)
        for m in range(2, N + 1):
            prefix[m] = prefix[m - 1] + benefit[m]
        
        # DP to find maximum benefit sum
        F = [0.0] * (N + 2)
        for i in range(N, 1, -1):
            L = min(i + K - 1, N)
            sum_benefit = prefix[L] - prefix[i - 1]
            F[i] = max(F[i + 1], sum_benefit + F[L + 1])
        
        # Compute constant term
        constant = sum(A[i] - mid * B[i] for i in range(1, N + 1))
        max_S = constant + F[2]
        
        # Update binary search bounds
        if max_S >= 0:
            low = mid
        else:
            high = mid
    
    return (low + high) / 2

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        A = [0] + list(map(int, input().split()))  # 1-based indexing
        B = [0] + list(map(int, input().split()))
        C = [0] + list(map(int, input().split()))
        D = [0] + list(map(int, input().split()))
        print(f"{solve(N, K, A, B, C, D):.10f}")

if __name__ == '__main__':
    main()