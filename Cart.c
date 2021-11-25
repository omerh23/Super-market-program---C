#include "Cart.h"

void printCartInfo(Cart cart)
{
	//printf("\nProducts List:\n");
	//printf("----------------\n");
	//for (int i = 0; i < cart.productCounter; i++)
	//	printProduct(cart.productsInCart[i]);

	printf("             *****  MY CART ***** \n");
	printf("---------------------------------------------------------------- - \n");
	printf("S.N.|    NAME           |  QUANTITY |  PRICE| CATEGORY \n");
	printf("----------------------------------------------------------------- - \n");
	for (int i = 0; i < cart.productCounter; i++) {
		printf(" %d     %-15s        %-5d     %-5.2lf", cart.productsInCart[i].serialNumber, cart.productsInCart[i].productName, cart.productsInCart[i].quantity,
			cart.productsInCart[i].productPrice);
		switch (cart.productsInCart[i].product_category)
		{
		case 0:
			puts("  Fruits");
			break;
		case 1:
			puts("  Vegetables");
			break;
		case 2:
			puts("  Drinks");
			break;
		case 3:
			puts("  Meat");
			break;
		case 4:
			puts("  Farm");
			break;
		default:
			puts("  ERROR");
			break;
		}
	}
	printf("----------------------------------------------------------------- - \n");
}

void addProductToCart(char* userName, int productSerialNumber, int quantity)
{
	FILE* fpointer = fopen(CARTS_FILENAME, "r+");
	if (fpointer == NULL) {
		fprintf(stderr, "\nERROR OPENING FILE\n");
		exit(1);
	}
	Cart temp;
	while (fread(&temp, sizeof(Cart), 1, fpointer)){//Find the cart by user name and read the cart to temp parameter.
		if (!strcmp(temp.userName, userName))
			break;
	}


	/*if the product is already exist it the cart*/
	for(int i=0;i<temp.productCounter;i++)
		if (temp.productsInCart[i].serialNumber == productSerialNumber) {//in case the product already contain in the cart
			temp.productsInCart[i].quantity += quantity;//Adds the quantity to the existing product in the cart
			fseek(fpointer, -(int)sizeof(Cart), SEEK_CUR);// jump back one Cart
			fwrite(&temp, sizeof(Cart), 1, fpointer);//rewrite the cart with the new product included
			fclose(fpointer);
			changeProductQuantity(productSerialNumber, ADD, -quantity);//Updates the quantity in stock
			return;
		}

	/*if the product not exist in cart: checking if there is free space in cart and add the product*/
	if (temp.productCounter < MAX_Products_In_Cart) {//Check if the cart is full.
		temp.productsInCart[temp.productCounter] = getProductBySerial(productSerialNumber);//adds the product to cart(copy product from the inventory)
		temp.productsInCart[temp.productCounter].quantity = quantity;//update the quantity in cart
		temp.productCounter++;
		fseek(fpointer, -(int)sizeof(Cart), SEEK_CUR);// jump back one Cart
		fwrite(&temp, sizeof(Cart), 1, fpointer);//rewrite the cart with the new product included
		fclose(fpointer);
		changeProductQuantity(productSerialNumber, ADD, -quantity);//Updates the quantity in stock
	}
	else{
		printf("\nThe cart is full.\n");
	}

}

void remove_Product_From_Cart(char* userName, int serialNumber)
{
	Cart temp,temp2;
	FILE* fpointer = fopen(CARTS_FILENAME, "r+");
	if (fpointer == NULL) {
		fprintf(stderr, "\nERROR OPENING FILE\n");
		exit(1);
	}
	while (fread(&temp, sizeof(Cart), 1, fpointer)) {//Find the cart by user name and read the cart to temp parameter.
		if (!strcmp(temp.userName, userName))
			break;
	}
	strcpy(temp2.userName, temp.userName);//copy user name 
	temp2.productCounter = 0;
	/*copy all product one by one, and skip the product we want to remove*/
	for (int i = 0; i < temp.productCounter; i++) {
		if (!(temp.productsInCart[i].serialNumber == serialNumber)) {
			temp2.productsInCart[temp2.productCounter] = temp.productsInCart[i];
			temp2.productCounter++;
		}
	}

	fseek(fpointer, -(int)sizeof(Cart), SEEK_CUR);
	fwrite(&temp2, sizeof(Cart), 1, fpointer);
	fclose(fpointer);
}

void remove_Product_From_All_Carts(int serialNumber)
{
	User temp;

	FILE* fpointer = fopen(USERS_FILENAME, "r");
	if (fpointer == NULL) {
		fprintf(stderr, "\nERROR OPENING FILE\n");
		exit(1);
	}
	while (fread(&temp, sizeof(User), 1, fpointer))
		remove_Product_From_Cart(temp.userName, serialNumber);
	fclose(fpointer);
}

Cart getCartByUser(char* user_name)
{
	FILE* fpointer = fopen(CARTS_FILENAME, "r");
	if (fpointer == NULL) {
		fprintf(stderr, "\nERROR OPENING FILE\n");
		exit(1);
	}
	Cart temp;
	while (fread(&temp, sizeof(Cart), 1, fpointer)){
		if (!strcmp(temp.userName, user_name)) {
			fclose(fpointer);
			return temp;
		}
	}
}

enum Bool empty_the_cart(User userName)
{
	//FILE* fpointer = fopen(USERS_FILENAME, "r");
	//return TRUE;
}
