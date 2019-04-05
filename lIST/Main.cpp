/*
1. 求单链表中结点的个数
2. 将单链表反转
3. 查找单链表中的倒数第K个结点（k > 0）
4. 查找单链表的中间节点
5. 从尾到头打印单链表
6. 已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序
7. 判断一个单链表中是否有环
8. 判断两个单链表是否相交
9. 求两个单链表相交的第一个节点
10. 已知一个单链表中存在环，求进入环中的第一个节点
11. 给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted
*/

#include <iostream>
#include <stack>
using namespace std;

typedef  struct List {
	int val;
	List* next;
}*myList;

//创建链表
myList CreatList(unsigned int length)
{
	if (length == 0)
		return NULL;
	myList head, tail, temp;
	head = new List();
	head->next = NULL;
	tail = head;
	//在32位系统中size_t是4字节的，而在64位系统中，size_t是8字节的，这样利用该类型可以增强程序的可移植性。
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

//销毁链表
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

//销毁带有环的
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

//遍历链表
void PrintList(myList head)
{
	while (head){
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

//求单链表个数
int Length(myList head)
{
	int length = 0;
	while (head) {
		length++;
		head = head++;
	}
	return length;
}

//反转链表
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

//查找单链表中的倒数第K个结点
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

//查找单链表的中间结点
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

//从尾到头打印单链表（递归）
void PrintListFromTailToHead(myList head)
{
	if (head == NULL)
		return;
	PrintListFromTailToHead(head->next);
	cout << head->val << endl;
}

//从尾到头打印单链表（通过栈）
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

//已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序（非递归）
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

//判断一个单链表中是否有环
/*
使用两个指针，一个指针每次向后移两位，一个每次移以为，若两指针相等表示链表有环
时间复杂度为 O(List.length)
*/
bool IsCircularList(myList head)
{
	if (head == NULL && head->next == NULL)
		return false;
	myList temp1 = head, temp2 = head;
	//temp1和temp2都不为空
	while (temp1 && temp2 && temp2->next)
	{
		temp1 = temp1->next;
		temp2 = temp2->next->next;
		if (temp1 == temp2)
			return true;
	}
	return false;
}

//判断两个单链表是否相交
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
	//若相交则两个链表的最后一个节点必然相等
	if (head1 == head2)
		return true;
	return false;
}

//求两个单链表相交的第一个节点
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
	//不相交
	if (temp1 != temp2)
		return NULL;
	//保证head1是两者中较长的链表
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

//已知一个单链表中存在环，求环的入口
myList CircularListEntrance(myList head)
{
	if (head == NULL)
		return NULL;
	myList fast = head, slow = head;
	while (slow && fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		//第一次相交
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

//给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted
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
	//cout << "请输入节点个数：";
	//cin >> c;
	//myList head = CreatList(c);
	//PrintList(head);
	//ReverseList(head);
	//PrintList(head);
	//int k;
	//cout << "打印倒数第k个节点的值，k = ";
	//cin >> k;
	//myList kNode = FindCountBackwardsK(head, k);
	//	if(kNode != NULL)
	//cout << "倒数第" << k << "个节点为：" << kNode->val << endl;
	//myList mNode = FindMiddleNode(head);
	//cout << "中间节点为：" << mNode->val << endl;
	//PrintListFromTailToHead(head);
	//PrintListFromTailToHeadByStack(head);

	//ReverseList(head);
	//cout << "输入三个递增的整型值以创建另一个链表" << endl;
	//myList list = CreatList(3);
	//list = MergeOrderedLists(head, list);
	//PrintList(list);

	//创建一个环形列表
	myList circularList = new List();
	circularList->val = 1;
	circularList->next = new List();
	circularList->next->val = 2;
	circularList->next->next = new List();
	circularList->next->next->val = 3;
	circularList->next->next->next = circularList->next;

	//cout << "list是否是环形链表：" << IsCircularList(list) << endl;
	//cout << "circularList是否是环形链表：" << IsCircularList(circularList) << endl;
	//
	//myList list_ = new List();
	//list_->next = list->next->next;
	//cout << "list与list_是否相交：" << IsIntersect(list, list_) << endl;
	//kNode = FirstIntersectNode(list, list_);
	//if(kNode != NULL)
	//	cout << "list与list_相交的第一个节点：" << kNode << endl;

	myList in = CircularListEntrance(circularList);
	cout << "环入口为：" << in->val << endl;

	//DestroyList(list);
	DestroyCircularListList(circularList);
	system("pause");
	return 0;
}