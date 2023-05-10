#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int n = 4;
struct node
{
	int teacher;	// �ýڵ��Ӧ����ʦ
	int lesson;		// �ýڵ����Ŀγ�
	int cur_time;	// Ŀǰ�������ýڵ㣩���ܱ���ʱ��
	int visited[n]; // �����ʦi���޷�������
	int sum_time;	// ��ʱ���½�
	node()			// ���ڵ�Ĺ��캯��
	{
		cur_time = 0;
		teacher = -1;
		lesson = -1;
		for (int i = 0; i < n; i++)
		{
			visited[i] = -1;
		}
		sum_time = 0;
	}
	// �ӽڵ�Ĺ��캯��
	node(node *a, int i, int (*array)[n])
	{
		for (int j = 0; j < n; j++)
		{
			visited[j] = a->visited[j]; // ����Ѿ��������ʦ
		}
		teacher = i;
		visited[i] = a->lesson + 1;				   // ����ʦ�õ�����
		lesson = a->lesson + 1;					   // ���䵽������һ���γ�
		cur_time = a->cur_time + array[i][lesson]; // Ŀǰʱ����ϱ��η����ʱ��
		sum_time = cur_time;					   // ��ʱ���½���Ŀǰʱ�����֮���ʱ���½�
		// ����δ����Ŀγ̣���ÿ���γ�δ������ʦ�ı���ʱ����Сֵ�ļӺ�
		for (int i = lesson + 1; i < n; i++)
		{
			int min_time = 999;
			for (int j = 0; j < n; j++)
			{
				if ((min_time > array[j][i]) && (visited[j] == -1))
				{
					min_time = array[j][i];
				}
			}
			sum_time += min_time;
		}
	}
};

struct cmp
{
	bool operator()(node *&a, node *&b) const // ����>��������ڽ������ȶ���ʱ���ڵ�ıȽ��ǽڵ�sum_timeֵ�ıȽ�
	{
		return a->sum_time > b->sum_time;
	}
};

void dfs(int (*array)[n])
{
	priority_queue<node *, vector<node *>, cmp> q;
	node *root = new node;
	int bound = 9999;			  // ���пγ̷��������ʱ���½�
	while (root->lesson != n - 1) // �����һ���Ѿ�����Ŀγ���n-1ʱ�����пγ̷�����ɣ�����ѭ��
	{
		for (int i = 0; i < n; i++)
		{
			if (root->visited[i] == -1) // ��ʦiδ��������
			{
				node *next = new node(root, i, array); // �½��ӽڵ�
				if (next->sum_time > bound)			   // ���Ԥ�ڵ���ʱ���½����Ŀǰ���������ʱ���½磬��֦
				{
					delete next;
				}
				else
				{
					q.push(next);			   // ���ýڵ�ѹ�����ȶ���
					if (next->lesson == n - 1) // �������������пγ̣������½�
					{
						bound = next->sum_time;
					}
				}
			}
		}
		root = q.top();
		q.pop();
	}
	cout << "���ŷ���Ϊ" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "��" << i << "λ��ʦ�����" << root->visited[i] << "�ſγ�" << endl;
	}
	cout << "��С�ܱ���ʱ��Ϊ��" << root->sum_time<<endl;
}

int main()
{
	int array[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> array[i][j];
		}
	}
	dfs(array);
}