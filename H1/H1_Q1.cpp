#include <iostream>
using namespace std;
// 定义一个结构体，代表一个参与配对的个体
struct individual
{
	string name;	  // 姓名
	bool isFree = 1;  // 是否已经有婚约
	int failed = 0;	  // 配对失败次数
	int lovenum = -1; // 配对成功的对象在对方数组中的序号
	string lovename;  // 配对成功的对象的姓名
	string *prefer;	  // 按偏好顺序存放待与之配对的人的姓名
};
int marriednum = 0;					  // 已经配对成功的个体数量
void Initial(individual *&ind, int n) // 结构体数组的初始化
{
	string *input = new string[n]; // 获取输入的字符串
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	for (int i = 0; i < n; i++)
	{
		ind[i].isFree = 1; // 初始时每个个体都是free
		ind[i].prefer = new string[n];
	}
	// 接下来要对输入的信息进行处理
	// 由输入样例可知，input数组的每行包括个体自身的姓名、偏好的对象及顺序，按照形如"A:X>Y"的格式，因此需要对输入字符串进行处理
	for (int i = 0; i < n; i++) // 对input每行进行遍历，得到每个个体的信息
	{
		int j = 0;
		// 输入的字符串，':'前的是个体自身的姓名，不一定是一位字符
		for (j = 0; j < input[i].length(); j++) // 对一行的字符串遍历，遇到的字符加入到个体的姓名信息中
		{
			if (input[i][j] == ':') // 当遇到':'时停止
				break;
			ind[i].name = ind[i].name + input[i][j];
		}
		int index = 0;
		// 然后继续读个体的偏好，将其喜欢的对象的姓名按偏好顺序存在prefer数组中
		for (int m = j + 1; m < input[i].length(); m++)
		{
			if (input[i][m] == '>') // 遇到'>'时，一个喜欢的对象结束
			{
				index++;
				continue;
			}
			ind[i].prefer[index] = ind[i].prefer[index] + input[i][m];
		}
	}
}
int main()
{
	int n;
	cin >> n;
	struct individual *man = new individual[n];	  // 结构体数组，每个元素表示一个男性个体
	struct individual *woman = new individual[n]; // 结构体数组，每个元素表示一个女性个体
	Initial(man, n);							  // 所有男性初始化
	Initial(woman, n);							  // 所有女性初始化
	while (marriednum != n)						  // 直到所有人都完成配对，配对结束
	{
		for (int i = 0; i < n; i++) // 第i个男性
		{
			if (!man[i].isFree) // 如果男性已经有婚约，跳过
				continue;
			for (int k = man[i].failed; k < n; k++)
			// k代表男性正在追求的女性在他偏好中的序号，如果是第1次参与匹配，肯定从他最喜欢的人（第0个）开始，如果他失败过i次，就从他排序中下标为i的喜爱的人开始
			{
				int j = 0;
				for (j; j < n; j++) // 以j为索引遍历女性，用名字找到男性第k个喜爱的女性在woman结构体数组中的序号
				{
					if (woman[j].name == man[i].prefer[k])
						break;
				}
				if (woman[j].isFree) // 女性free则匹配成功
				{
					marriednum++; // 匹配成功数加一
					// 更新二人状态，修改二人配对成功的对象的姓名及序号
					man[i].lovenum = j;
					man[i].lovename = woman[j].name;
					woman[j].lovenum = i;
					man[i].isFree = 0;
					woman[j].isFree = 0;
					break;
				}
				else // 女性已经有匹配，就要进行竞争
				{
					int comnum = -1; // 竞争者在女性偏好中的序号
					int nownum = -1; // 自己在女性偏好中的序号
					for (int s = 0; s < n; s++)
					{
						if (woman[j].prefer[s] == man[woman[j].lovenum].name) // 进行名称匹配，找到竞争者在女性偏好中的序号
						{
							comnum = s;
							if (nownum != -1)
								break;
						}
						if (woman[j].prefer[s] == man[i].name) // 进行名称匹配，找到自己在女性偏好中的序号
						{
							nownum = s;
							if (comnum != -1)
								break;
						}
					}
					if (nownum < comnum) // 如果自己排序小，打败竞争者
					{
						// 释放竞争者，修改竞争者的相关信息，竞争者失败次数加一
						man[woman[j].lovenum].isFree = 1;
						man[woman[j].lovenum].lovenum = -1;
						man[woman[j].lovenum].failed++;
						// 自己与该女性成功匹配，修改信息
						man[i].isFree = 0;
						man[i].lovenum = j;
						man[i].lovename = woman[j].name;
						woman[j].lovenum = i;
						break;
					}
					else
					{
						man[i].failed++; // 如果自己排序靠后，自己失败，自己的失败次数加一
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << '(' << man[i].name << ',' << man[i].lovename << ')' << endl;
	}
}