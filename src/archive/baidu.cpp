// 一面
// 1.RANSAC fit plane
// 2.GN fit plane



// 二面

// 在C++ string类中，提供了两个成员函数可以用来实现字符串分割，一个是find函数，另一个是substr函数，下面看一下这两个函数的声明。

// 对一个字符串，实现一个切分：
// 比方说：
// "a;b;cc;d",  切分符是";"
// 返回值: 
// vector里面存放了{a, b, cc, d}

// 可以利用字符串的find()和substr()函数；
// vector<string> split(const string &str, const string &pattern)；

// std::vector<string> split(const string &str, const string &pattern) {
// 	vector<string> res;
//   int len = str.length();
// 	size_t pre = 0;
//   size_t cur = 0;
//   while (str.find(pattern, pre) != str.end()) {
// 		cur = str.find();
//     res.push_back(str.substr(pre, cur - pre - 1));
// 		pre = cur + pattern.length();
// }
// 	res.push_back(str.substr(cur));
// 	return res;
// }

// c++vector 删除符合条件的元素
// 输入: input_vec中包含整数的vector, flag_vec中包括每个元素的指示值
// true表示删除 false表示保留
// 输出: input_vec, 但其size已经发生变化。
// 要求：尽可能减少空间复杂度， 减少元素移动的次数。
// bool DeleteElements(std::vector<int> *input_vec, const std::vector<bool>& flag_vec) {
// 	auto cmp = [&](i = 0) -> bool {
// 		return !flag_vec[i++];
// 	};
//   sort(input_vec.begin(), input_vec.end(), cmp);
//   int pos = 0;
// 	for (int i = 0; i < flag_vec.size(); i++)
//   	if (!flag_vec[i])
//     	pos += 1;
//   intput_vec.erase(intput_vec.begin() + pos, intput_vec.end());
// }

// struct TreeNode {
// 	int value;
//   TreeNode* left;
//   TreeNode* right;
//   TreeNode(int val):value(val), left(nullptr), right(nullptr) {}
//   TreeNode(int val, TreeNode* l, TreeNode* r):value(val), left(l), right(r) {}
// };


// bool isSymetric(TreeNode* left, TreeNode* right) {
// 	if (!root->left && !root->right)
//     return true;
//   if (!root->left || !root->right)
//     return false;
  
  
//   return (left->val == right->val) && isSymetric(left->left, right->right) 
//     			&& isSymetric(left->right, right->left);
// }

// int main()
// {
// 	TreeNode* root;
//   if (root == nullptr) 
//     flag = true;
  
//   bool flag = isSymetric(root->left, root->right);
	
  
//   return 0;
// }


