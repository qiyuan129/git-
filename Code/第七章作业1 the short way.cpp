#include <iostream>
#include <vector>
#include <set>
#define directed true
#define undirected false
using namespace std;
typedef struct node * link;
struct node {
	int v;    //边的另一个顶点
	int weight;
	link next;
};
typedef struct node2 *link2;
struct node2 {
	int v;
	long long dist;
	node2(int v1,long long dist1):v(v1),dist(dist1){}
	friend bool operator<(const node2& n1, const node2& n2) {
		return n1.dist < n2.dist;
	}
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
				link tmp = adj[i];      //存一下头节点原来指向的节点

				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = tmp;

				adj[i]=p1;
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
					link tmp = adj[j];      //存一下头节点原来指向的节点

					link p1 = new node();
					p1->v = i;
					p1->weight = w;
					p1->next = tmp;

					adj[j] = p1;
				}
			}
			e++;


		}
	}

	long long Dijkstra(int s=1) {
		long long* dist = new long long[n + 1]();
		vector<int> S;            //已确定的数
		set<int> Q;               //未确定的数
		set<node2> wait;          //待比较的数
		int t = 1;

		S.push_back(0);  //为了让有效元素在vector中的下标从1开始
		S.push_back(1);
		for (int i = 0; i <= n; i++)
			dist[i] = 2000000000000000;
		dist[1] = 0;

		for (int i = 2; i <= n; i++)       //初始化Q（未确定元素的集合）
			Q.insert(i);
		while (!Q.empty()) {
			int least = S[t];
			link p = adj[least];
			while (p) {                 //更新有邻接的点的dist
				long long tmp1 = dist[least] + p->weight;
				int u = p->v;                 //u是当前在处理的上一个最小点的邻接点

				if (tmp1 < dist[u]) {            //如果有更新，把这个点加入之后的待比较的集合中
					dist[u] = tmp1;

					node2 uu(u, dist[u]);
					set<node2>::iterator it = wait.find(uu);
					if (it == wait.end())
						wait.insert(uu);
				}
				p = p->next;
			}

			set<node2>::iterator it = wait.begin();        //因为set自带排序功能，所以第一个就是dist最小的
			int n_least = (*it).v;
			Q.erase(n_least);
			wait.erase(it);
			S.push_back(n_least);

			t++;
		}
		return dist[n];
	}
};
int main() {
	int n, m;

	cin >> n >> m;

	graph g1(n,undirected);
	for (int i = 0; i < m; i++) {
		int a, b, c;

		cin >> a >> b >> c;
		g1.add(a, b, c);
	}
	cout << g1.Dijkstra() << endl;

}


//6 9
//1 2 1
//1 3 4
//2 3 2
//2 4 7
//2 5 5
//3 5 1
//4 5 3
//4 6 2
//5 6 6
9
//我还改了呢
//你看我又加了一行