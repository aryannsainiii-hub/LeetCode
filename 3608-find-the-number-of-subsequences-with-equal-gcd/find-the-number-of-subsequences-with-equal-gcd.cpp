#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        int MOD = 1e9 + 7;
        int max_val = 0;
        for (int num : nums) {
            max_val = max(max_val, num);
        }

        // dp[g1][g2] stores the number of pairs of disjoint subsequences 
        // with GCD g1 and g2 respectively. 0 represents an empty subsequence.
        vector<vector<int>> dp(max_val + 1, vector<int>(max_val + 1, 0));
        dp[0][0] = 1; // Base case: both subsequences are empty

        for (int x : nums) {
            vector<vector<int>> next_dp = dp;

            for (int g1 = 0; g1 <= max_val; ++g1) {
                for (int g2 = 0; g2 <= max_val; ++g2) {
                    if (dp[g1][g2] == 0) continue;

                    // Choice 1: Add x to the first subsequence
                    int n1 = (g1 == 0) ? x : std::gcd(g1, x);
                    next_dp[n1][g2] = (next_dp[n1][g2] + dp[g1][g2]) % MOD;

                    // Choice 2: Add x to the second subsequence
                    int n2 = (g2 == 0) ? x : std::gcd(g2, x);
                    next_dp[g1][n2] = (next_dp[g1][n2] + dp[g1][g2]) % MOD;
                }
            }
            dp = move(next_dp);
        }

        long long ans = 0;
        // Sum up all pairs where g1 == g2 and they are non-empty (g1 > 0)
        for (int g = 1; g <= max_val; ++g) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};