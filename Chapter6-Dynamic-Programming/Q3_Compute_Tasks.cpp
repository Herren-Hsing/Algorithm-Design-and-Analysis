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
	int ***times_single_node = new int **[p]; // ��¼��k���ڵ㵥������i�������j����������Ҫ����Сʱ��
	int **from_a_times = new int *[na + 1];	  // ��¼��k���ڵ㵥������i�������j����������Ҫ����Сʱ�䣬���������Ľڵ���a�ڵ�
	int **from_b_times = new int *[na + 1];	  // ��¼��k���ڵ㵥������i�������j����������Ҫ����Сʱ�䣬���������Ľڵ���b�ڵ�
	int ***times = new int **[p];			  // ��¼ǰk���ڵ㹲ͬ����i�������j����������Ҫ����Сʱ��
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
		// ��ʼ��
		times_single_node[k][0][0] = 0;
		from_a_times[0][0] = 0;
		from_a_times[0][0] = 0;
		for (int i = 1; i <= na; i++)
		{
			// ��ʼ����ֻ������a���񣬾�ֻ����������i��a�����ʱ���a��������ʱ��
			times_single_node[k][i][0] = t_k[k][2] * i * i + t_k[k][0];
			from_a_times[i][0] = t_k[k][2] * i * i + t_k[k][0];
			from_b_times[i][0] = t_k[k][2] * i * i + t_k[k][0];
		}
		for (int i = 1; i <= nb; i++)
		{
			// ��ʼ����ֻ������b���񣬾�ֻ����������i��b�����ʱ���b��������ʱ��
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
					// ��������u��a����֮ǰ����i-u��a�����j��b���������һ����������b����ȡ��Сֵ
					from_a_times[i][j] = min(from_b_times[i - u][j] + u * u * t_k[k][2] + t_k[k][0], from_a_times[i][j]);
				}
				for (int u = 1; u <= j; u++)
				{
					// ��������u��b����֮ǰ����i��a�����j-u��b���������һ����������a����ȡ��Сֵ
					from_b_times[i][j] = min(from_a_times[i][j - u] + u * u * t_k[k][3] + t_k[k][1], from_b_times[i][j]);
				}
				times_single_node[k][i][j] = min(from_a_times[i][j], from_b_times[i][j]); // ��¼��k���ڵ㵥������i�������j����������Ҫ����Сʱ��
			}
		}
	}
	// ǰ1���ڵ㴦�����Сʱ����ǵ�һ���ڵ㵥���������Сʱ��
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
						// ǰk+1���ڵ㴦������ǰk���ڵ㴦��һ�������񣬵�k+1���ڵ㴦��һ�������񣬴���ʱ���Ƕ������ֵ��u��v�任�������ȡ������Сʱ�䡣
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