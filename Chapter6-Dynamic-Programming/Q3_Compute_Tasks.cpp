#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("hpc.in",ios::in);
	fout.open("hpc.out",ios::out);
	int na, nb, p;
	fin >> na >> nb >> p;
	int **t_k = new int *[p];
	int ***times_single_node = new int **[p]; // 记录第k个节点单独处理i个任务和j个任务所需要的最小时间
	int **from_a_times = new int *[na + 1];	  // 记录第k个节点单独处理i个任务和j个任务所需要的最小时间，其中最后处理的节点是a节点
	int **from_b_times = new int *[na + 1];	  // 记录第k个节点单独处理i个任务和j个任务所需要的最小时间，其中最后处理的节点是b节点
	int ***times = new int **[p];			  // 记录前k个节点共同处理i个任务和j个任务所需要的最小时间
	for (int i = 0; i < p; i++)
	{
		t_k[i] = new int[4];
		for (int j = 0; j < 4; j++)
		{
			fin >> t_k[i][j];
		}
		times_single_node[i] = new int *[na + 1];
		times[i] = new int *[na + 1];
		for (int j = 0; j < na + 1; j++)
		{
			times_single_node[i][j] = new int[nb + 1];
			times[i][j] = new int[nb + 1];
			from_a_times[j] = new int[nb + 1];
			from_b_times[j] = new int[nb + 1];
		}
	}
	for (int k = 0; k < p; k++)
	{
		// 初始化
		times_single_node[k][0][0] = 0;
		from_a_times[0][0] = 0;
		from_a_times[0][0] = 0;
		for (int i = 1; i <= na; i++)
		{
			// 初始化，只处理了a任务，就只有连续处理i个a任务的时间和a任务启动时间
			times_single_node[k][i][0] = t_k[k][2] * i * i + t_k[k][0];
			from_a_times[i][0] = t_k[k][2] * i * i + t_k[k][0];
			from_b_times[i][0] = t_k[k][2] * i * i + t_k[k][0];
		}
		for (int i = 1; i <= nb; i++)
		{
			// 初始化，只处理了b任务，就只有连续处理i个b任务的时间和b任务启动时间
			times_single_node[k][0][i] = t_k[k][3] * i * i + t_k[k][1];
			from_a_times[0][i] = t_k[k][3] * i * i + t_k[k][1];
			from_b_times[0][i] = t_k[k][3] * i * i + t_k[k][1];
		}
		for (int i = 1; i <= na; i++)
		{
			for (int j = 1; j <= nb; j++)
			{
				from_a_times[i][j] = 100000;
				from_b_times[i][j] = 100000;
				for (int u = 1; u <= i; u++)
				{
					// 连续处理u个a任务，之前处理i-u个a任务和j个b任务且最后一个结束的是b任务；取最小值
					from_a_times[i][j] = min(from_b_times[i - u][j] + u * u * t_k[k][2] + t_k[k][0], from_a_times[i][j]);
				}
				for (int u = 1; u <= j; u++)
				{
					// 连续处理u个b任务，之前处理i个a任务和j-u个b任务且最后一个结束的是a任务；取最小值
					from_b_times[i][j] = min(from_a_times[i][j - u] + u * u * t_k[k][3] + t_k[k][1], from_b_times[i][j]);
				}
				times_single_node[k][i][j] = min(from_a_times[i][j], from_b_times[i][j]); // 记录第k个节点单独处理i个任务和j个任务所需要的最小时间
			}
		}
	}
	// 前1个节点处理的最小时间就是第一个节点单独处理的最小时间
	for (int i = 0; i <= na; i++)
	{
		for (int j = 0; j <= nb; j++)
		{
			times[0][i][j] = times_single_node[0][i][j];
		}
	}
	for (int k = 1; k < p; k++)
	{
		for (int i = 0; i <= na; i++)
		{
			for (int j = 0; j <= nb; j++)
			{
				times[k][i][j] = 100000;
				for (int u = 0; u <= i; u++)
				{
					for (int v = 0; v <= j; v++)
					{
						// 前k+1个节点处理任务：前k个节点处理一部分任务，第k+1个节点处理一部分任务，处理时间是二者最大值。u、v变换任务分配取最终最小时间。
						times[k][i][j] = min(times[k][i][j], max(times[k - 1][u][v], times_single_node[k][i - u][j - v]));
					}
				}
			}
		}
	}
	fout << times[p - 1][na][nb];
	fin.close();
	fout.close();
}