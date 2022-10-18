#include <stdio.h>
#include<string.h>
#include <stdlib.h>

struct Node 
{
	char un[100], pf[100], ps[100], st[10];
    int height;
    Node *left, *right;
};

Node* createNode(const char un[], const char pf[], const char ps[], const char st[])
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->un, un);
    strcpy(newNode->pf, pf);
    strcpy(newNode->ps, ps);
    strcpy(newNode->st, st);
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    
    return newNode;
}

int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int getHeight(struct Node* curr)
{
	if (curr == NULL)
	{
		return 0;
	}
	else
	{
		return curr->height;
	}
}

void updateHeight(struct Node* curr)
{
	int left = getHeight(curr->left);
	int right = getHeight(curr->right);
	curr->height = max(left, right) + 1;
}

int balanceFactor(struct Node* curr)
{
	int left = getHeight(curr->left);
	int right = getHeight(curr->right);
	return left - right;
}

Node* rightRotate(struct Node* curr)
{
	Node* child = curr->left;
	Node* gchild = child->right;
	
	curr->left = gchild;
	child->right = curr;
	
	updateHeight(curr);
	updateHeight(child);
	
	return child;
}

Node* leftRotate(struct Node* curr)
{
	Node* child = curr->right;
	Node* gchild = child->left;
	
	curr->right = gchild;
	child->left = curr;
	
	updateHeight(curr);
	updateHeight(child);
	
	return child;
}

Node* rebalance(struct Node* curr)
{
	int balance = balanceFactor(curr);
	
	if (balance > 1)
	{
		if (balanceFactor(curr->left) < 0)
		{
			curr->left = leftRotate(curr->left);
		}
		curr = rightRotate(curr);
	}
	else if (balance < -1)
	{
		if (balanceFactor(curr->right) > 0)
		{
			curr->right = rightRotate(curr->right);
		}
		curr = leftRotate(curr);
	}

	return curr;
}

Node* insert(struct Node* curr, const char un[], const char pf[], const char ps[], const char st[])
{
    if (curr == NULL)
    {
    	return createNode(un, pf, ps, st);
	}
    else
    {
	    if (strcmp(un, curr->un) < 0)
	    {
	        curr->left = insert(curr->left, un, pf, ps, st);
		}
	    else if (strcmp(un, curr->un) > 0)
	    {
	        curr->right = insert(curr->right, un, pf, ps, st);
		}
	}
			
	updateHeight(curr);
		
	return rebalance(curr);
}

Node* predecessor (struct Node* curr)
{
    Node* temp = curr->left;
    while (temp->right != NULL)
    {
    	temp = temp->right;
	} 
    return temp;
}

Node* deleteNode(struct Node* curr, const char un[])
{
    if (curr == NULL)
    {
    	return NULL;
	}
    else
	{
	    if (strcmp(un, curr->un) < 0)
	    {
	    	curr->left = deleteNode(curr->left, un);
		}
	    else if (strcmp(un, curr->un) > 0)
	    {
	    	curr->right = deleteNode(curr->right, un);
		}
	    else 
		{
			if (curr->left == NULL && curr->right == NULL) 
			{
	            free(curr);
				return NULL;
	        }
	        else if (curr->left == NULL && curr->right != NULL) 
			{
	            Node* temp = curr->right;
	            free(curr);
	            return temp;
	        }
	        else if (curr->right == NULL && curr->left != NULL) 
			{
	            Node* temp = curr->left;
	            free(curr);
	            return temp;
	        }
	 		else
			{
				Node* temp = predecessor(curr);
		        strcpy(curr->un, temp->un);
		        strcpy(curr->pf, temp->pf);
		        strcpy(curr->ps, temp->ps);
		        strcpy(curr->st, temp->st);
		        curr->left = deleteNode(curr->left, temp->un);
			}
	    }
	}
	
	updateHeight(curr);
	
	return rebalance(curr);
}

Node* search(struct Node* curr, const char un[])
{
	if (curr == NULL || strcmp(un, curr->un) == 0)
    {
    	return curr;
	}
    else if (strcmp(un, curr->un) < 0)
    {
    	return search(curr->left, un);
	}
	else if (strcmp(un, curr->un) > 0)
    {
    	return search(curr->right, un);
	}
}

void preorder(struct Node* curr)
{
    if (curr != NULL) 
	{
        printf("| %-26s | %-26s | %-6d | %-26s | %-16s |\n", curr->un, curr->pf, curr->height, curr->ps, curr->st);
        preorder(curr->left);
        preorder(curr->right);
    }
}

void inorder(struct Node* curr)
{
    if (curr != NULL) 
	{
        inorder(curr->left);
        printf("| %-26s | %-26s | %-6d | %-26s | %-16s |\n", curr->un, curr->pf, curr->height, curr->ps, curr->st);
        inorder(curr->right);
    }
}

void postorder(struct Node* curr)
{
    if (curr != NULL) 
	{
        postorder(curr->left);
        postorder(curr->right);
        printf("| %-26s | %-26s | %-6d | %-26s | %-16s |\n", curr->un, curr->pf, curr->height, curr->ps, curr->st);
    }
}

