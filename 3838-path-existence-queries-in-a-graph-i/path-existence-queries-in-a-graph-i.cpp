class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // comp[i] will store the component ID for node i
        vector<int> comp(n, 0);
        int current_id = 0;
        
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] > maxDiff) {
                current_id++; // Break the chain, start a new component
            }
            comp[i] = current_id;
        }
        
        vector<bool> answer;
        answer.reserve(queries.size());
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            answer.push_back(comp[u] == comp[v]);
        }
        
        return answer;
    }
};