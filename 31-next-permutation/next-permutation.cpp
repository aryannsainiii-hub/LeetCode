class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;

        // Step 1: Find the first decreasing element from the right
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // If a breakpoint was found
        if (i >= 0) {
            // Step 2: Find the element just larger than nums[i] from the right
            int j = n - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            // Swap them
            swap(nums[i], nums[j]);
        }

        // Step 3: Reverse the elements to the right of index i
        reverse(nums.begin() + i + 1, nums.end());
    }
};