
#include "Orders.h"
#include "Structs.h"
#include "Cart.h"
#define MAX

void Create_Order(char* username)
{
	FILE* Orders;
	FILE* carts_file;
	FILE* fpointerU;
	Cart cart;
	Order order;
	Product orderp;
	

	Orders = fopen(ORDERS_FILENAME, "r+");
	if (Orders == NULL)
	{
		fprintf(stderr, "\n Error open orders");
		exit(1);
	}
	carts_file = fopen(CARTS_FILENAME, "r+"); // open file with carts 
	if (carts_file == NULL)
	{
		fprintf(stderr, "\n Error open orders");
		exit(1);
	}
	fpointerU = fopen(USERS_FILENAME, "r+");
	if (fpointerU == NULL)
	{
		fprintf(stderr, "\n Error open orders");
		exit(1);
	}

	fread(&cart, sizeof(Cart), 1, carts_file); //copy to cart all the data from cart file

	while (fread(&cart, sizeof(Cart), 1, fpointerU)) {
		{
			if (!strcmp(cart.userName, username))
				break;
		}
	}
	
	strcpy(order.userName , cart.userName);
	for (int i = 0; i < cart.productCounter; i++) //copy the products from cart to the order
	{
		strcpy(order.cart_list[i].productName, cart.productsInCart[i].productName);
		order.cart_list[i].productPrice = cart.productsInCart[i].productPrice;
		order.cart_list[i].product_category = cart.productsInCart[i].product_category;
		order.cart_list[i].quantity = cart.productsInCart[i].quantity;
		order.cart_list[i].serialNumber = cart.productsInCart[i].serialNumber;

	}
	char name[MAX_SIZE];
	int num_check=0;
	printf("Enter full name:\n");
	gets(order.customer_full_name);
	printf("Enter id with 10 digits only:\n");
	scanf_s("%d", &num_check);

	while (check_validation(num_check)==FALSE)
	{
		printf("wrong id please try again with 10 digits only:\n");
		scanf("%d", &num_check);
		getchar();
	}
	order.customer_id = num_check;
	
	printf("Enter credit card with 10 digits only:\n");
	scanf_s("%d", &num_check);
	while (check_validation(num_check) == FALSE)
	{
		printf("wrong credit card please try again with 10 digits only:\n");
		scanf("%d", &num_check);
		getchar();
	}
	order.customer_credit_card = num_check;
	printf("Enter address:\n");
	scanf("%s", name);
	strcpy(order.customer_address, name);
	getchar();

	
	printf("Enter phone number with 10 digits only with 10 digits only:\n");
	scanf_s("%d", &num_check);

	while (check_validation(num_check) == FALSE)
	{
		printf("wrong phone number please try again with 10 digits only:\n");
		scanf_s("%d", &num_check);
		getchar();

	}
	order.phoneNumber = num_check;
	
	for (int i = 0; i < cart.productCounter; i++)
	{
		order.orderPrice += cart.productsInCart[i].productPrice;

	}
	order.status = APPENDING;
	fwrite(&order, sizeof(Order), 1, Orders);

	fclose(Orders);
	fclose(carts_file);
	fclose(fpointerU);
}




 void change_order_status(char* username)
{
	 User user;
	 Order order;
	 FILE* fpointerU;
	 FILE* fpointerO;
	 int choice=2;
	 fpointerU = fopen(USERS_FILENAME, "r+"); //open users file
	 if (fpointerU == NULL) {
		 fprintf(stderr, "\nERROR OPENING FILE\n");
		 exit(1);
	 }
	 fpointerO = fopen(ORDERS_FILENAME, "r+"); // open orders file
	 if (fpointerO == NULL) {
		 fprintf(stderr, "\nERROR OPENING FILE\n");
		 exit(1);
	 }
	 fread(&order, sizeof(Order), 1, fpointerO);

	 while (fread(&user, sizeof(User), 1, fpointerU)) { //searching the user that we want on data base
		 {
			 if (!strcmp(user.userName, username))
				 break;
		 }
	 }
	 while (fread(&order, sizeof(Order), 1, fpointerU)) {//Find the order by user name 
		 {
			 if (!strcmp(order.userName, username))
				 break;
		 }
	 }
	 if (order.status == APPENDING) //if the order still appending
	 {
		 if (user.userType == MANAGER) // if the user is manager
		 {

			 printf("Would you like to cancel or approve the order\nPress 1 to approve or 2 to cancel\n");
			 scanf("%d", &choice);
			 while (choice != 1 || choice != 2)
			 {
				 if (choice == 1)
				 {
					 order.status = APPROVED;
					 break;
				 }
				 if (choice == 2)
				 {
					 order.status = CANCELD;
					 break;
				 }

				 else
					 printf("You entered wrong answer, please try again\n");

			 }






		 }

		 else
		 {
			 
			 while (choice != 1 || choice != 2)
			 {
				 printf("Would you like to cancel your order?\nPress 1 for yes or 2 for no\n");
				 scanf("%d", &choice);

				 if (choice == 1) {
					 order.status = CANCELD;
					 break;
				 }

				 if (choice == 2)
					 break;
				 
				 else
					 printf("You entered wrong answer, please try again\n");

			 }


		 }
	 }
	  else
		 printf("there is no appending order\n");


	 fclose(fpointerO);
	 fclose(fpointerU);
}

 enum Bool check_validation(unsigned long long num)
 {
	 int counter = 1;
	 while (num / 10 != 0)
	 {
		 num /= 10;
		 counter++;
	 }
	 if (counter == 10)
		 return TRUE;
	 return	FALSE;
 }



 void print_order_details(Order* order)
 {
 }
