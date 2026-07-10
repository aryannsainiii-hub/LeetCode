#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Pair up values with their original indices and sort by value
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());

        // Map original index to its position in the sorted array
        vector<int> sorted_pos(n);
        for (int i = 0; i < n; ++i) {
            sorted_pos[sorted_nodes[i].second] = i;
        }

        // Identify connected components and the greedy next step for each node
        vector<int> comp(n, 0);
        int comp_id = 0;
        comp[0] = comp_id;
        
        for (int i = 1; i < n; ++i) {
            if (sorted_nodes[i].first - sorted_nodes[i - 1].first > maxDiff) {
                comp_id++;
            }
            comp[i] = comp_id;
        }

        // Precompute the binary lifting sparse table
        // up[i][j] stores the index reached from sorted node i after 2^j greedy jumps
        int max_log = 18; // 2^17 >= 10^5
        vector<vector<int>> up(n, vector<int>(max_log));

        int r = 0;
        for (int i = 0; i < n; ++i) {
            while (r < n && sorted_nodes[r].first <= sorted_nodes[i].first + maxDiff) {
                r++;
            }
            up[i][0] = r - 1; // Furthest reachable node to the right
        }

        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i < n; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }

        // Process each query
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0], v = q[1];
            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int id_u = sorted_pos[u];
            int id_v = sorted_pos[v];

            // If they are not in the same connected component, no path exists
            if (comp[id_u] != comp[id_v]) {
                ans.push_back(-1);
                continue;
            }

            // If values are equal but nodes are distinct, distance is 1 (since diff is 0 <= maxDiff)
            if (nums[u] == nums[v]) {
                ans.push_back(1);
                continue;
            }

            // Ensure we are jumping from a smaller value to a larger value
            if (id_u > id_v) {
                swap(id_u, id_v);
            }

            int steps = 0;
            // Lift id_u as high as possible as long as it doesn't reach or pass id_v
            for (int j = max_log - 1; j >= 0; --j) {
                if (up[id_u][j] < id_v) {
                    steps += (1 << j);
                    id_u = up[id_u][j];
                }
            }

            // One final jump is required to reach or exceed id_v
            ans.push_back(steps + 1);
        }

        return ans;
    }
};