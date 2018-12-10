#include <iostream>
#define directed true
#define undirected false
using namespace std;
bool found = false;
typedef struct node * link;
struct node {
	int v;    //边的另一个顶点
	int weight;
	link next;
};
class graph {
private:
	int n;      //图的顶点数
	int e;      //图的边数
	link* adj;       //邻接表
	bool direction;        //该布尔值标记该图为有向图还是无向图，默认为有向图
public:
	graph(int number, bool direction1 = directed) :n(number), e(0), adj(new link[n + 1]()), direction(direction1) {
		for (int i = 0; i <= n; i++)    adj[i] = NULL;
	}

	bool exist(int i, int j) {          //判断在当前图中存不存在从i到j的边 
		if (i<1 || i>n || j<1 || j>n) {
			return false;
		}
		else {
			link p1 = adj[i];
			while (!p1) {
				if (p1->v == j)
					return true;
				p1 = p1->next;
			}
			return false;
		}
	}

	void add(int i, int j, int w = 1) {    //在图中添加从i到j，权为w的边（输入合法的话）
		if (i<1 || i>n || j<1 || j>n)
			cout << "ERROR INPUT" << endl;
		else {
			link head = adj[i];
			if (head == NULL) {              //邻接表的头指针为空时要单独处理（因为这时不能用head->next）
				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = NULL;

				adj[i] = p1;
			}
			else {
				link p = adj[i];
				while (p->next != NULL) p = p->next;   //先找到指向最后一个节点的指针

				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = NULL;

				p->next = p1;
			}

			if (direction == undirected) {             //如果建立的是无向图，则在添加边时还要添加一条相反方向的有向边
				head = adj[j];
				if (head == NULL) {              //邻接表的头指针为空时要单独处理（因为这时不能用head->next）
					link p1 = new node();
					p1->v = i;
					p1->weight = w;
					p1->next = NULL;

					adj[j] = p1;
				}
				else {
					link p = adj[j];
					while (p->next != NULL) p = p->next;   //先找到指向最后一个节点的指针

					link p1 = new node();
					p1->v = i;
					p1->weight = w;
					p1->next = NULL;

					p->next = p1;
				}
			}
			e++;


		}
	}

	void find_route() {       //之所以可以不用标记数组，好像是因为想要满足题意，不能有哈密顿回路（首尾相连处没法安排）
		unsigned int *route = new unsigned int[n + 1]();

		for (int i = 1; i <= n && found==false; i++) {     //没找到才对每个点依次找，找到了直接退出循环
			dfs(i,route);
		}
		if (found == true) {
			for (int i = 1; i <= n; i++)
				cout << route[i] << ' ';
		}
		else {
			cout << "该图不存在哈密顿通路" << endl;
		}
	}
	void dfs(int v, unsigned int* route, int depth = 1) {
		if (found == false)
			route[depth] = v;

		link p = adj[v];
		while (p) {
			if (found)              //如果已经找到一条哈密顿通路，在回溯过程中就不用再看其他邻接点了。
				break;
			dfs(p->v, route,depth+1);
			p = p->next;
		}
		if (depth == n)
			found = true;                //找到符合条件的路径后令标记为true，这样不管在回溯的过程中怎么样，route的数组不会再被改变
	}
};
int main() {
	int n;

	cin >> n;
	graph g1(n);
	for (int i = 1; i <= n; i++) {
		int tmp;
		cin >> tmp;
		for (int j = 0; j < tmp; j++) {
			int people;
			cin >> people;
			g1.add(i, people);
		}
	}

	g1.find_route();
}

