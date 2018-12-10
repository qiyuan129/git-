#include <iostream>
#define directed true
#define undirected false
using namespace std;
bool found = false;
typedef struct node * link;
struct node {
	int v;    //�ߵ���һ������
	int weight;
	link next;
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
				link p = adj[i];
				while (p->next != NULL) p = p->next;   //���ҵ�ָ�����һ���ڵ��ָ��

				link p1 = new node();
				p1->v = j;
				p1->weight = w;
				p1->next = NULL;

				p->next = p1;
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
					link p = adj[j];
					while (p->next != NULL) p = p->next;   //���ҵ�ָ�����һ���ڵ��ָ��

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

	void find_route() {       //֮���Կ��Բ��ñ�����飬��������Ϊ��Ҫ�������⣬�����й��ܶٻ�·����β������û�����ţ�
		unsigned int *route = new unsigned int[n + 1]();

		for (int i = 1; i <= n && found==false; i++) {     //û�ҵ��Ŷ�ÿ���������ң��ҵ���ֱ���˳�ѭ��
			dfs(i,route);
		}
		if (found == true) {
			for (int i = 1; i <= n; i++)
				cout << route[i] << ' ';
		}
		else {
			cout << "��ͼ�����ڹ��ܶ�ͨ·" << endl;
		}
	}
	void dfs(int v, unsigned int* route, int depth = 1) {
		if (found == false)
			route[depth] = v;

		link p = adj[v];
		while (p) {
			if (found)              //����Ѿ��ҵ�һ�����ܶ�ͨ·���ڻ��ݹ����оͲ����ٿ������ڽӵ��ˡ�
				break;
			dfs(p->v, route,depth+1);
			p = p->next;
		}
		if (depth == n)
			found = true;                //�ҵ�����������·��������Ϊtrue�����������ڻ��ݵĹ�������ô����route�����鲻���ٱ��ı�
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

