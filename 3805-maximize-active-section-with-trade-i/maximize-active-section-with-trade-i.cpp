#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxActiveSectionsAfterTrade(std::string s) {        std::string t = "1" + s + "1";
        
        int initial_ones = 0;
        for (char c : s) {
            if (c == '1') initial_ones++;
        }

        std::vector<std::pair<char, int>> segments;
        for (char c : t) {
            if (segments.empty() || segments.back().first != c) {
                segments.push_back({c, 1});
            } else {
                segments.back().second++;
            }
        }

        int max_delta = 0;

        for (int i = 1; i < (int)segments.size() - 1; ++i) {
            if (segments[i].first == '1' && segments[i - 1].first == '0' && segments[i + 1].first == '0') {
                int left_zeros = segments[i - 1].second;
                int right_zeros = segments[i + 1].second;
                max_delta = std::max(max_delta, left_zeros + right_zeros);
            }
        }

        return initial_ones + max_delta;
    }
};