#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct node // 节点结构体，包含节点的值、左右孩子、是否是叶节点
{
	int value;
	node *left;
	node *right;
	bool isLeaf = 0;
	node(int x, node *l, node *r)
	{
		value = x;
		left = l;
		right = r;
	}
	node(int x, bool y)
	{
		value = x;
		isLeaf = y;
		left = nullptr;
		right = nullptr;
	}
};
struct cmp
{
	bool operator()(node *&a, node *&b) const // 重载>运算符，在进入优先队列时，节点的比较是节点value值的比较
	{
		return a->value > b->value;
	}
};
// 根据树的层次遍历，计算每个叶子节点的距离根节点的高度；所有的叶子节点的value值*高度加起来除以value总和就是
double get_res(node *root)
{
	double ans = 0, sum_value = 0;
	int curNum = 1, nextNum = 0;
	if (root)
	{
		queue<node *> s;
		s.push(root);
		int level = 0;
		while (!s.empty())
		{
			node *head = s.front();
			s.pop();
			if (head->isLeaf)
			{
				ans += level * head->value; // 计算叶子节点高度*value总和

				sum_value += head->value; // 计算value总和
			}
			curNum--;
			if (head->left)
			{
				s.push(head->left);
				nextNum++;
			}
			if (head->right)
			{
				s.push(head->right);
				nextNum++;
			}
			if (!curNum)
			{
				curNum = nextNum;
				nextNum = 0;
				level++;
			}
		}
	}
	return ans / sum_value;
}
int main()
{
	int n;
	cin >> n;
	priority_queue<node *, vector<node *>, cmp> frequency; // 优先队列，按照自定规则升序排序
	node *tmp;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		tmp = new node(x, 1);
		frequency.push(tmp);
	}
	while (frequency.size() != 1) // 当只有一个节点时，结束循环
	{
		// 取出value最小的两个节点
		node *sym1 = frequency.top();
		frequency.pop();
		node *sym2 = frequency.top();
		frequency.pop();
		node *sum = new node(sym1->value + sym2->value, sym1, sym2); // 新节点是value最小两个节点的父母，其value是二者value的和
		frequency.push(sum);										 // 将新节点入优先队列
	}
	node *root = frequency.top(); // 队列中唯一一个节点是构建霍夫曼树的根节点
	cout <<get_res(root);
}