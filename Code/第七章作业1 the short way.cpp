#include <iostream>
#include <vector>
#include <set>
#define directed true
#define undirected false
using namespace std;
typedef struct node * link;
struct node {
	int v;    //�ߵ���һ������
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
	int n;      //ͼ�Ķ�����
	int e;      //ͼ�ı���
	link* adj;       //�ڽӱ�
	bool direction;        //�ò���ֵ��Ǹ�ͼΪ����ͼ��������ͼ��Ĭ��Ϊ����ͼ
public:
	graph(int number, bool direction1 = directed) :n(number), e(0), adj(new link[n + 1]()), direction(direction1) {
		for (int i = 0; i <= n; i++)    adj[i] = NULL;
	}

	bool exist(int i, int j) {          //�ж��ڵ�ǰͼ�д治���ڴ�i��j�ı� 
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

	void add(int i, int j, int w = 1) {    //��ͼ����Ӵ�i��j��ȨΪw�ıߣ�����Ϸ��Ļ���
		if (i<1 || i>n || j<1 || j>n)
			cout << "ERROR INPUT" << endl;
		else {
			link head = adj[i];
			if (head == NULL) {              //�ڽӱ��ͷָ��Ϊ��ʱҪ����������Ϊ��ʱ������head->next��
				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = NULL;

				adj[i] = p1;
			}
			else {
				link tmp = adj[i];      //��һ��ͷ�ڵ�ԭ��ָ��Ľڵ�

				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = tmp;

				adj[i]=p1;
			}

			if (direction == undirected) {             //���������������ͼ��������ӱ�ʱ��Ҫ���һ���෴����������
				head = adj[j];
				if (head == NULL) {              //�ڽӱ��ͷָ��Ϊ��ʱҪ����������Ϊ��ʱ������head->next��
					link p1 = new node();
					p1->v = i;
					p1->weight = w;
					p1->next = NULL;

					adj[j] = p1;
				}
				else {
					link tmp = adj[j];      //��һ��ͷ�ڵ�ԭ��ָ��Ľڵ�

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
		vector<int> S;            //��ȷ������
		set<int> Q;               //δȷ������
		set<node2> wait;          //���Ƚϵ���
		int t = 1;

		S.push_back(0);  //Ϊ������ЧԪ����vector�е��±��1��ʼ
		S.push_back(1);
		for (int i = 0; i <= n; i++)
			dist[i] = 2000000000000000;
		dist[1] = 0;

		for (int i = 2; i <= n; i++)       //��ʼ��Q��δȷ��Ԫ�صļ��ϣ�
			Q.insert(i);
		while (!Q.empty()) {
			int least = S[t];
			link p = adj[least];
			while (p) {                 //�������ڽӵĵ��dist
				long long tmp1 = dist[least] + p->weight;
				int u = p->v;                 //u�ǵ�ǰ�ڴ������һ����С����ڽӵ�

				if (tmp1 < dist[u]) {            //����и��£�����������֮��Ĵ��Ƚϵļ�����
					dist[u] = tmp1;

					node2 uu(u, dist[u]);
					set<node2>::iterator it = wait.find(uu);
					if (it == wait.end())
						wait.insert(uu);
				}
				p = p->next;
			}

			set<node2>::iterator it = wait.begin();        //��Ϊset�Դ������ܣ����Ե�һ������dist��С��
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
//�һ�������
//�㿴���ּ���һ��