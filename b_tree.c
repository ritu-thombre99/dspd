#include<stdio.h>
#include<stdlib.h>
typedef struct data_node
{
	int data;
	struct data_node* next;
	struct data_node* branch0;
	struct data_node* branch1;
}Data_type;
Data_type* Make_Node(int data)
{
	Data_type* node = (Data_type*) malloc (sizeof(Data_type));
	node->data = data;
	node->next = NULL;
	node->branch0 = NULL;
	node->branch1 = NULL;
	return node;
}
int length(Data_type *lptr)
{
	Data_type *ptr = lptr;
	int length = 0;
	while(ptr != NULL)
	{
		length ++;
		ptr = ptr -> next;
	}
	return length;
}
void printList(Data_type *lptr)
{
	while(lptr != NULL)
	{
		printf("%d\t",lptr -> data);
		lptr = lptr -> next;
	}
	printf("\n");
}
void printTree(Data_type *b_tree)
{
	if(b_tree != NULL)
	{
		printList(b_tree);
		printTree(b_tree -> branch0);
		printTree(b_tree -> branch1);
		if(b_tree->next!=NULL)
		{
			printList(b_tree->next->branch1);
		}
	}
}
Data_type* sort(Data_type *lptr)
{
	Data_type *ptr1 = lptr,*ptr2 = NULL;
	int temp;
	while(ptr1 != NULL)
	{
		ptr2 = ptr1->next;
		while(ptr2 != NULL)
		{
			if(ptr1 -> data > ptr2 -> data)
			{
				temp = ptr2 -> data;
				ptr2 -> data = ptr1-> data;
				ptr1 ->data = temp;
			}
			ptr2 = ptr2 -> next;
		}
		ptr1 = ptr1 -> next;
	}
	return lptr;
}
Data_type* Insert_Node(Data_type* p ,Data_type* Data,int x)
{
	Data_type* q = p;
	if(x==0)
	{
		while(q->next!=NULL)
		{
			q = q->next;
		}
		q->next = Data;
		p = sort(p);
	}
	if(x==1)
	{
		printf("before first if in x==1\n");
		if(q->data > Data->data)
		{
			printf("before second if in x==1\n");
			if(q->branch0 == NULL)
			{
				printf("after second if in x==1\n");
				q->branch0 = Data;
			}
			else
			{
				q = Insert_Node(q->branch0,Data,1);
			}
		}
		else
		{
		    if(q->branch1 == NULL)
		    {
		        q->branch1 = Data;
		    }
		    else
		    {
		        q = Insert_Node(q->branch1,Data,1);
		    }
		}
		p = sort(p);
	}
	return p;
}
Data_type* Insert(Data_type* root,Data_type* Data)
{
	Data_type* p,*temp,*prev,*next,*use;
	p = root;
	if(p == NULL)
	{
		root = Data;
	}
	else
	{
		if((p->data) > (Data->data))
		{
			if(p->branch0 == NULL)
			{
				p= Insert_Node(p,Data,0);
			}
			else
			{
				p = Insert(p->branch0,Data);
				if(p->branch0!=NULL && p->branch1!=NULL)
				{
					if(root==NULL)
					{
						root = p;
					}
					else
					{
						if(root->data > p->data)
						{
							p->next = root;
							root->branch0 = p->branch1;
							root = p;
						}
						else
						{
							root->next = p;
							root->branch1 = p->branch0;
						}
					}
				}
			}
			if(length(p)==3)
			{
				int i = 3/2;
				temp = p;
				while(i!=0)
				{
					temp = temp->next;
					i--;
				}
				prev = p;
				(prev->next) = NULL;
				next = temp->next;
				printf("Before 1st insert_node\n");
				temp->next = NULL;
				p = Insert_Node(temp,p,1);
				printf("Before 2st insert_node\n");
				p = Insert_Node(temp,next,1);
				root = p;
			}
		}
		else
		{
			if(p->branch1 == NULL)
			{
				p= Insert_Node(p,Data,0);
			}
			else
			{
				p = Insert(p->branch1,Data);;
				if(p->branch0!=NULL && p->branch1!=NULL)
				{
					if(root==NULL)
					{
						root = p;
					}
					else
					{
						if(root->data > p->data)
						{
							p->next = root;
							root->branch0 = p->branch1;
							root = p;
						}
						else
						{
							root->next = p;
							root->branch1 = p->branch0;
						}
					}
				}
			}
			if(length(p)==3)
			{
				int i = 3/2;
				temp = p;
				while(i!=0)
				{
					temp = temp->next;
					i--;
				}
				prev = p;
				(prev->next) = NULL;
				next = temp->next;
				temp->next = NULL;
				p = Insert_Node(temp,p,1);
				p = Insert_Node(temp,next,1);
				root = p;
			}
		}
	}
	//root = p;
	return root;
}
int main()
{
	int n;
	Data_type* root = NULL;
	printf("Enter Data");
	scanf("%d",&n);
	Data_type* node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	printf("Enter Data");
	scanf("%d",&n);
	node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	printf("Enter Data");
	scanf("%d",&n);
	node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	printf("Enter Data");
	scanf("%d",&n);
	node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	printf("Enter Data");
	scanf("%d",&n);
	node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	printf("Enter Data");
	scanf("%d",&n);
	node = Make_Node(n);
	root = Insert(root,node);
	printTree(root);
	return 0;
}
