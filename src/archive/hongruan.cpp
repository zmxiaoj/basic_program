
#include<bits/stdc++.h>
/** code1
 * @brief 给定义只包含A B的字符串，根据规则计算字符串得分
 * 已知字符串S只包含A,B两种字符，设X为S中所有A的索引的集合，Y为S中所有B的索引的集合。
 * 若S满足以下条件，则称S为有序字符串。
 * X与Y之间存在双射f，满足\forall i\in X, f(i)>i
   给定有序字符串S，按照下述规则计算S的分数，设P,Q分别为有序字符串
   1.AB的分数 = 1
   2.PQ的分数 = P的分数+Q的分数
   3.APB的分数 = 2*P的分数
 * 
 */

using namespace std;

int main()
{
    string str;
    cin >> str;
    auto check = [&](string& s, int l, int r) -> bool {
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            if (s[i] == 'A') cnt++;
            else cnt--;
            if (cnt < 0) return false;
        }
        return cnt == 0;
    };
    function<int(string&, int, int)> dfs = [&](string& s, int l, int r) -> int {
        if (l + 1 == r && s.substr(l, 2) == "AB")
            return 1;
        for (int i = l; i < r; i++) {
            if (check(s, l, i) && check(s, i + 1, r))
                return dfs(s, l, i) + dfs(s, i + 1, r);
        }
        if (s[l] == 'A' && s[r] == 'B') 
            return 2 * dfs(s, l + 1, r - 1);
    };
    int res = dfs(str, 0, str.length() - 1);
    cout << res << endl;
    return 0;
}

/** code2
 * @brief 有红、绿、蓝三种颜色（分别用R、G、B表示）的小球，其数量分别为a,b,c。
 * 现在想将这些小球排成一列，但不希望相邻的两个小球出现相同颜色，请问有多少种排列方法?
 * 
 */