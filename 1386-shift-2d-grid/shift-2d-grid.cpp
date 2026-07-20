class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;
        
        k = k % total;
        
        vector<vector<int>> result(m, vector<int>(n));
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int flatIndex = r * n + c;
                
                int newFlatIndex = (flatIndex + k) % total;
                
                int newRow = newFlatIndex / n;
                int newCol = newFlatIndex % n;
                
                result[newRow][newCol] = grid[r][c];
            }
        }
        
        return result;
    }
};