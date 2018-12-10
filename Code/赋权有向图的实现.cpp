#include <iostream>
#define directed true
#define undirected false
using namespace std;
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
	graph(int number,bool direction1=directed):n(number),e(0),adj(new link[n+1]()),direction(direction1){
		for (int i = 0; i <= n; i++)    adj[i] = NULL;
	}

	int edges() {
		return e;
	}
	int vertices() {
		return n;
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

	void add(int i, int j,int w=1) {    //��ͼ����Ӵ�i��j��ȨΪw�ıߣ�����Ϸ��Ļ���
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

	//void Delete(int i, int j) {       //�ڵ�ǰͼ��ɾ����idao
	//	if (i<1 || i>n || j<1 || j>n || exist(i,j))
	//		cout << "ERROR";
	//	else {

	//	}
	//}
	void gprint() {
		cout << "��ǰ��ͼ����" << e << "����" << endl;
		cout << "�����Ǹ�ͼ���ڽӱ�" << endl;
		for (int i = 1; i <= n; i++) {
			cout  << i << ":  ";
			if (adj[i]) {
				link p = adj[i];
				while (p) {              //p��NULL�����
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

		cout << "��ͼ�ӵ�" << begin << " ��ȱ�����˳��Ϊ��" << endl;
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