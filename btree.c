#include<stdio.h>
#include<stdlib.h>
int m = 5;
typedef struct Node_tag
{
	int data;
	struct Node_tag *down_left;
	struct Node_tag *down_right;
	struct Node_tag *next;
} b_Node;
b_Node* MakeNode(int data)
{
	b_Node *node;
	node = (b_Node*)malloc(sizeof(b_Node));
	node -> data = data;
	node -> down_left = node  -> down_right = node -> next = NULL;
	return node;
}
int lengthOf(b_Node *lptr)
{
	b_Node *ptr = lptr;
	int length = 0;
	while(ptr != NULL)
	{
		length ++;
		ptr = ptr -> next;
	}
	return length;
}
void printList(b_Node *lptr)
{
	while(lptr != NULL)
	{
		printf("%d\t",lptr -> data);
		lptr = lptr -> next;
	}
	printf("\n");
}
void printTree(b_Node *b_tree)
{
	if(b_tree != NULL)
	{
		printList(b_tree);
		printTree(b_tree -> down_left);
		printTree(b_tree -> down_right);
	}
}
b_Node* sort(b_Node *lptr)
{
	b_Node *ptr1 = lptr,*ptr2 = NULL;
	int temp;
	while(ptr1 != NULL)
	{
		ptr2 = lptr;
		while(ptr2 -> next != NULL)
		{
			if(ptr2 -> data > ptr2 -> next -> data)
			{
				temp = ptr2 -> data;
				ptr2 -> data = ptr2 -> next -> data;
				ptr2 -> next -> data = temp;
			}
			ptr2 = ptr2 -> next;
		}
		ptr1 = ptr1 -> next;
	}
	return lptr;
}
b_Node* Insert(b_Node *b_tree,int data)
{
	int found = 0;
	b_Node *temp_b = b_tree,*prev,*lptr;
	//lptr = b_tree;
	
	if(temp_b -> down_right == NULL && temp_b -> down_left == NULL)
	{
		if(b_tree -> data == data)
			printf("ELEMENT ALREADY PRESENT\n");
		else
		{
			prev = NULL;
			temp_b = MakeNode(data);
			temp_b -> next = b_tree;
			b_tree = temp_b;
			b_tree = sort(b_tree);
			int length = 0;
			lptr = b_tree;
			printList(lptr);
			while(lptr != NULL)
			{
				lptr = lptr -> next;
				length ++;
			}
			if(length > m - 1)
			{
				b_Node *ptr1,*ptr2;
				ptr1 = ptr2 = b_tree;
				while(ptr1 != NULL && ptr2 != NULL && ptr2 -> next != NULL)
				{
					prev = ptr1;
					ptr1 = ptr1 -> next;
					ptr2 = ptr2 -> next -> next;
				}
				b_Node *right_tree = ptr1 -> next;
				prev -> next = NULL;
				b_Node *left_tree = b_tree;
				ptr1 -> down_left = left_tree;
				ptr1 -> down_right = right_tree;
				ptr1 -> next = NULL;
				b_tree = ptr1;
			}
		}
	}
	else
	{
			int found = 0;
			while(temp_b != NULL && found == 0)
			{
				prev = NULL;
				lptr = temp_b;
				while(lptr != NULL && lptr -> data < data)
				{
					prev = lptr;
					lptr = lptr -> next;
				}
				if(prev == NULL)
				{
					if(lptr -> data != data)
						temp_b = lptr -> down_left;
					else
						found = 1;
				}
				else if(lptr != NULL && lptr -> data == data)
				{
					found = 1;
				}
				else
				{
					if(lptr == NULL)
					{
						temp_b = prev -> down_right;
					}
					else
					{
						temp_b = lptr -> down_right;
					}
				}
			}
			if(found == 1)
			{
				printf("ELEMENT ALREADY PRESENT IN THE TREE\n");
			}
			else
			{
				
			}
	}
	return b_tree;
}
int main()
{
	b_Node *node;
	b_Node *b_tree = NULL;
	int data,i;
	int num;
	printf("ENTER NUMBER OF DATA:\n");
	scanf("%d",&num);
	for(i=0;i<num;i++)
	{
		printf("ENTER DATA:");
		scanf("%d",&data);
		node = MakeNode(data);
		if(b_tree == NULL)
			b_tree = node;
		else
		{
			b_tree = Insert(b_tree,data);
		}
	}
	int choice = 1;
	while(choice <= 3)
	{
		printf("ENTER FROM FOLLOWING:\n");
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Traverse\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				printf("ENTER DATA:\n");
				int data;
				scanf("%d",&data);
				b_tree = Insert(b_tree,data);
				break;
			}
			case 2:
			{
				printf("ENTER DATA:\n");
				int data;
				scanf("%d",&data);
				b_tree = Insert(b_tree,data);
				break;
			}
			case 3:
			{
				printTree(b_tree);
				break;
			}
			default:
				printf("INVALID INPUT\n");
		}
	}
	
	return 0;
}