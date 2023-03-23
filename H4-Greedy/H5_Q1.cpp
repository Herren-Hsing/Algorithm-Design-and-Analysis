#include <iostream>
#include <algorithm>
using namespace std;
int k, n, s;
bool in_cache(int x, int &pos, int *cache) // 判断是否在缓存区，并得到在缓存区的位置
{
	for (int i = 0; i < n; i++)
	{
		if (cache[i] == x)
		{
			pos = i;
			return true;
		}
	}
	return false;
}
void get_last(int index, int &delete_pos, int *cache, int *requests) // 得到缓存区中在请求中最晚出现的元素
{
	int *visited = new int[k]; // 存放缓存区每个元素在请求中的位置
	for (int i = 0; i < k; i++)
	{
		visited[i] = 0;
	}
	for (int i = index; i < s; i++) // 遍历未请求的请求序列
	{
		int pos = 0;
		if (in_cache(requests[i], pos, cache))
		{
			if (!visited[pos]) // 如果之前该元素并未请求过，更新其请求序号
			{
				visited[pos] = i;
			}
		}
	}
	// 缓存区可能存在一些元素，之后再也不会被请求，这里删除他们中最大的
	int *never_appear = new int[k];
	for (int i = 0; i < k; i++)
	{
		never_appear[i] = 0;
	}
	int index_of_never_appear = 0;
	for (int i = 0; i < k; i++)
	{
		if (!visited[i])
		{
			never_appear[index_of_never_appear++] = cache[i];
		}
	}
	if (index_of_never_appear)
	{
		int delete_ele = *(max_element(never_appear, never_appear + n));
		for (int i = 0; i < n; i++)
		{
			if (cache[i] == delete_ele)
			{
				delete_pos = i;
				delete never_appear;
				delete visited;
				return;
			}
		}
	}
	// 如果不存在再也不会被请求的元素，那么就删除缓存区最后一个被访问的元素，得到visited数组中的最大元素，就是要删除的元素
	delete_pos = max_element(visited, visited + n) - visited;
	delete[] visited;
	delete[] never_appear;
}
int main()
{
	cin >> k >> n >> s;
	int *cache = new int[k];	// 缓存
	int *requests = new int[s]; // 请求
	int pos = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> cache[i];
	}
	for (int i = 0; i < s; i++)
	{
		cin >> requests[i];
	}
	for (int i = 0; i < s; i++) // 遍历请求
	{
		if (in_cache(requests[i], pos, cache)) // 如果在缓存区，继续请求
		{
			continue;
		}
		int sub = k - n;
		if (sub--) // 如果不在缓存区且缓存区不满，加入缓存区
		{
			cache[n++] = requests[i];
			continue;
		}
		// 缓存区满且不在缓存区，需要删掉缓存区内最后出现的
		int delete_pos = 0;
		get_last(i + 1, delete_pos, cache, requests);
		cout << cache[delete_pos] << ' ';
		cache[delete_pos] = requests[i]; // 替换缓存区删除的元素
	}
	delete[] cache;
	delete[] requests;
}