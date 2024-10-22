// 题目一：

// 给你一个链表数组，每个链表都已经按升序排列。

// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

// 示例 1：

// 输入：lists = [[1,4,5],[1,3,4],[2,6]]
// 输出：[1,1,2,3,4,4,5,6]
// 解释：链表数组如下：
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// 将它们合并到一个有序链表中得到。
// 1->1->2->3->4->4->5->6
// 示例 2：

// 输入：lists = []
// 输出：[]
// 示例 3：

// 输入：lists = [[]]
// 输出：[]

// Code:







// ----------------------------------------------------------------------------------------------
// 题目二：

// 给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的排列。如果是，返回 true ；否则，返回 false 。

// 换句话说，s1 的排列之一是 s2 的 子串 。

 

// 示例 1：

// 输入：s1 = "ab" s2 = "eidbaooo"
// 输出：true
// 解释：s2 包含 s1 的排列之一 ("ba").
// 示例 2：

// 输入：s1= "ab" s2 = "eidboaoo"
// 输出：false
 

// 提示：

// 1 <= s1.length, s2.length <= 104
// s1 和 s2 仅包含小写字母



// Code:

#include <bits/stdc++.h>

using namespace std;

class solution
{
	int len1 = s1.length();
  int len2 = s2.length();
  unordered_map<char, int> hmap;
  for (auto& c : s1) {
    if (hmap.find(c) == hmap.end())
      hmap[c] = 1;
		hmap[c] += 1;
  }
    
    
  
  auto check = [](unordered_map<char, int>& hmap) -> bool {
  	for (auto& p : hmap)
      if (p.second != 0)
        return false;
   	return true;
  };
  
  for (int l = 0, r = 0; r < len2; r++) {
    // for (int i = 0; i < len1; i++) {
    	hmap[s2[r]] -= 1;
    //  r += 1;
    // }
 
    if (check(hmap))
      return true;
   	while (r - l + 1 >= len1) {
    	hmap[s2[l]] += 1;
      l += 1;
      if (check(hmap))
        return true;
    }
  }
  return false;
}





// 09.11
//test

// 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。

// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。

// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

// 示例 1：

// 输入：k = 2, prices = [2,4,1]
// 输出：2
// 解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
// 示例 2：

// 输入：k = 2, prices = [3,2,6,5,0,3]
// 输出：7
// 解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
//      随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 

// 提示：

// 1 <= k <= 100
// 1 <= prices.length <= 1000
// 0 <= prices[i] <= 1000


// class Solution {
// public:
//     int maxProfit(int k, vector<int>& prices) {
// 			int n = prices.size();
//       vector<vector<vector<int>>> dp(n, vector<vector<int>>(k, vector<int>(2, 0)));
//       // dp[][][0] dp[][][1]
//       for (int i = 1; i < n; i++) {
//       	for (int j = 1; j < k; j++) {
//         	dp[i][j][0] = 0;
//           dp[i][j][1] = INT_MIN;
//         }
//       }
      
//       for (int i = 1; i < n; i++) {
//       	for (int j = 1; j < k; j++) {
//         	dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
//           dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
//         }
//       }
//       int res = 0;
//       for (int i = 1; i < n; i++) {
//       	for (int j = 1; j < k; j++) {
// 					res = max(res, dp[i][j][0]);
//         }
//       }
//       return res;
//     }
// };











