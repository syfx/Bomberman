/*
1. �������н��ĸ���
2. ��������ת
3. ���ҵ������еĵ�����K����㣨k > 0��
4. ���ҵ�������м�ڵ�
5. ��β��ͷ��ӡ������
6. ��֪����������pHead1 ��pHead2 �������򣬰����Ǻϲ���һ��������Ȼ����
7. �ж�һ�����������Ƿ��л�
8. �ж������������Ƿ��ཻ
9. �������������ཻ�ĵ�һ���ڵ�
10. ��֪һ���������д��ڻ�������뻷�еĵ�һ���ڵ�
11. ����һ������ͷָ��pHead��һ�ڵ�ָ��pToBeDeleted��O(1)ʱ�临�Ӷ�ɾ���ڵ�pToBeDeleted
*/

#include <iostream>
#include <stack>
using namespace std;

typedef  struct List {
	int val;
	List* next;
}*myList;

//��������
myList CreatList(unsigned int length)
{
	if (length == 0)
		return NULL;
	myList head, tail, temp;
	head = new List();
	head->next = NULL;
	tail = head;
	//��32λϵͳ��size_t��4�ֽڵģ�����64λϵͳ�У�size_t��8�ֽڵģ��������ø����Ϳ�����ǿ����Ŀ���ֲ�ԡ�
	for (size_t i = 0; i < length; ++i){
		temp = new List();
		cin >> temp->val;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	temp = head;
	head = head->next;
	delete temp;
	return head;
}

//��������
void DestroyList(myList head)
{
	if (head == NULL)
		return;
	while (head) {
		myList temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
	}
}

//���ٴ��л���
void DestroyCircularListList(myList head)
{
	if (head == NULL)
		return;
	myList temp = head->next;
	head->next = NULL;
	while (temp) {
		temp = temp->next;
		delete head;
		head = NULL;
	}
}

//��������
void PrintList(myList head)
{
	while (head){
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

//���������
int Length(myList head)
{
	int length = 0;
	while (head) {
		length++;
		head = head++;
	}
	return length;
}

//��ת����
void ReverseList(myList &head)
{
	if (head == NULL || head->next == NULL)
		return;
	myList temp, oldHead = head;
	while (oldHead->next) {
		temp = oldHead->next;
		oldHead->next = temp->next;
		temp->next = head;
		head = temp;
	}
}

//���ҵ������еĵ�����K�����
myList FindCountBackwardsK(myList head, unsigned int k) 
{
	if (head == NULL)
		return NULL;
	myList  left = head, right = head;
	for (size_t i = 1; i < k; ++i){
		right = right->next;
		if (!right)
			return NULL;
	}
	while (right && right->next){
		right = right->next;
		left = left->next;
	}
	return left;
}

//���ҵ�������м���
myList FindMiddleNode(myList head)
{
	myList left = head, right = head;
	if (head == NULL)
		return NULL;
	while (right->next){
		right = right->next->next;
		if (right == NULL) 
			break;
		left = left->next;
	}
	return left;
}

//��β��ͷ��ӡ�������ݹ飩
void PrintListFromTailToHead(myList head)
{
	if (head == NULL)
		return;
	PrintListFromTailToHead(head->next);
	cout << head->val << endl;
}

//��β��ͷ��ӡ������ͨ��ջ��
void PrintListFromTailToHeadByStack(myList head)
{
	stack<myList> sta;
	while (head){
		sta.push(head);
		head = head->next;
	}
	while (!sta.empty()){
		cout << sta.top()->val << " ";
		sta.pop();
	}
	cout << endl;
}

//��֪����������pHead1 ��pHead2 �������򣬰����Ǻϲ���һ��������Ȼ���򣨷ǵݹ飩
myList MergeOrderedLists(myList head1, myList head2)
{
	if (head1 == NULL)
		return head2;
	if (head2 == NULL)
		return head1;
	myList newHead =NULL;
	if (head1->val >= head2->val) {
		newHead = head2;
		head2 = head2->next;
	}
	else {
		newHead = head1;
		head1 = head1->next;
	}
	newHead->next = NULL;
	myList temp = newHead;
	while ( head1 && head2){
		if (head1->val < head2->val) {
			temp->next = head1;
			head1 = head1->next;
		}
		else {
			temp->next = head2;
			head2 = head2->next;
		}
		temp = temp->next;
		temp->next = NULL;
	}
	if (head1 == NULL) {
		temp->next = head2;
	}
	else {
		temp->next = head1;
	}
	return newHead;
}

//�ж�һ�����������Ƿ��л�
/*
ʹ������ָ�룬һ��ָ��ÿ���������λ��һ��ÿ������Ϊ������ָ����ȱ�ʾ�����л�
ʱ�临�Ӷ�Ϊ O(List.length)
*/
bool IsCircularList(myList head)
{
	if (head == NULL && head->next == NULL)
		return false;
	myList temp1 = head, temp2 = head;
	//temp1��temp2����Ϊ��
	while (temp1 && temp2 && temp2->next)
	{
		temp1 = temp1->next;
		temp2 = temp2->next->next;
		if (temp1 == temp2)
			return true;
	}
	return false;
}

//�ж������������Ƿ��ཻ
bool IsIntersect(myList head1, myList head2)
{
	if (head1 == NULL || head2 == NULL)
		return false;
	while (head1->next) {
		head1 = head1->next;
	}
	while (head2->next) {
		head2 = head2->next;
	}
	//���ཻ��������������һ���ڵ��Ȼ���
	if (head1 == head2)
		return true;
	return false;
}

//�������������ཻ�ĵ�һ���ڵ�
myList FirstIntersectNode(myList head1, myList head2)
{
	if (head1 == NULL || head2 == NULL)
		return NULL;
	int len1 = 1, len2 = 1;
	myList temp1 = head1, temp2 = head2;
	while (temp1->next) {
		len1++;
		temp1 = temp1->next;
	}
	while (temp2->next) {
		len2++;
		temp2 = temp2->next;
	}
	//���ཻ
	if (temp1 != temp2)
		return NULL;
	//��֤head1�������нϳ�������
	if (len1 < len2) {
		temp1 = head1;
		head1 = head2;
		head2 = temp1;
	}
	for (int i = 0; i < abs(len1 - len2); ++i) {
		head1 = head1->next;
	}
	while (head2) {
		if (head1 == head2)
			return head1;
		head1 = head1->next;
		head2 = head2->next;
	}
	return NULL;
}

//��֪һ���������д��ڻ����󻷵����
myList CircularListEntrance(myList head)
{
	if (head == NULL)
		return NULL;
	myList fast = head, slow = head;
	while (slow && fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		//��һ���ཻ
		if (slow == fast) {
			fast = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}
	return NULL;
}

//����һ������ͷָ��pHead��һ�ڵ�ָ��pToBeDeleted��O(1)ʱ�临�Ӷ�ɾ���ڵ�pToBeDeleted
void DeleteNode(myList head, myList pToBeDeleted)
{
	if (head == NULL)
		return;
	if (pToBeDeleted->next != NULL) {
		myList temp = pToBeDeleted->next;
		pToBeDeleted->val = temp->val;
		pToBeDeleted->next = temp->next;
		delete temp;
		temp = NULL;
	}
	else {
		if (head == pToBeDeleted) {
			delete pToBeDeleted;
			head = NULL;
			pToBeDeleted = NULL;
		}
		while (head->next != pToBeDeleted) {
			head = head->next;
		}
		head->next = NULL;
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}

int main()
{
	//int c;
	//cout << "������ڵ������";
	//cin >> c;
	//myList head = CreatList(c);
	//PrintList(head);
	//ReverseList(head);
	//PrintList(head);
	//int k;
	//cout << "��ӡ������k���ڵ��ֵ��k = ";
	//cin >> k;
	//myList kNode = FindCountBackwardsK(head, k);
	//	if(kNode != NULL)
	//cout << "������" << k << "���ڵ�Ϊ��" << kNode->val << endl;
	//myList mNode = FindMiddleNode(head);
	//cout << "�м�ڵ�Ϊ��" << mNode->val << endl;
	//PrintListFromTailToHead(head);
	//PrintListFromTailToHeadByStack(head);

	//ReverseList(head);
	//cout << "������������������ֵ�Դ�����һ������" << endl;
	//myList list = CreatList(3);
	//list = MergeOrderedLists(head, list);
	//PrintList(list);

	//����һ�������б�
	myList circularList = new List();
	circularList->val = 1;
	circularList->next = new List();
	circularList->next->val = 2;
	circularList->next->next = new List();
	circularList->next->next->val = 3;
	circularList->next->next->next = circularList->next;

	//cout << "list�Ƿ��ǻ�������" << IsCircularList(list) << endl;
	//cout << "circularList�Ƿ��ǻ�������" << IsCircularList(circularList) << endl;
	//
	//myList list_ = new List();
	//list_->next = list->next->next;
	//cout << "list��list_�Ƿ��ཻ��" << IsIntersect(list, list_) << endl;
	//kNode = FirstIntersectNode(list, list_);
	//if(kNode != NULL)
	//	cout << "list��list_�ཻ�ĵ�һ���ڵ㣺" << kNode << endl;

	myList in = CircularListEntrance(circularList);
	cout << "�����Ϊ��" << in->val << endl;

	//DestroyList(list);
	DestroyCircularListList(circularList);
	system("pause");
	return 0;
}