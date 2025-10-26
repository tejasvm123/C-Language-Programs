// Solution 1
// class Solution {
// public:
//     static bool compare(vector<int> a,vector<int> b){
//         if(a[0] != b[0]){
//             return a[0] < b[0];
//         }
//         return a[1] > b[1];
//     }
//     int lis(vector<int>& hts,int index,int prev,vector<vector<int>>& memo){
//         if(index >= hts.size()){
//             return 0;
//         }
//         if(memo[index][prev+1] != -1){
//             return memo[index][prev+1];
//         }
//         int take = 0;
//         if(prev == -1 || hts[index] > hts[prev]){
//             take = 1 + lis(hts,index+1,index,memo);
//         }
//         int notTake = lis(hts,index+1,prev,memo);
//         return memo[index][prev+1] = max(take,notTake);
//     }
//     int maxEnvelopes(vector<vector<int>>& envelopes) {
//         sort(envelopes.begin(),envelopes.end(),compare);
//         vector<int> hts;
//         for(auto temp:envelopes){
//             hts.push_back(temp[1]);
//         }
//         int n = hts.size();
//         vector<vector<int>> memo(n,vector<int>(n+1,-1));
//         return lis(hts,0,-1,memo);
//     }
// };

//Solution 2
class Solution {
public:
    static bool compare(vector<int>& a, vector<int>& b) {
        if (a[0] != b[0])
            return a[0] < b[0];
        return a[1] > b[1]; 
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), compare);

        vector<int> heights;
        for (auto& env : envelopes) {
            heights.push_back(env[1]);
        }

        vector<int> lis; 

        for (int h : heights) {
            auto it = lower_bound(lis.begin(), lis.end(), h);
            if (it == lis.end()) {
                lis.push_back(h);
            } else {
                *it = h; 
            }
        }

        return lis.size();
    }
};
