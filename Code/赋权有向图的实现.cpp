#include <iostream>
#define directed true
#define undirected false
using namespace std;
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
	graph(int number,bool direction1=directed):n(number),e(0),adj(new link[n+1]()),direction(direction1){
		for (int i = 0; i <= n; i++)    adj[i] = NULL;
	}

	int edges() {
		return e;
	}
	int vertices() {
		return n;
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

	void add(int i, int j,int w=1) {    //在图中添加从i到j，权为w的边（输入合法的话）
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

	//void Delete(int i, int j) {       //在当前图中删除从idao
	//	if (i<1 || i>n || j<1 || j>n || exist(i,j))
	//		cout << "ERROR";
	//	else {

	//	}
	//}
	void gprint() {
		cout << "当前该图共有" << e << "条边" << endl;
		cout << "下面是该图的邻接表" << endl;
		for (int i = 1; i <= n; i++) {
			cout  << i << ":  ";
			if (adj[i]) {
				link p = adj[i];
				while (p) {              //p非NULL才输出
					cout << p->v << "->";
					p = p->next;
				}
				cout << "NULL"<<endl;
			}
			else
				cout << "NULL" << endl;
		}
	}

	void bianli(int begin) {
		bool *sign = new bool[n + 1]();
		int v = 1;

		cout << "该图从点" << begin << " 深度遍历的顺序为：" << endl;
		while(v<=n) {
			if (sign[v] == true) {
				v++;
			}
			else
				dfs(v,sign);
		}
		delete[]sign;
	}
	void dfs(int v,bool *sign) {
		cout << v <<"-> ";
		sign[v] = true;

		link p = adj[v];
		while (p) {
			if (sign[p->v] == true) {
				p = p->next;
			}
			else {
				dfs(p->v, sign);
				p = p->next;
			}
		}
	}
};
int main() {
	graph g1(8,undirected);

	g1.add(1,2 );
	g1.add(1,3 );
	g1.add(2,4 );
	g1.add(2,5 );
	g1.add(3,6 );
	g1.add(3,7 );
	g1.add(6,7 );
	g1.add(4,8 );
	g1.add(5,8 );

	g1.bianli(1);
	system("pause");

}