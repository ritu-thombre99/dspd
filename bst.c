#include<stdio.h>
#include<stdlib.h>
typedef struct Tree_Node_tag
{
	int data;
	struct Tree_Node_tag *left;
	struct  Tree_Node_tag *right;
} Tree_Node;
int height(Tree_Node *root)
{
	int retval,left_ht,right_ht;
	if(root == NULL)
	{
		retval = -1;
	}
	else if(root -> left == NULL && root -> right == NULL)
	{
		retval = 0;
	}
	else
	{
		left_ht = height(root -> left);
		right_ht = height(root -> right);
		if(left_ht > right_ht)
		{
			retval = 1 + left_ht;
		}
		else
		{
			retval = 1 + right_ht;
		}
	}
	return retval;
}
void InOrder(Tree_Node *root)
{
	if(root != NULL)
	{
		InOrder(root -> left);
		printf("%d ",root -> data);
		InOrder(root -> right);
	}
}
void PreOrder(Tree_Node *root)
{
	if(root != NULL)
	{
		printf("%d ",root -> data);
		PreOrder(root -> left);
		PreOrder(root -> right);	
	}
}
void PostOrder(Tree_Node *root)
{
	if(root != NULL)
	{
		PostOrder(root -> left);
		PostOrder(root -> right);
		printf("%d ",root -> data);	
	}
}
//LEVEL ORDER
void printLevelOrder(Tree_Node* root,int i)
{
	if(i == 1 && root != NULL)
	{
		printf("%d ",root -> data);
	}
	else if(i > 1 && root != NULL)
	{
		printLevelOrder(root -> left,i-1);
		printLevelOrder(root -> right,i-1);
	}
}
void LevelOrder(Tree_Node *root)
{
	int h = height(root);
	int i;
	for(i=1;i<=h+1;i++)
	{
		printLevelOrder(root,i);
	}
}
Tree_Node* Insert(Tree_Node *root,int data,int *present)
{
	Tree_Node *node = (Tree_Node*)malloc(sizeof(Tree_Node));
	node -> data = data;
	node -> left = node -> right = NULL;
	Tree_Node *p = root;
	int done;
	*present = 0;
	if(root == NULL)
		root = node;
	else
	{
		while(!done)
		{
			if(node -> data < p -> data)
			{
				if(p -> left != NULL)
					p = p -> left;
				else
				{
					done = 1;
					p -> left = node;
				}
			}
			else if(node -> data > p -> data)
			{
				if(p -> right != NULL)
					p = p -> right;
				else
				{
					done = 1;
					p -> right = node;
				}
			}
			else
			{
				*present = 1;
				done = 1;
			}
		}
	}
	return root;
}
Tree_Node* Create(Tree_Node *root)
{
	printf("ENTER THE NUMBER OF NODES:");
	int n;
	scanf("%d",&n);
	int i = 0,data,present;
	while(i < n)
	{
		printf("ENTER DATA:");
		scanf("%d",&data);
		root = Insert(root,data,&present);
		if(present == 0)
		{
			printf("INSERTED SUCCESSFULLY\n");
			}
		else
		{
			printf("ELEMENT ALREADY PRESENT\n");
		}
		i++;
	}
	return root;
}
void deleteNode(Tree_Node **pptr)
{
	Tree_Node *p = *pptr;
	if(p -> right == NULL)
	{
		*pptr = p -> left;
		free(p);
	}
	else if(p -> left == NULL)
	{
		*pptr = p -> right;
		free(p);
	}
	else
	{
		Tree_Node *temp,*prev;
		for(temp = p -> left;temp -> right != NULL;)
		{
			prev = temp;
			temp = temp -> right;
		}
		prev -> right = temp -> left;
		temp -> left = p -> left;
		temp -> right = p -> right;
		*pptr = temp;
		free(p);
	}
}
Tree_Node* delete(Tree_Node *root,int data,int *present)
{
	*present = 1;
	Tree_Node *prev = NULL,*p = root;
	while(p != NULL && p -> data != data)
	{
		if(data < p -> data)
		{
			prev = p;
			p = p -> left;
		}
		else
		{
			prev = p;
			p = p -> right;
		}
	}
	if(p != NULL)
	{
		if(prev == NULL)
		{
			deleteNode(&root);
		}
		else
		{	
			if(data == prev -> right -> data)
				deleteNode(&prev -> right);
			else
				deleteNode(&prev -> left);
		}
	}
	else
		*present = 0;
	return root;
}
//FUNCTION TO FIND MAXIMUM SUM OF A LEVEL
void LevelSum(Tree_Node *root,int level,int* sum)
{
	if(level == 1 && root != NULL)
	{
		*sum = *sum + root -> data;
	}
	else if(level > 1 && root != NULL)
	{
		LevelSum(root -> left,level - 1,sum);
		LevelSum(root -> right,level - 1,sum);
	}
}
int MaxLevelSum(Tree_Node *root,int *level)
{
	int max = 0,i,sum;
	int h = height(root);
	for(i=1;i<=h+1;i++)
	{
		sum = 0;
		LevelSum(root,i,&sum);
		if(sum > max)
		{
			*level = i - 1;
			max = sum;
			printf("\n\nmax:%d\nsum:%d\n\n",max,sum);
		}
	}
	return max;
}
//LEVEL OF A NODE
int getLevel(Tree_Node *root,int data)
{
	Tree_Node *temp = root;
	int i = 0,level = -1;
	while(temp != NULL && data != temp -> data )
	{
		if(data < temp -> data)
		{
			temp = temp -> left;
			i++;
		}
		else
		{
			temp = temp -> right;
			i++;
		}
	}
	if(temp != NULL)
		level = i;
	return level;
}
int main()
{
	int x;
	Tree_Node *root = NULL;
	do
	{
		printf("Choose from the following:\n");
		printf("1.Create binary search tree\n");
		printf("2.Insert into Binary Search tree\n");
		printf("3.Delete Node from Binary Search tree\n");
		printf("4.In Order traversal\n");
		printf("5.Pre Order traversal\n");
		printf("6.Post Order traversal\n");
		printf("7.Level Order traversal\n");
		printf("8.Height of a tree\n");
		printf("9.Maximum level sum\n");
		printf("10.Get level of a node in a binary tree\n");
		//printf("11.Create binary tree with level order traversal\n");
		scanf("%d",&x);
		switch(x)
		{
			case 1:
			{
				root = NULL;
				root = Create(root);
				break;
			}
			case 2:
			{
				int present;
				printf("ENTER DATA:");
				int data;
				scanf("%d",&data);
				root = Insert(root,data,&present);
				if(present == 0)
				{
					printf("INSERTED SUCCESSFULLY\n");
				}
				else
				{
					printf("ELEMENT ALREADY PRESENT\n");
				}
				break;
			}
			case 3:
			{
				int data,present;
				printf("ENTER DATA YOU WANT TO DELETE:");
				scanf("%d",&data);
				root = delete(root,data,&present);
				if(present == 0)
				{
					printf("ELEMENT NOT FOUND\nDELETION FAILED\n");
				}
				else
				{
					printf("ELEMENT DELETED SUCCESSFULLY\n");
				}
				break;
			}
			case 4:
			{
				InOrder(root);
				printf("\n");
				break;
			}
			case 5:
			{
				PreOrder(root);
				printf("\n");
				break;
			}
			case 6:
			{
				PostOrder(root);
				printf("\n");
				break;
			}
			case 7:
			{
				LevelOrder(root);
				printf("\n");
				break;
			}
			case 8:
			{
				int h = height(root);
				printf("Height of a tree is:%d\n",h);
				break;
			}
			case 9:
			{
				int level;
				int sum = MaxLevelSum(root,&level);
				printf("Maximum level sum is %d at level %d\n",sum,level);
				break;
			}
			case 10:
			{
				int level,data;
				printf("ENTER DATA TO FIND IT'S LEVEL:");
				scanf("%d",&data);
				level = getLevel(root,data);
				if(level != -1)
					printf("%d is at level %d\n\n",data,level);
				else
					printf("%d NOT FOUND IN TREE\n",data);
				break;
			}
			default:
				printf("INVALID INPUT\n");
		}
	} while(x <= 10);
	return 0;
}