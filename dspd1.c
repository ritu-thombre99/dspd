#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 500
typedef enum{FALSE,TRUE} boolean;
typedef enum{FAILURE,SUCCESS} status_code;
typedef struct Product_tag
{
	int purchases;
	int availability;
	char Model_name[50];
	int price;
	char category[50];
	struct Product_tag *next_product;
} Product_type;
typedef struct Customer_Product_tag
{
	char Model_name[50];
	char category[50];
	int price;
	int quantity;
	struct Customer_Product_tag *next_product;
} Customer_Product_type;
typedef struct Customer_tag
{
	char name[50];	
	long int phone;
	char email[200];
	char address[200];
	int user_id;
	int number_of_items_bought;
	int amount;
	char paymentMode[50];
	Product_type *wishlist;
	Customer_Product_type *history;
	Customer_Product_type *favourites;
} Customer_type;
//Registration function
status_code Register(Customer_type Customer[],int *last_index)
{
	status_code retval = SUCCESS;
	char name[50];	
	long int phone;
	char email[100];
	char address[200];
	int user_id,i = 0;
	printf("Enter your name:");
	scanf("\n");
	scanf("%[^\n]s",name);
	while(i < *last_index && retval == SUCCESS)
	{
		if(strcmp(Customer[i].name,name) == 0)
			retval = FAILURE;
		i++;
	}
	if(retval == SUCCESS)
	{
		printf("Enter your address:");
		scanf("\n");
		scanf("%[^\n]s",address);
		printf("Enter your phone:");
		scanf("%ld",&phone);
		i = 0;
		int temp = phone;
		while(temp > 0)
		{
			temp = temp / 10;
			i++;
		}
		if(i != 10 )	
		{
			retval = FAILURE;
			printf("\n\nEnter valiid 10 digit phone number\n\n");
		}
		while(i < *last_index && retval == SUCCESS)
		{
			if(Customer[i].phone == phone)
				retval = FAILURE;
			i++;
		}
		if(retval == SUCCESS)
		{
			printf("Enter your email:");
			scanf("\n");
			scanf("%[^\n]s",email);
			char *p1,*p2;
			p1 = strchr(email, '@');
			p2 = strchr(email, '.');
			if(p1 == NULL || p2 == NULL)
			{
				retval = FAILURE;
				printf("\n\nE-mail should contain '@' and '.' \n\n");
			}
			else
			{
				i = 0;
				while(i < *last_index && retval == SUCCESS)
				{
					if(strcmp(Customer[i].email,email) == 0)
						retval = FAILURE;
					i++;
				}
				if(retval == FAILURE)
				printf("Enter unique email\nThis email already exists\n");
			}
		}
		else
			printf("Enter unique phone number\nThis number already exists\n");
	}
	else
			printf("\nEnter valid user name\nThis user name already exists\n");
	if(retval == SUCCESS)
	{
		strcpy(Customer[*last_index].name,name);
		strcpy(Customer[*last_index].email,email);
		strcpy(Customer[*last_index].address,address);
		Customer[*last_index].phone = phone;
		Customer[*last_index].user_id = (*last_index + 1);
		Customer[*last_index].paymentMode[0] = '\0';
		Customer[*last_index].wishlist = NULL;
		Customer[*last_index].history = NULL;
		Customer[*last_index].favourites = NULL;
		FILE * f=fopen("/home/ritu/Customer.txt","a");
		fprintf(f,"Name:%s\n",Customer[*last_index].name);
		fprintf(f,"Phone:%ld\n",Customer[*last_index].phone);
		fprintf(f,"E-mail:%s\n",Customer[*last_index].email);
		fprintf(f,"Address:%s\n",Customer[*last_index].address);
		fprintf(f,"User id:%d\n",Customer[*last_index].user_id);
		fprintf(f,"______________________________________________________________\n\n");
		fclose(f);
		(*last_index)++;
		printf("\n\nYour id is:%d\n\n",(*last_index));
	}
	return retval;
}
//Login function
status_code Login(Customer_type Customer[],int *id)
{
	status_code retval = SUCCESS;
	int user_id;
	char email[200];
	printf("Enter your id:");
	scanf("%d",&user_id);
	printf("Enter your email:");
	scanf("\n");
	scanf("%[^\n]s",email);
	if(user_id >= MAX)
	{
		printf("Invalid id\nPlease register if you haven't registered\n\n");
		retval = FAILURE;
	}
	else if(Customer[user_id - 1].user_id == 0)
	{
		printf("Invalid id\nPlease register if you haven't registered\n\n");
		retval = FAILURE;
	}
	else
	{
		*id = user_id;
		if(strcmp(Customer[user_id - 1].email,email) != 0)
		{
			printf("Enter valid email address\n\n");
			retval = FAILURE;
		}
	}
	return retval;
}
int hashProduct(char str[50])
{
	int index;
	if(strcmp(str,"Mobile_phones") == 0)
	{
		index = 0;
	}
	else if(strcmp(str,"Mobile_accessories") == 0)
	{
		index = 1;
	}
	else if(strcmp(str,"Laptops,Computer_accessories_and_tablets") == 0)
	{
		index = 2;
	}
	else if(strcmp(str,"Electronic_gadgets") == 0)
	{
		index = 3;
	}
	else if(strcmp(str,"Games_and_gaming_consoles") == 0)
	{
		index = 4;
	}
	else
	{
		printf("\n\n%s\n\n",str);
		index = 5;
	}
	return index;
}
//sort favourites
Customer_Product_type* sort_favourites(Customer_Product_type* favourites)
{
	int sort = 0,quantity,price;
	char Model_name[50],category[50];
	Customer_Product_type *ptr1,*ptr2;
	ptr1 = favourites;
	while(ptr1 != NULL && sort == 0)
	{
		sort = 1;
		ptr2 = favourites;
		while(ptr2 -> next_product != NULL)
		{
			if(ptr2 -> quantity < ptr2 -> next_product -> quantity)
			{
				quantity = ptr2 -> quantity;
				ptr2 -> quantity = ptr2 -> next_product -> quantity;
				ptr2 -> next_product -> quantity = quantity;
				price = ptr2 -> price;
				ptr2 -> price = ptr2 -> next_product -> price;
				ptr2 -> next_product -> price = price;
				strcpy(Model_name,ptr2 -> Model_name);
				strcpy(ptr2 -> Model_name,ptr2 -> next_product -> Model_name);
				strcpy(ptr2 -> next_product -> Model_name,Model_name);
				strcpy(category,ptr2 -> category);
				strcpy(ptr2 -> category,ptr2 -> next_product -> category);
				strcpy(ptr2 -> next_product -> category,category);
				sort = 0;
			}
			ptr2 = ptr2 -> next_product;
		}
	}
	return favourites;
}
//User Page
void UserPage(int id,Product_type *Product[],Customer_type Customer[MAX])
{
	Customer_Product_type *temp_customer_product;
	Product_type *temp_product;
	int i;
	system("clear");
	printf("You have logged in successfully\n");
	printf("Welcome,%s\n",Customer[id - 1].name);
	printf("\nGet started to shop from the comfort of your own home\n\n");
	int shopping_option = 1;
	while(shopping_option <= 8 && shopping_option != 9)
	{	
		printf("Choose from the following:\n");
		printf("1.Start shopping (browse products)\n");
		printf("2.Order\n");
		printf("3.Add to wishlist\n");
		printf("4.Return product\n");
		printf("5.Print my wishlist\n");
		printf("6.Print product list for available products\n");	
		printf("7.Print my Information\n");
		printf("8.Print my favourites\n");
		printf("9.Logout\n");
		scanf("%d",&shopping_option);
		switch(shopping_option)
		{
			case 1:
			{
				int product_select = 1;
				while(product_select <= 6 && product_select != 0)
				{
					printf("Choose the category from the following\n");
					printf("1.Mobile phones\n");
					printf("2.Mobile accessories\n");
					printf("3.Laptops,Computer accessories and Tablets\n");
					printf("4.Electronic gadgets\n");
					printf("5.Games and gaming consoles\n");
					printf("6.Home and Kitchen appliances\n");
					printf("\n\nEnter 0 to return\n\n");
					scanf("%d",&product_select);
					if(product_select <= 6 && product_select >= 1)
					{
						temp_product = Product[product_select - 1];
						while(temp_product != NULL)
						{
							printf("Category:%s\n",temp_product -> category);
							printf("Model name:%s\n",temp_product -> Model_name);
							printf("Price:%d\n",temp_product -> price);
							printf("Purchases:%d\n",temp_product -> purchases);
							printf("Availability:%d\n",temp_product -> availability);
							temp_product = temp_product -> next_product;
							printf("\n");
						}
						printf("\n\n\n");
					}
					else
					{
						printf("\nInvalid input\n");
					}
				}
				break;
			}
			case 2:
			{
				int product_select;
				printf("Choose the category from the following\n");
				printf("1.Mobile phones\n");
				printf("2.Mobile accessories\n");
				printf("3.Laptops,Computer accessories and Tablets\n");
				printf("4.Electronic gadgets\n");
				printf("5.Games and gaming consoles\n");
				printf("6.Home and Kitchen appliances\n");
				scanf("%d",&product_select);
				if(product_select <= 6 && product_select >= 1)
				{
					int count = 1,product;
					temp_product = Product[product_select - 1];
					while(temp_product != NULL)
					{	
						printf("%d\n",count);
						count ++;
						printf("Category:%s\n",temp_product -> category);
						printf("Model name:%s\n",temp_product -> Model_name);
						printf("Price:%d\n",temp_product -> price);
						printf("Purchases:%d\n",temp_product -> purchases);
						printf("Availability:%d\n",temp_product -> availability);
						temp_product = temp_product -> next_product;
						printf("\n");
					}
					count --;
					printf("\n\n\n");
					printf("Enter product number:");
					scanf("%d",&product);
					//printf("\n\nCount%d:\n\nProduct:%d\n\n",count,product);
					if(product > count)
					{
						printf("\nInvalid input\n");
					}
					else if(product <= count)
					{
						temp_product = Product[product_select - 1];
						count = 1;
						while(count != product)
						{
							temp_product = temp_product -> next_product;
							count ++;
						}
						if(temp_product -> availability == 0)
						{
							printf("The product is not currently available\n");
						}
						else
						{
							printf("Category:%s\n",temp_product -> category);
							printf("Model name:%s\n",temp_product -> Model_name);
							printf("Price:%d\n",temp_product -> price);
							printf("Purchases:%d\n",temp_product -> purchases);
							printf("Availability:%d\n",temp_product -> availability);
							int are_you_sure;
							printf("Are you sure you want to buy this product\n1.Yes\n2.No\n");
							scanf("%d",&are_you_sure);
							if(are_you_sure == 1)
							{
								int quantity;
								char Model_name[50];
								strcpy(Model_name,temp_product -> Model_name);
								printf("Enter quantity:");
								scanf("%d",&quantity);
								Customer[id - 1].number_of_items_bought = Customer[id - 1].number_of_items_bought + quantity;
								temp_product -> purchases = temp_product -> purchases + quantity;
								temp_product -> availability = temp_product -> availability - quantity;
								printf("Enter payment mode\n");
								printf("1.Buy Now Pay Later\n");
								printf("2.Cash on Delivery\n");
								printf("3.Debit card\n");
								printf("4.Credit card\n");
								printf("5.Net banking\n");
								printf("6.UPI Enabled\n");
								printf("7.PhonePe\n");
								char paymentMode[50];
								scanf("\n");
								scanf("%[^\n]s",paymentMode);
								strcpy(Customer[id - 1].paymentMode,paymentMode);
								Customer[id - 1].amount = Customer[id - 1].amount + (quantity * temp_product -> price);
								Customer_Product_type *history_temp;
								history_temp = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
								strcpy(history_temp -> Model_name,temp_product -> Model_name);
								strcpy(history_temp -> category,temp_product -> category);
								history_temp -> quantity = quantity;
								history_temp  -> price = temp_product -> price;
								history_temp -> next_product = NULL;
								if(Customer[id - 1].history == NULL)
								{
									Customer[id - 1].history = history_temp;
								}
								else
								{
									history_temp -> next_product = Customer[id - 1].history;
									Customer[id - 1].history = history_temp;
								}
								printf("Your order has been placed successfully\n");
								Customer_Product_type *favourites_temp,*favourites_temp1;
								favourites_temp = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
								strcpy(favourites_temp -> Model_name,temp_product -> Model_name);
								strcpy(favourites_temp -> category,temp_product -> category);
								favourites_temp -> quantity = quantity;
								favourites_temp  -> price = temp_product -> price;
								favourites_temp -> next_product = NULL;
								if(Customer[id - 1].favourites == NULL)
								{
									Customer[id - 1].favourites = favourites_temp;
								}
								else
								{
									favourites_temp1 = Customer[id - 1].favourites;
									while(favourites_temp1 != NULL && strcmp(favourites_temp1 -> Model_name,Model_name) != 0)
									{
										favourites_temp1 = favourites_temp1 -> next_product;
									}
									if(favourites_temp1 == NULL)
									{
										favourites_temp -> next_product = Customer[id - 1].favourites;
										Customer[id - 1].favourites = favourites_temp;
									}
									else
									{
										favourites_temp1 -> quantity = favourites_temp1 -> quantity + quantity;
									}
									Customer[id - 1].favourites = sort_favourites(Customer[id - 1].favourites);
								}
							}
							else
							{
								printf("Order cancelled\n");
							}
						}
					}
				}
				else
				{
					printf("Enter valid category\n");
				}
				break;
			}
			case 3:
			{
					int count = 1,product;
					int product_select;
					printf("Choose the category from the following\n");
					printf("1.Mobile phones\n");
					printf("2.Mobile accessories\n");
					printf("3.Laptops,Computer accessories and Tablets\n");
					printf("4.Electronic gadgets\n");
					printf("5.Games and gaming consoles\n");
					printf("6.Home and Kitchen appliances\n");
					scanf("%d",&product_select);	
					if(product_select <= 0 && product_select >=7)
						printf("\n\nEnter valid category\n");
					else
					{
						temp_product = Product[product_select - 1];
						while(temp_product != NULL)
						{	
							printf("%d\n",count);
							count ++;
							printf("Category:%s\n",temp_product -> category);
							printf("Model name:%s\n",temp_product -> Model_name);
							printf("Price:%d\n",temp_product -> price);
							printf("Purchases:%d\n",temp_product -> purchases);
							printf("Availability:%d\n",temp_product -> availability);
							temp_product = temp_product -> next_product;
							printf("\n");
						}
						count --;
						printf("\n\n\n");
						printf("Enter product number:");
						scanf("%d",&product);
						if(product > count)
						{
							printf("\nInvalid input\n");
						}
						else if(product <= count)
						{
							temp_product = Product[product_select - 1];
							count = 1;
							while(count != product)
							{
								temp_product = temp_product -> next_product;
								count ++;
							}
							Product_type *temp_product1 = Customer[id - 1].wishlist;
							int found = 0;
							while(found == 0 && temp_product1 != NULL)
							{
								if(strcmp(temp_product1 -> Model_name,temp_product -> Model_name) == 0)
									found = 1;
								temp_product1 = temp_product1 -> next_product;
							}
							if(found == 1)
								printf("\nProduct already present in your wishlist\n\n");
							else	
							{
								temp_product -> next_product = Customer[id - 1].wishlist;
								Customer[id - 1].wishlist = temp_product;
								printf("\n\nProduct successfuly added to the wishlist\n\n");
							}
						}
					}
					break;
			}
			case 4:
			{
				temp_customer_product = Customer[id - 1].history;
				int count = 1;
				while(temp_customer_product != NULL)
				{
					printf("%d.\n",count);
					count ++;
					printf("Category:%s\n",temp_customer_product -> category);
					printf("Model name:%s\n",temp_customer_product -> Model_name);
					printf("Price:%d\n",temp_customer_product -> price);
					printf("Quantity:%d\n",temp_customer_product -> quantity);
					temp_customer_product = temp_customer_product -> next_product;
					printf("\n");
				}
				count --;
				int product;
				printf("Enter product number you want to return\n");
				scanf("%d",&product);
				if(product > count)
				{
					printf("\n\nInvalid input\n\n");
				}
				else if(product <= count)
				{
					char Model_name[50];
					Customer_Product_type *prev = NULL,*temp_customer_product1;
					temp_customer_product = Customer[id - 1].history;
					count = 1;
					while(count != product)
					{
						prev = temp_customer_product;
						temp_customer_product = temp_customer_product -> next_product;
						count ++;
					}
					printf("Do you really want to return %s \n",temp_customer_product -> Model_name);
					int are_you_sure;
					printf("1.Yes\n2.No\n");
					scanf("%d",&are_you_sure);
					if(are_you_sure == 1)
					{
						int index,found = 0,quantity,returnPrice;
						Customer_Product_type *temp_customer_product2;
						index = hashProduct(temp_customer_product -> category);
						printf("\nIndex:%d\n",index );
						temp_product = Product[index];
						while(temp_product != NULL && found == 0)
						{
							if(strcmp(temp_product -> Model_name,temp_customer_product -> Model_name) == 0)
							{
								found = 1;
								strcpy(Model_name,temp_product -> Model_name);
								quantity = temp_customer_product -> quantity;
								temp_product -> availability = temp_product -> availability + temp_customer_product -> quantity;
								temp_product -> purchases = temp_product -> purchases - temp_customer_product -> quantity;
								Customer[id - 1].number_of_items_bought = Customer[id - 1].number_of_items_bought - quantity;
								returnPrice = quantity * temp_product -> price;
							}
							temp_product = temp_product -> next_product;
						}
						if(prev == NULL)
						{
							temp_customer_product1 = Customer[id - 1].history;
							Customer[id - 1].history = Customer[id - 1].history -> next_product;
							free(temp_customer_product1);
						}
						else
						{
							temp_customer_product1 = temp_customer_product;
							prev -> next_product = temp_customer_product -> next_product;
							temp_customer_product = temp_customer_product -> next_product;
							free(temp_customer_product1);
						}
						printf("\nProduct returned successfully\n\n");
						Customer[id - 1].amount = Customer[id - 1].amount - returnPrice;
						printf("\nYour %d money has been returned to your account\n\n",returnPrice);
						if(strcmp(Customer[id - 1].favourites -> Model_name,Model_name) == 0)
						{
							if(Customer[id - 1].favourites -> quantity == quantity)
							{
								temp_customer_product1 = Customer[id - 1].favourites;
								Customer[id - 1].favourites = Customer[id - 1].favourites -> next_product;
								free(temp_customer_product1);
							}
							else
							{
								Customer[id - 1].favourites -> quantity = Customer[id - 1].favourites -> quantity - quantity;
							}
							Customer[id - 1].favourites = sort_favourites(Customer[id - 1].favourites);
						}
						else
						{
							Customer_Product_type *favourites_temp1 = Customer[id - 1].favourites,*prev = NULL;
							while(strcmp(favourites_temp1 -> Model_name,Model_name) != 0)
							{
								prev = favourites_temp1;
								favourites_temp1 = favourites_temp1 -> next_product;
							}
							if(favourites_temp1 -> quantity == quantity)
							{
								temp_customer_product1 = favourites_temp1;
								prev -> next_product = favourites_temp1 -> next_product;
								free(temp_customer_product1);
							}
							else
							{
								favourites_temp1 -> quantity = favourites_temp1 -> quantity - quantity;
							}
					        Customer[id - 1].favourites = sort_favourites(Customer[id - 1].favourites);
						}
					}
					else
					{
						printf("\nReturn cancelled\n");
					}
				}
				break;
			}
			case 5:
			{
				printf("\n\nHere's your wishlist\n\n");
				temp_product = Customer[id - 1].wishlist;
				if(temp_product == NULL)
					printf("\n\nYou have no wishlist\n\n");
				else
				{
					while(temp_product != NULL)
					{
						printf("Category:%s\n",temp_product -> category);
						printf("Model name:%s\n",temp_product -> Model_name);
						printf("Price:%d\n",temp_product -> price);
						printf("Purchases:%d\n",temp_product -> purchases);
						printf("Availability:%d\n",temp_product -> availability);
						temp_product = temp_product -> next_product;
						printf("\n");
					}
				}
				break;
			}
			case 6:
			{
				for(i=0;i<6;i++)
				{		
					temp_product = Product[i];
					while(temp_product != NULL)
					{
						if(temp_product -> availability != 0)
						{
							printf("Categpry:%s\n",temp_product -> category);
							printf("Model name:%s\n",temp_product -> Model_name);
							printf("Price:%d\n",temp_product -> price);
							printf("Purchases:%d\n",temp_product -> purchases);
							printf("Availability:%d\n",temp_product -> availability);
							printf("\n");
						}
						temp_product = temp_product -> next_product;
					}
					printf("\n\n\n");
				}
				break;
			}
			case 7:
			{
				printf("Customer Name:%s\n",Customer[id - 1].name);
				printf("Customer Address:%s\n",Customer[id - 1].address);
				printf("Customer E-mail:%s\n",Customer[id - 1].email);
				printf("Customer phone:%ld\n",Customer[id - 1].phone);
				printf("Customer Payment Mode:%s\n",Customer[id - 1].paymentMode);
				printf("Number of items customer has broought:%d\n",Customer[id - 1].number_of_items_bought);
				printf("You have spent %d amount of money till now\n\n",Customer[id - 1].amount);
				printf("\n\n\n");
				printf("Customer's history\n\n");
				temp_customer_product = Customer[id - 1].history;
				while(temp_customer_product != NULL)
				{
					printf("Category:%s\n",temp_customer_product -> category);
					printf("Model name:%s\n",temp_customer_product -> Model_name);
					printf("Price:%d\n",temp_customer_product -> price);
					printf("Quantity:%d\n",temp_customer_product -> quantity);
					temp_customer_product = temp_customer_product -> next_product;
					printf("\n");			
				}
				break;
			}
			case 8:
			{
				printf("Customer's favourites\n\n");
				temp_customer_product = Customer[id - 1].favourites;
				if(temp_customer_product == NULL)
					printf("\n\nYou have no favourites\n\n");
				else
				{
					while(temp_customer_product != NULL)
					{
						printf("Category:%s\n",temp_customer_product -> category);
						printf("Model name:%s\n",temp_customer_product -> Model_name);
						printf("Price:%d\n",temp_customer_product -> price);
						printf("Quantity:%d\n",temp_customer_product -> quantity);
						temp_customer_product = temp_customer_product -> next_product;
						printf("\n");
					}	
				}
				break;
			}
			case 9:
			{
				FILE * f=fopen("/home/ritu/Output.txt","a");
				fprintf(f,"Name:%s\n",Customer[id - 1].name);
				fprintf(f,"Phone:%ld\n",Customer[id - 1].phone);
				fprintf(f,"E-mail:%s\n",Customer[id - 1].email);
				fprintf(f,"Address:%s\n",Customer[id - 1].address);
				fprintf(f,"User id:%d\n",Customer[id - 1].user_id);
				fprintf(f,"Numbers of items bought:%d\n",Customer[id - 1].number_of_items_bought);
				fprintf(f,"Payment Modes:%s\n",Customer[id - 1].paymentMode);
				fprintf(f,"\n\nWishlist\n\n");
				Product_type *temp_product = Customer[id - 1].wishlist;
				while(temp_product != NULL)
				{
					fprintf(f,"Name:%s\n",temp_product -> Model_name);
					fprintf(f,"Category:%s\n",temp_product -> category);
					fprintf(f,"Price:%d\n",temp_product -> price);
					temp_product = temp_product -> next_product;
					printf("\n\n");
				}
				free(temp_product);
				fprintf(f,"\n\nHistory\n\n");
				Customer_Product_type *temp_customer_history = Customer[id - 1].history;
				while(temp_customer_history != NULL)
				{
					fprintf(f,"Name:%s\n",temp_customer_history -> Model_name);
					fprintf(f,"Category:%s\n",temp_customer_history -> category);
					fprintf(f,"Price:%d\n",temp_customer_history -> price);
					fprintf(f,"Quantity:%d\n",temp_customer_history -> quantity);
					temp_customer_history = temp_customer_history -> next_product;
					printf("\n\n");
				}
				free(temp_customer_history);
				fprintf(f,"\n\nFavourites\n\n");
				Customer_Product_type *temp_customer_favourites = Customer[id - 1].favourites;
				while(temp_customer_favourites != NULL)
				{
					fprintf(f,"Name:%s\n",temp_customer_favourites -> Model_name);
					fprintf(f,"Category:%s\n",temp_customer_favourites -> category);
					fprintf(f,"Price:%d\n",temp_customer_favourites -> price);
					fprintf(f,"Quantity:%d\n",temp_customer_favourites -> quantity);
					temp_customer_favourites = temp_customer_favourites -> next_product;
					printf("\n\n");
				}
				free(temp_customer_favourites);
				fprintf(f,"__________________________________________________________________________________\n\n");
				fclose(f);
				break;
			}
			default:
				printf("Invalid input\n");
		}
	}
}
//sorting based on products
Product_type* sort_on_purchases(Product_type *Product)
{
	int sort = 0;
	Product_type *ptr1 = Product,*ptr2,*temp;
	temp = (Product_type*)malloc(sizeof(Product_type));
	while(ptr1 != NULL && sort == 0)
	{
		sort = 1;
		ptr2 = Product;
		while(ptr2 -> next_product != NULL)
		{
			if(ptr2 -> purchases < ptr2 -> next_product -> purchases)
			{
				sort = 0;
				temp -> purchases = ptr2 -> purchases;
				ptr2 -> purchases = ptr2 -> next_product -> purchases;
				ptr2 -> next_product -> purchases = temp -> purchases;
				temp -> availability = ptr2 -> availability;
				ptr2 -> availability = ptr2 -> next_product -> availability;
				ptr2 -> next_product -> availability = temp -> availability;
				temp -> price = ptr2 -> price;
				ptr2 -> price = ptr2 -> next_product -> price;
				ptr2 -> next_product -> price = temp -> price;
				strcpy(temp -> Model_name,ptr2 -> Model_name);
				strcpy(ptr2 -> Model_name,ptr2 -> next_product -> Model_name);
				strcpy(ptr2 -> next_product -> Model_name,temp -> Model_name);
			}
			ptr2 = ptr2 -> next_product;
		}
		ptr1 = ptr1 -> next_product;
	}
	return Product;
}
//sort customers
void sort_customers_on_frequency(Customer_type Customer[MAX])
{
	int i = 0,j,sort = 0;
	Customer_type temp;
	while(Customer[i].name[0] != '\0' && sort == 0)
	{
		j = 0;
		sort = 1;
		while(Customer[j + 1].name[0] != '\0')
		{
			if(Customer[j].number_of_items_bought < Customer[j + 1].number_of_items_bought)
			{
				sort = 0;
				temp = Customer[j];
				Customer[j] = Customer[j + 1];
				Customer[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
//Admin page
void AdminPage(Product_type *Product[6],Customer_type Customer[MAX])
{
	printf("You have logged in as an Admin");
	int x = 1,i;
	while(x <= 2 && x!= 3)
	{
		printf("Enter from the following:\n");
		printf("1.Print the list of customers who purchase more often\n");
		printf("2.Print the items purchased frequntly by customers\n");
		printf("3.Logout\n");
		scanf("%d",&x);
		switch(x)
		{
			case 1:
			{
				Customer_type temp_customer_array[MAX];
				for(i=0;i<MAX;i++)
				{
					temp_customer_array[i].number_of_items_bought = Customer[i].number_of_items_bought;
					temp_customer_array[i].name[0] = '\0';
					temp_customer_array[i].email[0] = '\0';
					temp_customer_array[i].paymentMode[0] = '\0';
					temp_customer_array[i].phone = 0;
					temp_customer_array[i].user_id = 0;
					temp_customer_array[i].wishlist = NULL;
					temp_customer_array[i].history = NULL;
				}
				for(i=0;i<MAX;i++)
				{
					strcpy(temp_customer_array[i].name,Customer[i].name);
					strcpy(temp_customer_array[i].email,Customer[i].email);
					strcpy(temp_customer_array[i].paymentMode,Customer[i].paymentMode);
					strcpy(temp_customer_array[i].address,Customer[i].address);
					temp_customer_array[i].phone = Customer[i].phone;
					temp_customer_array[i].user_id = Customer[i].user_id;
					temp_customer_array[i].wishlist = Customer[i].wishlist;
					temp_customer_array[i].history = Customer[i].history;
				}
				sort_customers_on_frequency(temp_customer_array);
				for(i=0;temp_customer_array[i].name[0] != '\0';i++)
				{
					printf("Number of items customer has broought:%d\n",temp_customer_array[i].number_of_items_bought);
					printf("Customer Name:%s\n",temp_customer_array[i].name);
					printf("Customer Address:%s\n",temp_customer_array[i].address);
					printf("Customer E-mail:%s\n",temp_customer_array[i].email);
					printf("Customer phone:%ld\n",temp_customer_array[i].phone);
					printf("Customer Payment Mode:%s\n",temp_customer_array[i].paymentMode);
					printf("\n\n");
				}
				break;
			}
			case 2:
			{
				for(i=0;i<6;i++)
				{
					Product[i] = sort_on_purchases(Product[i]);
				}
				int product_select,count = 1;
				printf("Choose the category from the following\n");
				printf("1.Mobile phones\n");
				printf("2.Mobile accessories\n");
				printf("3.Laptops,Computer accessories and Tablets\n");
				printf("4.Electronic gadgets\n");
				printf("5.Games and gaming consoles\n");
				printf("6.Home and Kitchen appliances\n");
				scanf("%d",&product_select);
				Product_type *temp_product = Product[product_select - 1];
				while(temp_product != NULL)
				{	
					printf("%d\n",count);
					count ++;
					printf("Category:%s\n",temp_product -> category);
					printf("Model name:%s\n",temp_product -> Model_name);
					printf("Price:%d\n",temp_product -> price);
					printf("Purchases:%d\n",temp_product -> purchases);
					printf("Availability:%d\n",temp_product -> availability);
					temp_product = temp_product -> next_product;
					printf("\n");
				}
				break;
			}
			case 3:
			{
				break;
			}
			default:
				printf("\nInvalid input\n");
		}
	}
}
int main()
{
	status_code retval;
	Product_type *Product[6],*temp_product;
	Customer_type Customer[MAX];
	Customer_Product_type *temp_customer_product;
	int i,last_index = 0,id;
	//Initialization
	for(i=0;i<6;i++)
	{
		Product[i] = NULL;
	}
	for(i=0;i<MAX;i++)
	{
		Customer[i].name[0] = '\0';
		Customer[i].email[0] = '\0';
		Customer[i].paymentMode[0] = '\0';
		Customer[i].phone = 0;
		Customer[i].number_of_items_bought = 0;
		Customer[i].amount = 0;
		Customer[i].user_id = 0;
		Customer[i].wishlist = NULL;
		Customer[i].history = NULL;
		Customer[i].favourites = NULL;
	}
	FILE * f=fopen("/home/ritu/Products.txt","r");
	char Model_name[50],category[50];
	int purchases,availability,price;
	while(!feof(f)){
		fscanf(f,"%s%s%d%d%d",category,Model_name,&purchases,&price,&availability);	
		int index = hashProduct(category);
		temp_product = (Product_type*)malloc(sizeof(Product_type));
		strcpy(temp_product -> Model_name,Model_name);
		strcpy(temp_product -> category,category);
		temp_product -> price = price;
		temp_product -> purchases = purchases;
		temp_product -> availability = availability;
		temp_product -> next_product = NULL;
		if(Product[index] == NULL)
		{
			Product[index] = temp_product;
		}
		else
		{
			temp_product -> next_product = Product[index];
			Product[index] = temp_product;
		}
	}
	free(temp_product);
	temp_product = NULL;
	fclose(f);
	//First customer
	//Customer details
	strcpy(Customer[0].name,"Harry James Potter");
	strcpy(Customer[0].email,"HarryPotter@hogwarts.wiz");
	strcpy(Customer[0].paymentMode,"Credit Card");
	strcpy(Customer[0].address,"Boys Dormitory,Gryffindore tower,Hogwarts school of Witchcraft and Wizardy");
	Customer[0].user_id = 001;
	Customer[0].phone = 9823647631;
	Customer[0].number_of_items_bought = 13;
	Customer[0].amount = 254000;
	//Customer's wishlist
	temp_product = (Product_type*)malloc(sizeof(Product_type));
	strcpy(temp_product -> Model_name,"Kent-Water-purifier");
	strcpy(temp_product -> category,"Home_and_kitchen_appliances");
	temp_product -> price = 7000;
	temp_product -> purchases = 10;
	temp_product -> availability = 8;
	temp_product -> next_product = NULL;
	Customer[0].wishlist = temp_product;
	temp_product = (Product_type*)malloc(sizeof(Product_type));
	strcpy(temp_product -> Model_name,"All-new-Echo-Dot-SmartSpeaker-with-Alexa");
	strcpy(temp_product -> category,"Electronic_gadgets");
	temp_product -> price = 4000;
	temp_product -> purchases = 25;
	temp_product -> availability = 10;
	temp_product -> next_product = Customer[0].wishlist;
	Customer[0].wishlist = temp_product;
	temp_product = (Product_type*)malloc(sizeof(Product_type));
	strcpy(temp_product -> Model_name,"Photron-P10-Wireless-3W-Portable-Bluetooth-Speaker(DeepCobalt)");
	strcpy(temp_product -> category,"Electronic_gadgets");
	temp_product -> price = 600;
	temp_product -> purchases = 20;
	temp_product -> availability = 15;
	temp_product -> next_product = Customer[0].wishlist;
	Customer[0].wishlist = temp_product;
	//Customer's history
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"All-new-Echo-Dot-SmartSpeaker-with-Alexa");
	strcpy(temp_customer_product -> category,"Electronic_gadgets");
	temp_customer_product -> price = 4000;
	temp_customer_product -> quantity = 2;
	temp_customer_product -> next_product = NULL;
	Customer[0].history = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"iBall-Wireless-mouse");
	strcpy(temp_customer_product -> category,"Laptops,Computer_accessories_and_tablets");
	temp_customer_product -> price = 1000;
	temp_customer_product -> quantity = 4;
	temp_customer_product -> next_product = Customer[0].history;
	Customer[0].history = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"Apple-iPad");
	strcpy(temp_customer_product -> category,"Laptops,Computer_accessories_and_tablets");
	temp_customer_product -> price = 26000;
	temp_customer_product -> quantity = 1;
	temp_customer_product -> next_product = Customer[0].history;
	Customer[0].history = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"Microsoft-Lumia-L2");
	strcpy(temp_customer_product -> category,"Mobile_phones");
	temp_customer_product -> price = 36000;
	temp_customer_product -> quantity = 6;
	temp_customer_product -> next_product = Customer[0].history;
	Customer[0].history = temp_customer_product;
	//Customer's favourites
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"Apple-iPad");
	strcpy(temp_customer_product -> category,"Laptops,Computer_accessories_and_tablets");
	temp_customer_product -> price = 26000;
	temp_customer_product -> quantity= 1;
	temp_customer_product -> next_product = NULL;
	Customer[0].favourites = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"All-new-Echo-Dot-SmartSpeaker-with-Alexa");
	strcpy(temp_customer_product -> category,"Electronic_gadgets");
	temp_customer_product -> price = 4000;
	temp_customer_product -> quantity = 2;
	temp_customer_product -> next_product = Customer[0].favourites;
	Customer[0].favourites = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"iBall-Wireless-mouse");
	strcpy(temp_customer_product -> category,"Laptops,Computer_accessories_and_tablets");
	temp_customer_product -> price = 1000;
	temp_customer_product -> quantity = 4;
	temp_customer_product -> next_product = Customer[0].favourites;
	Customer[0].favourites = temp_customer_product;
	temp_customer_product = (Customer_Product_type*)malloc(sizeof(Customer_Product_type));
	strcpy(temp_customer_product -> Model_name,"Microsoft-Lumia-L2");
	strcpy(temp_customer_product -> category,"Mobile_phones");
	temp_customer_product -> price = 36000;
	temp_customer_product -> quantity = 6;
	temp_customer_product -> next_product = Customer[0].favourites;
	Customer[0].favourites = temp_customer_product;
	last_index ++;
	system("clear");
	int input = 1;
	while(input != 0)
	{
		
		printf("Choose form the following:\n\n");
		printf("1.Login as Customer\n");
		printf("2.Register\n");
		printf("3.Login as Admin\n");
		printf("\n\n4.Enter 0 to escape\n\n");
		scanf("%d",&input);
		if(input == 1)
		{
			retval = Login(Customer,&id);
			if(retval == SUCCESS)
			{
				system("clear");
				UserPage(id,Product,Customer);
				system("clear");
				printf("You have logged out successfully\n");
			}
			else
			{
				printf("\nLogin failed\n\n");	
			}
		}
		else if(input == 2)
		{
			retval = Register(Customer,&last_index);
			if(retval == SUCCESS)
				printf("You have successfully registered\n");
			else
				printf("Registration unsuccessful\n");
		}
		else if(input == 3)
		{
			printf("Enter email:");
			char email[200],password[20];
			scanf("\n");
			scanf("%[^\n]s",email);
			printf("Enter password:");
			scanf("\n");
			scanf("%[^\n]s",password);
			if((strcmp(email,"renitath99@gmail.com") == 0)&&(strcmp(password,"RituThombre") == 0))
			{
				system("clear");
				AdminPage(Product,Customer);
				system("clear");
				printf("You have logged out successfully\n");
			}
			else
			{
				printf("\nEnter valid email and password\n");
			}
		}
		else
		{
			printf("Invalid input\n\n");
		}
	}	
	return 0;
}