void view(struct Node* curr)
{
	if (curr == NULL)
	{
		printf("There is no data!\n");
		return;
	}
	else
	{
		char x[10];
		do{
			printf("Choose order: [Pre | In | Post]: ");
			scanf("%[^\n]", x);
			getchar();
			if(strcmp(x, "Pre")==0)
			{
				printf("====================================================================================================================\n");
			    printf("| Username                   | Platform                   | Height | Password                   | Strength         |\n");
			    printf("====================================================================================================================\n");
				preorder(curr);
				printf("====================================================================================================================\n");
			}
			else if (strcmp(x, "In")==0)
			{
				printf("====================================================================================================================\n");
			    printf("| Username                   | Platform                   | Height | Password                   | Strength         |\n");
			    printf("====================================================================================================================\n");
				inorder(curr);
				printf("====================================================================================================================\n");
			}
			else if((strcmp(x, "Post")==0))
			{
				printf("====================================================================================================================\n");
			    printf("| Username                   | Platform                   | Height | Password                   | Strength         |\n");
			    printf("====================================================================================================================\n");
				postorder(curr);
				printf("====================================================================================================================\n");
			}
		} while (strcmp(x, "Pre")!=0 && strcmp(x, "In")!=0 && strcmp(x, "Post")!=0);
	}
}

Node* insertAccount(struct Node* curr)
{
	char un[100], pf[100], ps[100], st[10];
	int factor;
    
    do{
    	printf("Input username [6-80 characters]: ");
    	scanf("%[^\n]", un);
    	getchar();
	} while (strlen(un)<6 || strlen(un)>80);
	
	do{
    	printf("Input platform [6-80 characters]: ");
    	scanf("%[^\n]", pf);
    	getchar();
	} while (strlen(pf)<6 || strlen(pf)>80);
	
	do{
    	printf("Input password [<60 characters]: ");
    	scanf("%[^\n]", ps);
    	getchar();
    	
    	int len=0, num=0, upper=0, lower=0;
	    for (int i = 0; i < strlen(ps); i++)
		{
			if(strlen(ps)>6) //length
			{
				len = 1;
			}
	        if(ps[i] >= 48 && ps[i] <= 57) //number
			{
	            num = 1;
	        }
	        if(ps[i] >= 65 && ps[i] <= 90) //uppercase
			{
	            upper = 1;
	        }
	        if(ps[i] >= 97 && ps[i] <= 122) //lowercase
			{
	            lower = 1;
	        }
	    }
	    
	    factor = len+num+upper+lower;
	    if(factor==1)
	    {
	    	strcpy(st, "Invalid");
		}
		else if (factor==2)
		{
			strcpy(st, "Weak");
		}
		else if (factor==3)
		{
			strcpy(st, "Medium");
		}
		else if (factor==4)
		{
			strcpy(st, "Strong");
		}
    
	} while (strlen(ps)==0 || strlen(ps)>=60 || factor==1);
	
	char x;
	do{
		printf("Do you want to insert %s login? [y | n]\n", un);
		printf(">> ");
		scanf("%c", &x);
		getchar();
	} while (x!='y' && x!='n');
	
	if (x=='y')
	{
		return insert(curr, un, pf, ps, st);
	}
	else
	{
		return curr;
	}
}

Node* deleteAccount(struct Node* curr)
{
	if (curr == NULL)
	{
		printf("There is no data!\n");
		return NULL;
	}
	else
	{
		char un[100];
		Node* found = NULL;
		view(curr);
		printf("Which account you want to delete?\n");
		do{
			printf("Username ['cancel' to exit] >> ");
			scanf("%[^\n]", un);
			getchar();
			if(strcmp(un, "cancel")==0)
			{
				return curr;
			}
			found = search(curr, un);
		} while (found == NULL);
		
		char x;
		do{
			printf("Do you want to delete %s account? [y | n]\n", un);
			printf(">> ");
			scanf("%c", &x);
			getchar();
		} while (x!='y' && x!='n');
		
		if (x=='y')
		{	
			return deleteNode(curr, un);
		}
		else
		{
			return curr;
		}
	}
}

Node* deleteAll(struct Node* curr)
{
	while(curr!=NULL)
	{
		curr = deleteNode(curr, curr->un);
	}
	return curr;
}

int main()
{
	Node* root = NULL;
	int menu;
	while(true)
	{
		printf("JPassword saver\n");
		printf("1. View Accounts\n");
		printf("2. Insert Account\n");
		printf("3. Delete Account\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &menu);
		getchar();
		
		switch (menu)
		{
			case 1:
				view(root);
				printf("\n");
				break;
			case 2:
				root = insertAccount(root);
				printf("\n");
				break;
			case 3:
				root = deleteAccount(root);
				printf("\n");
				break;
			case 4:
				root = deleteAll(root);
				printf("Program exited!\n");
				return 0;
			default:
				printf("Please choose valid input! [1 - 4]\n");
		 		break;
		}
	}
}
