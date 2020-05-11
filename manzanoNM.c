/************************************************************************************
	This is to certify that this project is my own work, based on my personal efforts 
	in studying and applying the concepts learned. I have constructed the functions 
	and their respective algorithms and corresponding code by myself. The program was 
	run, tested, and debugged by my own efforts. I further certify that I have not 
	copied in part or whole or otherwise plagiarized the work of other students 
	and/or persons.
	
										Ninna Robyn M. Manzano, DLSU ID# 11836814
************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_USER 	100
#define MAX_ITEM 	20

typedef char string10[11];
typedef char string15[16];
typedef char string20[21];
typedef char string30[31];

typedef struct {
	int year,
		month,
		day;
} structDateType;

typedef struct {
	int 		productID;
	string20 	itemName;
	string15 	category;
	string30 	item_descript;
	int 		quantity;
	float 		price;
	int 		sellerID;
} structItemType;

typedef struct {
	int 	 userID;
	string10 password;
	string30 address;
	double contactNo;
	string20 name;
} structUserType;

typedef structItemType arrTransac[5];

typedef struct {
	structDateType 	date;
	arrTransac	 	itemList;
	int 			buyerID,
					sellerID;
	float 			totalAmount;
} structTransacType;

typedef structUserType arrUsers[MAX_USER];
typedef structItemType arrItems[MAX_USER*MAX_ITEM];
typedef	structItemType arrCart[10];

/** This function reads and loads all User information from a file "Users.txt"
*/
void loadUsers(arrUsers aUsers, int *pUsers)
{
	FILE *fp;
	char dump;
	
	if ((fp = fopen("Users.txt", "r")) != NULL) {
		*pUsers = 0;
		
		while ( fscanf(fp, "%d%c%s%c", &aUsers[*pUsers].userID, &dump, 
									   aUsers[*pUsers].password, &dump ) == 4 ) 
		{
			fgets(aUsers[*pUsers].name, 21, fp);
			aUsers[*pUsers].name[ strlen(aUsers[*pUsers].name)-1 ] = '\0';
			fgets(aUsers[*pUsers].address, 31, fp);
			aUsers[*pUsers].address[ strlen(aUsers[*pUsers].address)-1 ] = '\0';
			fscanf(fp, "%lf%c", &aUsers[*pUsers].contactNo, &dump);
			(*pUsers)++;
		}
		
		fclose(fp);	
	} else printf("   File is not available for reading.\n");
}

/** This function saves all added User information to a file "Users.txt"
*/
void saveUsers(arrUsers aUsers, int nUsers) 
{
	FILE *fp;
	int  i;
	
	if( (fp = fopen("Users.txt", "w")) != NULL )
	{
		for (i = 0; i < nUsers; i++) {
			fprintf(fp, "%d %s\n", aUsers[i].userID, aUsers[i].password);
			fprintf(fp, "%s\n%s\n%.0lf\n\n", aUsers[i].name, aUsers[i].address, (double) aUsers[i].contactNo);
		}
	fclose(fp);	
	}
	else printf("   Error opening file for writing\n");
}

/** This function loads all item information from a file "Items.txt"
*/
void loadItems(arrItems aItems, int *pItems)
{
	FILE *fp;
	char dump;
	
	if ((fp = fopen("Items.txt", "r")) != NULL) {
		*pItems = 0;
		
		while ( fscanf(fp, "%d%c%d%c", &aItems[*pItems].productID, &dump, 
									   &aItems[*pItems].sellerID, &dump ) == 4 ) 
		{
			fgets(aItems[*pItems].itemName, 21, fp);
			aItems[*pItems].itemName[ strlen(aItems[*pItems].itemName)-1 ] = '\0';
			
			fgets(aItems[*pItems].category, 16, fp);
			aItems[*pItems].category[ strlen(aItems[*pItems].category)-1 ] = '\0';
			
			fgets(aItems[*pItems].item_descript, 31, fp);
			aItems[*pItems].item_descript[ strlen(aItems[*pItems].item_descript)-1 ] = '\0';			
			
			fscanf(fp, "%d%c%f%c", &aItems[*pItems].quantity, &dump, &aItems[*pItems].price, &dump);
			(*pItems)++;
		}
		fclose(fp);	
	} else printf("   File is not available for reading.\n");
}

/** This function saves all added item information in a file "Items.txt"
*/
void saveItems(arrItems aItems, int nItems) 
{
	FILE *fp;
	int  i;
	
	if( (fp = fopen("Items.txt", "w")) != NULL )
	{
		for (i = 0; i < nItems; i++) {
			fprintf(fp, "%d %d\n", aItems[i].productID, aItems[i].sellerID);
			fprintf(fp, "%s\n%s\n%s\n", aItems[i].itemName, aItems[i].category, aItems[i].item_descript);
			fprintf(fp, "%d %.2f\n\n", aItems[i].quantity, aItems[i].price);
		}
	fclose(fp);	
	}
	else printf("Error opening file for writing\n");
}

/** This function checks if userID is unique by searching inputted
	user ID in the array of user IDs.
*/
int checkUser(arrUsers aUsers, int tempID, int *pUsers){
	int i;
	
	for(i = 0; i < *pUsers; i++)
		if (tempID == aUsers[i].userID){
			printf("\tUserID already exists!\n");
			return 0;
		}
		else if( tempID < 0 || tempID == 0){
			printf("\tInvalid user ID input!\n");
			return 0;		
		}
	return 1;
}

/** This function permits the user to register if the checked inputted user ID is unique 
	then stores inputted user information to the array of Users.
*/
void registerUser(arrUsers aUsers, int *pUsers)
{
	char dump;
	int tempID;
	
	printf("   Enter user ID: ");
	scanf("%d%c", &tempID, &dump);

	if (checkUser(aUsers, tempID, pUsers)) {
		aUsers[*pUsers].userID = tempID;
		
		printf("Enter password (max. 10 characters): ");
			fgets(aUsers[*pUsers].password, 11, stdin);
			aUsers[*pUsers].password[ strlen(aUsers[*pUsers].password) - 1] = '\0';
		
		printf("Enter address (max. 30 characters): ");
			fgets(aUsers[*pUsers].address, 31, stdin);
			aUsers[*pUsers].address[ strlen(aUsers[*pUsers].address) - 1] = '\0';
			
		printf("Enter contact number: ");
			scanf("%lf%c", &aUsers[*pUsers].contactNo, &dump);
		
		printf("Enter name (max. 20 characters): ");
			fgets(aUsers[*pUsers].name, 21, stdin);
			aUsers[*pUsers].name[ strlen(aUsers[*pUsers].name) - 1] = '\0';
			(*pUsers)++;
	} 	
}


/** This function checks if inputted userID and password matches any registered
	users then gets matched user ID and its index for accessing in the latter 
	functions. If not, the user is redirected back to the main menu.
*/
int userLogin(arrUsers aUsers, int *pUsers, int *userID, int *logIndex)
{
	char dump;
	int i;
	structUserType temp;
	
	printf("\n   [USER Log-in]\n");
	printf("\tEnter userID: ");
	scanf("%d%c", &temp.userID, &dump);
	
	printf("\tEnter password: ");
	fgets(temp.password, 11, stdin);
	temp.password[ strlen(temp.password) - 1] = '\0';
		
	for (i = 0; i < (*pUsers); i++) // checking for valid user
		if ( (temp.userID == aUsers[i].userID) && strcmp( temp.password, aUsers[i].password ) == 0 ) {
			*userID = temp.userID;
			*logIndex = i;
			return 1;
		}
	return 0;
}

/** This function checks if productID is unique (regardless of the seller).
	
	return 0 - not unique product ID
	return 1 - unique product ID
*/
int checkProductID(arrItems aItems, int *pItems, int tempProdID){
	int i;
	for (i = 0; i < (*pItems); i++)
		if (tempProdID == aItems[i].productID || tempProdID < 0 || tempProdID == 0){			
			return 0;
		}
	return 1;
}

/** This function searches for the inputted product ID in the existing array of
	product IDs.
	
	return 0 - no matching product ID
	return 1 - there is a matching product ID
*/
int findProductID(arrItems aItems, int *pItems, int tempProdID, int *prodIndex)
{
	int i;
	for (i = 0; i < (*pItems); i++)
		if (tempProdID == aItems[i].productID){
			*prodIndex = i;
			return 1;
		}
	return 0;
}


/** This function sorts product information in increasing order according to
	product ID.
*/
void sortProductID(arrItems aItems, int *pItems)
{
	int i, j;
	structItemType temp;
	
	for (i = 0; i < *pItems-1; i++){
		for (j = i+1; j < *pItems; j++){
			if ( aItems[i].productID > aItems[j].productID ) { //checking for larger product ID
				temp = aItems[j];
				aItems[j] = aItems[i];
				aItems[i] = temp;		
			}
		}
	}
}

/** This function checks if the seller has reached the maximum 20
	number of items.
	
	return 1 - seller has reached limit
	return 0 - has not reached the limit
*/
int checkSellerItemLimit(arrItems aItems, int *pItems, int sellID)
{
	int i;
	int itemsCtr = 0;
	
	for(i = 0; i < (*pItems); i++){
		if (aItems[i].sellerID == sellID)
			itemsCtr++;
		
		if(itemsCtr >= 20)
			return 1;
	}
	return 0;	
}

/** This function lets the user add a new item to sell. Information for the item (except the sellerID)
	is asked from the user namely the productID, item name, category, item description, and price.
	
	sellerID - placeholder for userID of logged in User
*/
void addNewItem(arrItems aItems, int *pItems, int sellerID) 
{
	int tempProdID;
	char dump;

	aItems[*pItems].sellerID = sellerID; //copies the userID as the sellerID
	printf("   sellerID saved.\n"); 	
	
	if(!checkSellerItemLimit(aItems, pItems, sellerID)) {
		do {
			printf("   Enter product ID: ");
			scanf("%d%c", &tempProdID, &dump);
			
			if (!checkProductID(aItems, pItems, tempProdID)) 
				printf("   There is an existing product ID!\n");
				
		} while (!checkProductID(aItems, pItems, tempProdID)); // runs when checkProductID returns 1
		
		aItems[*pItems].productID = tempProdID; 
		
		printf("   Enter item name (max. 20): ");
			fgets(aItems[*pItems].itemName, 21, stdin);
			aItems[*pItems].itemName[ strlen(aItems[*pItems].itemName) - 1] = '\0';
		
		printf("   Enter category (max. 15): ");
			fgets(aItems[*pItems].category, 16, stdin);
			aItems[*pItems].category[ strlen(aItems[*pItems].category) - 1] = '\0';
			
		printf("   Enter item description (max. 30): ");
			fgets(aItems[*pItems].item_descript, 31, stdin);
			aItems[*pItems].item_descript[ strlen(aItems[*pItems].item_descript) - 1] = '\0';
		
		printf("   Enter quantity: ");
			scanf("%d%c", &aItems[*pItems].quantity, &dump);
			
		printf("   Enter price: ");
			scanf("%f%c", &aItems[*pItems].price, &dump);
			
		(*pItems)++;
	} else printf("   Seller has reached max. number of items!\n");
}

/** This function sorts array of Items in increasing order based on the productID.
	It then shows all information of the products in the following table format: 
	productID, item name, category, unit price, quantity. 
*/
void showMyProducts(arrItems aItems, int *pItems, int *sellerID)
{	
	int i;
	sortProductID(aItems, pItems); 
	
	printf("   ============================================================================================================================\n");
	printf("   |	Product ID  |	    Item Name	    |	   Category    |	Item Description       |  Unit Price  |	   Quantity   |\n");
	printf("   ============================================================================================================================\n");

	for (i = 0; i < *pItems; i++)
		if ( aItems[i].sellerID == *sellerID )
				printf("   | %15d| %-22s| %-17s| %-30s| %13.2f| %14d|\n", aItems[i].productID, aItems[i].itemName, 
					aItems[i].category, aItems[i].item_descript, aItems[i].price, aItems[i].quantity);
	printf("   ----------------------------------------------------------------------------------------------------------------------------\n");
}

/** This function shows all of seller's products in table format by calling showMyProducts().
	Then if productID is valid, asks for product ID whose information is to be edited and offers 
	the submenus (Replenish, Change Price..) until the user chooses to finish editing. If not, 
	it redirects user back to Sell Menu.
*/
void editStock(arrItems aItems, int *pItems, int *sellerID)
{
	int option4 = 1;
	char dump;
	structItemType add;
	int i, tempProdID, prodIndex = -1;
	
	/*sorts the product IDs first before displaying all of seller's products in table format*/
	sortProductID(aItems, pItems); 
	showMyProducts(aItems, pItems, sellerID); 
	
	printf("\n   Enter product ID: ");
	scanf("%d%c", &tempProdID, &dump);
	
	for (i = 0; i < (*pItems); i++)
		if (tempProdID == aItems[i].productID)
			prodIndex = i;
	if (prodIndex == -1 || tempProdID == 0 || tempProdID < 0)
		printf("   --Invalid product ID.\n");
	else {
		while (option4 != 0) {
			printf("\n   Select from /Edit Stock/ options\n");
			printf("\t1: Replenish\n\t2: Change Price\n\t3: Change Item Name\n\t4: Change Category\n");
			printf("\t5: Change Description\n\t0: Finish Editing\n");
			scanf("%d%c", &option4, &dump);
			
			switch(option4) { //2.1.2.1 Replenish
				case 1: {
					printf("\t2.1.2.1 Replenish\n");
					printf("Enter quantity to add for this //item//: ");
					scanf("%d%c", &add.quantity, &dump);	
					aItems[prodIndex].quantity += add.quantity;
					break;
				}
				case 2: { //2.1.2.2 Change Price
					printf("\t2.1.2.2 Change Price\n");
					printf("Enter new price: ");
					scanf("%f%c", &aItems[prodIndex].price, &dump);
					break;
				}
				case 3: { //2.1.2.3 Change Item Name
					printf("\t2.1.2.3 Change Item Name\n");
					printf("Enter new item name: ");
					fgets(aItems[prodIndex].itemName, 21, stdin);
					aItems[prodIndex].itemName[ strlen(aItems[prodIndex].itemName)-1 ] = '\0';
					break;
				}
				case 4: { //2.1.2.4 Change Category
					printf("\t2.1.2.4 Change Category\n");
					printf("Enter new category: ");
					fgets(aItems[prodIndex].category, 16, stdin);
					aItems[prodIndex].category[ strlen(aItems[prodIndex].category)-1 ] = '\0';
					break;
				}
				case 5: { //2.1.2.5 Change Description
					printf("\t2.1.2.5 Change Description\n");
					printf("Existing description: %s\n", aItems[prodIndex].item_descript);
					printf("Enter new description: ");
					fgets(aItems[prodIndex].item_descript, 31, stdin);
					aItems[prodIndex].item_descript[ strlen(aItems[prodIndex].item_descript)-1 ] = '\0';
					break;
				}
				case 0: { //2.1.2.6 Finish Editing
					printf("\t<..Redirecting back to Sell Menu..>\n");
					break;
				}
			}
		}
	}

}

/** This function shows all the information (including product description) but excluding 
	seller's userID) about each product whose quantity is below 5. It displays information 
	one at a time per product. wherein it allows the user to press N to see the next 
	product with low stocks and press X to exit the view.
*/
void showLowStocks(arrItems aItems, int *pItems, int *sellerID)
{
	int i;
	char key = 'N';
	int noneCount = 0;
	
	printf("    Press [N] for Next, [X] to Exit\n");
	printf("   ============================================================================================================================\n");
	printf("   |	Product ID  |	    Item Name	    |	   Category    |	Item Description       |  Unit Price  |	   Quantity   |\n");
	printf("   ============================================================================================================================\n");
	for (i = 0; i < *pItems; i++) {
		if ( aItems[i].sellerID == *sellerID )
			if( aItems[i].quantity < 5 && (key == 'N')) {
				printf("   | %15d| %-22s| %-17s| %-30s| %13.2f| %14d|\n", aItems[i].productID, aItems[i].itemName, 
					aItems[i].category, aItems[i].item_descript, aItems[i].price, aItems[i].quantity);
				do {
					key = getch();
				} while ((key != 'x') && (key != 'N'));
			}
			if( aItems[i].quantity == 0) {
				noneCount++; // counts items with 0 stocks.
			}		
	}
	printf("   ----------------------------------------------------------------------------------------------------------------------------\n");
	
	if(noneCount > 0){ //displays items with no stocks
		for (i = 0; i < noneCount; i++)
			if(aItems[i].quantity == 0){
				printf("   Items with no stocks: \n");
				printf("     '%s'\n", aItems[i].itemName);
			}
	printf("   Go to [EDIT STOCK] to change item/s with no stocks.\n");
	}
}


/** This function sorts array of items in increasing order based on seller ID.
*/
void sortSellerID(arrItems aItems, int nItems)
{
	int i, j;
	structItemType temp;
	
	for(i = 0; i < nItems-1; i++)
		for(j = i+1; j < nItems; j++)
			if( aItems[i].sellerID > aItems[j].sellerID ){
				temp = aItems[j];
				aItems[j] = aItems[i];
				aItems[i] = temp;
			}
}

void showProductsBySeller(arrItems aItems, int *pItems, int sellerID);

/** This function displays all items from 1 seller at a time, sorted in increasing order based on 
	seller ID. Seller ID is shown first, then followed by a table of the products of that seller. 
	When the user presses N, the next seller ID is shown and under it, the table of products of 
	that seller, and so on. The user can press X to exit this view and go back to the Buy Menu.
*/
int viewAllProducts(arrUsers aUsers, int nUsers, arrItems aItems, int nItems)
{
	int i, j;
	char key = 'N';
	int sellerID, prodItem = 0;
	sortSellerID(aItems, nItems);
	
	printf("    Press [N] for Next, [X] to Exit\n");
	
	for(i = 0; i < nUsers; i++) {
		sellerID = aUsers[i].userID;
		prodItem = 0;
		for(j = 0; j < nItems; j++) {
			if (sellerID == aItems[j].sellerID)
				prodItem++;
		}
		printf("\n   Seller ID: %d\n", sellerID);
		if (prodItem > 0) {
			if ((key != 'X' && key != 'x')){
				printf("   ============================================================================================\n");
				printf("   |	Product ID  |	    Item Name	    |	   Category    |  Unit Price  |	   Quantity   |\n");
				printf("   ============================================================================================\n");
				for(j = 0; j < nItems; j++)
					if ((sellerID == aItems[j].sellerID) && (key == 'N' || key == 'n')){
							printf("   | %15d| %-22s| %-17s| %13.2f| %14d|\n", aItems[j].productID, aItems[j].itemName, 
								aItems[j].category, aItems[j].price, aItems[j].quantity);
					}
				printf("   --------------------------------------------------------------------------------------------\n");
				do {
					key = getch();
				} while ((key != 'x' && key != 'X') && (key != 'N' && key != 'n'));	
			}
		}
		else if(prodItem == 0)
			printf("   This user is not selling any items.\n");
	}
	return 0;
}

/** This function searches if inputted seller ID matches with an existing sellerID. Then, 
	the program displays the seller’s ID and below it the table of that seller’s products.
*/
void showProductsBySeller(arrItems aItems, int *pItems, int sellerID)
{
	int i, j;
	
	int prodItem = 0;
	sortSellerID(aItems, *pItems);

	for(i = 0; i < *pItems; i++) {
		prodItem = 0;
		for(j = 0; j < *pItems; j++) {
			if (sellerID == aItems[j].sellerID)
				prodItem++;
		}
	}
	printf("\n   Seller ID: %d\n", sellerID);
	if (prodItem > 0) {
			printf("   ============================================================================================\n");
			printf("   |	Product ID  |	    Item Name	    |	   Category    |  Unit Price  |	   Quantity   |\n");
			printf("   ============================================================================================\n");
			for (i = 0; i < *pItems; i++){
				if ( sellerID == aItems[i].sellerID ){
					printf("   | %15d| %-22s| %-17s| %13.2f| %14d|\n", aItems[i].productID, aItems[i].itemName, 
						aItems[i].category, aItems[i].price, aItems[i].quantity);
				}
			}
			printf("   --------------------------------------------------------------------------------------------\n");
	}
	else if(prodItem == 0)
		printf("   This user is not selling any items.\n");
}

/** This function asks the user to input the category to search for. It then displays the number of items
	found in the search then displays those products matching the given category in table format similar 
	to Show Low Stocks. It also allows the user type N and X to navigate through the display.
*/
void searchProductsByCategory(arrItems aItems, int *pItems)
{
	int i;
	char key = 'N';
	string15 tempCateg;
	int categItems = 0;
	
	printf("    Enter the 'category' to search for: ");
	fgets(tempCateg, 16, stdin);
	tempCateg[strlen(tempCateg)-1] = '\0';
		
	for(i = 0; i < (*pItems); i++) //counts no. of items found in that category
		if( strcmp(tempCateg, aItems[i].category) == 0)
			categItems++;
	printf("\n    %d items found.\n", categItems);
	
	if(categItems > 0) {
		printf("    Press [N] for Next, [X] to Exit\n");
		printf("   ============================================================================================\n");
		printf("   |	Product ID  |	    Item Name	    |	   Category    |  Unit Price  |	   Quantity   |\n");
		printf("   ============================================================================================\n");
		
		for(i = 0; i < (*pItems); i++)
			if( strcmp(tempCateg, aItems[i].category) == 0)
					if (key == 'N' || key == 'n'){
						printf("   | %15d| %-22s| %-17s| %13.2f| %14d|\n", aItems[i].productID, aItems[i].itemName, 
							aItems[i].category, aItems[i].price, aItems[i].quantity);
						do {
							key = getch();
						} while ((key != 'x' && key != 'X') && (key != 'N' && key != 'n'));
					}
		printf("   --------------------------------------------------------------------------------------------\n");
	}
}

/** This function asks the user to input keywords of the product (substring) to search for. It then 
	displays number of items found in the search followed by a table format that is similar with 
	Show Low Stocks. It also allows the user type N and X to navigate through the display.	
*/
void searchProductsByName(arrItems aItems, int *pItems)
{
	int i;
	char key = 'N';
	string20 tempItemName;
	int foundItem = 0;
	
	printf("    Enter the 'product name' to search for: ");
	fgets(tempItemName, 21, stdin);
	tempItemName[strlen(tempItemName)-1] = '\0';
		
	for(i = 0; i < (*pItems); i++) //counts no. of items found in that category
		if( strstr(aItems[i].itemName, tempItemName) != NULL)
			foundItem++;
			
	printf("\n    %d items found.\n", foundItem);
	
	if (foundItem > 0) {
		printf("    Press [N] for Next, [X] to Exit\n");
		printf("   ============================================================================================\n");
		printf("   |	Product ID  |	    Item Name	    |	   Category    |  Unit Price  |	   Quantity   |\n");
		printf("   ============================================================================================\n");
		
		for(i = 0; i < (*pItems); i++)
			if( (strstr(aItems[i].itemName, tempItemName)) != NULL)
					if (key == 'N' || key == 'n'){
						printf("   | %15d| %-22s| %-17s| %13.2f| %14d|\n", aItems[i].productID, aItems[i].itemName, 
							aItems[i].category, aItems[i].price, aItems[i].quantity);
						do {
							key = getch();
						} while ((key != 'x' && key != 'X') && (key != 'N' && key != 'n'));
					}
		printf("   --------------------------------------------------------------------------------------------\n");	}
}

/** This function loads previous cart information from a binary file "<user's ID>.bag"
	if there is a previous cart. If not, it creates a new cart by writing into a
	new binary file.
*/
void loadPreviousCart(arrCart aCart, int *pCart, int *userID)
{
	FILE *fpBin;
	
	string20 filename;
	itoa(*userID, filename, 10); // converts integer into string
	strcat(filename, ".bag"); 	 // appends required file extension to the string
	
	if ( (fpBin = fopen(filename, "rb")) != NULL ) {
		printf("   Loading cart..\n");
		
		*pCart = 0;
		while ( fread(&aCart[*pCart], sizeof(structItemType), 1, fpBin) == 1 )
			(*pCart)++;
			
		fclose(fpBin);
		printf("   %d item/s in Cart.\n", *pCart);
	} 
	else {
		fpBin = fopen(filename, "wb");
		printf("   Making new cart..\n");	
		fclose(fpBin);	
	}
}

/** This function saves remaining item information to a binary file of Items with
	the filename <user's ID>.bag
*/
void saveCart(arrCart aCart, int nCart, int *userID)
{
	FILE *fpBin;
	int i;
	
	string20 filename;
	itoa(*userID, filename, 10); // converts integer into string
	strcat(filename, ".bag");
	
	if ( (fpBin = fopen(filename, "wb")) != NULL ){
		for(i = 0; i < nCart; i++)
			fwrite(&aCart[i], sizeof(structItemType), 1, fpBin);
			printf("\t\tDEBUGGING: nCart = %d", nCart);
		fclose(fpBin);
	}
	else printf("   ERROR opening file for writing.\n");
}

/** This function displays all product information contained in Cart.
*/
void displayCart(arrCart aCart, int *pCart)
{
	int i;
	printf("   ============================================================================================\n");
	printf("   |	Product ID  |	    Item Name	    |	   Category    |  Unit Price  |	   Quantity   |\n");
	printf("   ============================================================================================\n");
	
	for (i = 0; i < *pCart; i++)
		printf("   | %15d| %-22s| %-17s| %13.2f| %14d|\n", aCart[i].productID, aCart[i].itemName, 
					aCart[i].category, aCart[i].price, aCart[i].quantity);
		printf("   --------------------------------------------------------------------------------------------\n");
}

/** This function finds the product ID of the item that the buyer wishes to buy then checks if 
	the currently logged-in user is in the directory of seller IDs in the stored array of Items.
*/
int checkBuyer(arrItems aItems, int *pItems, int userID, int productID)
{
	int i;
	for(i = 0; i < *pItems; i++)
		if(productID == aItems[i].productID)
			if(userID == aItems[i].sellerID)
				return 0;
	return 1;
}

/** This function asks for the product ID and first checks if the buyer is trying to buy his own product. It then searches
	for the product in the array of Items. When found, it checks if the item quantity is enough for the user input quantity.
	If the cart is full already, no additional items can be added to the cart suggests that the user proceed to Edit Cart 
	or Check Out first before adding more items.
*/
void addToCart(arrItems aItems, int *pItems, arrCart aCart, int *pCart, int userID)
{
	structItemType temp;
	int i;
	int prodIndex = 0;
	int found = 0;
				
	if(*pCart < 10) { //checks if cart is already full
		printf("   Input product ID of item to buy: ");
		scanf("%d", &temp.productID);
		if (checkBuyer(aItems, pItems, userID, temp.productID)){ // checks if buyer is trying to buy his own item
			if(findProductID(aItems, pItems, temp.productID, &prodIndex)) { //checks for existing item
				printf("   Input quantity of item to buy: ");
				scanf("%d", &temp.quantity);
				
				if( temp.quantity >= aItems[prodIndex].quantity ){	//checks if item quantity is enough
					printf("   Insufficient quantity for this item.");
				} 
				
				for(i = 0; i < *pCart; i++)
					if(aCart[i].productID == temp.productID){	//checks if item is already in Cart
						aCart[i].quantity += temp.quantity;
						found = 1;
					}
				
				if(!found)
					for(i = 0; i < *pItems; i++)
						if(temp.productID == aItems[i].productID){
							aCart[*pCart] = aItems[i];
							aCart[*pCart].quantity = temp.quantity;
							(*pCart)++;
						}
			} else printf("   Product ID doesn't exist.\n");
		} else printf("   User cannot buy own item.\n");
	}
	else{
		printf("   Cart already full! Cannot add items to cart.\n");
		printf("   Choose to [Edit Stock] or [Check Out] before adding items.\n");
	}
		
			printf("\t\tDEBUGGING: nCart = %d\n", *pCart);
}

/** This function first displays all items in the Cart then provides the submenus (Remove all
	items from Seller, Remove Specific Item...) for editing.
*/
void editCart(arrItems aItems, int *pItems, arrCart aCart, int *pCart, int userID)
{
	int option4 = 1;
	int i;
	char dump;
	structItemType temp;
	int deductCart = 0;
	
	printf("   %d item/s in the cart.\n", *pCart);	
	displayCart(aCart, pCart);
	
	while(option4 != 0){
		printf("\n   Select from [Edit Cart] options.\n");
		printf("\t1: Remove all items from Seller\n\t2: Remove Specific Item\n");
		printf("\t3: Edit Quantity\n\t0: Finish Edit Cart\n");
		scanf("%d%c", &option4, &dump);
		
		switch(option4){
			case 1:{
				printf("   2.2.6.1 Remove all items from Seller\n");
				printf("   Enter seller ID: ");
				scanf("%d", &temp.sellerID);
				
				for(i = 0; i < *pCart; i++)
					if(temp.sellerID == aCart[i].sellerID){
						aCart[i] = aCart[i+1];
						deductCart++;
					}
					(*pCart) -= deductCart;	
					printf("   Items removed.\n");
				break;
			}
			case 2:{
				printf("   2.2.6.2 Remove Specific Item\n");
				printf("   Enter product ID: ");
				scanf("%d", &temp.productID);
				
				for(i = 0; i < *pCart; i++)
					if(temp.productID == aCart[i].productID){
						printf("   Item '%s' removed.\n", aCart[i].itemName);
						aCart[i] = aCart[i+1];				
						(*pCart)--;
					}				
				break;
			}
			case 3:{
				printf("   2.2.6.3 Edit Quantity\n");
				printf("   Enter product ID: ");
				scanf("%d", &temp.productID);
				
				printf("   Enter new quantity: ");
				scanf("%d", &temp.quantity);
				
				for(i = 0; i < *pCart; i++)
					if(temp.productID == aCart[i].productID){
						if(temp.quantity <= aItems[i].quantity)
							aCart[i].quantity = temp.quantity;
					}
				break;
			}
			case 0:{
				printf("   2.2.6.4 Finish Edit Cart\n");
				printf("   <..Returning to Buy Menu..>\n");
				break;
			}
		}
	
	}
}

/** This function checks if items to be checked out are available and if seller has updated
	the information (..quantity and price). If there is any change, the buyer is notified 
	by displaying the old and the new quantity and price; changes are also updated in the 
	cart. The buyer is given notice (message) that he can still go to Edit Cart.
*/
void checkIfAvailable(arrItems aItems, int *pItems, arrCart aCart, int *pCart)
{
	int i, j;
	
	for(i = 0; i < *pCart; i++)
		for(j = 0; j < *pItems; j++)
			if(aCart[i].productID == aItems[j].productID) {
					if (aCart[i].quantity > aItems[j].quantity) {
						printf("\n   Change in [quantity] for item '%s', \n", aCart[i].itemName);
						printf("   Go to [Edit Cart] to make changes.\n");
						printf("	Old quantity: %d\n	New quantity: %d\n", aCart[i].quantity, aItems[j].quantity);
//						printf("    Updating [quantity]..\n");
//						aCart[i].quantity = aItems[j].quantity;
					}
					else if (aCart[i].price > aItems[j].price) {
							printf("\n   Change in [price] for item '%s', \n", aCart[i].itemName);
							printf("   Go to [Edit Cart] to make changes.\n");
							printf("	Old price: %.2f\n	New price: %.2f\n", aCart[i].price, aItems[j].price);
//							printf("    Updating [price]..\n");
//							aCart[i].price = aItems[j].price;
					}
//					else printf("   \n<CHECKED> UPDATED quantity and price.\n");
			}
//				else printf("   \n<CHECKED> UPDATED quantity and price.\n");
}

/** This function saves the transactions made by reading the end of "Transactions.dat" then writing
	into the file.
*/
void saveTransac(structTransacType transac)
{
	FILE *fpBin;
	
	if( (fpBin = fopen("Transactions.dat", "rb+")) != NULL){
		fseek(fpBin, 0, SEEK_END);
		fwrite(&transac, sizeof(structTransacType), 1, fpBin);
		fclose(fpBin);	
	}
}

void checkOutBySpecSeller(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems, arrCart aCart, int *pCart, structTransacType transac, int sellerID, int buyerID);

/** This function removes all items bought by the user and updates the cart. Each transaction contains all items 
	from the same seller only then a display of summary of each transaction should be displayed on the screen
	following the table format: quantity, product ID, item name, unit price, total price for item. Then below 
	the table, a total amount due for the transaction and payable to sellerID and seller name. Only then will 
	transaction information added to the binary file "Transactions.dat". 
*/
void checkOutAll(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems, arrCart aCart, int *pCart, structTransacType transac, int buyerID)
{
	int i;
	int currSellerID;
	
	for(i = 0; i < *pCart; i++){
		currSellerID = aCart[i].sellerID;
		checkOutBySpecSeller(aUsers, pUsers, aItems, pItems, aCart, pCart, transac, currSellerID, buyerID);
	}
}

/** This function removes items bought from the cart based on inputted seller ID.
*/
void checkOutBySpecSeller(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems, arrCart aCart, int *pCart, structTransacType transac, int sellerID, int buyerID)
{
	int i, j;
	int transItemCount = 0;
	transac.totalAmount = 0;

	for(i = 0; i < *pCart; i++)
		if(sellerID == aCart[i].sellerID && (transItemCount < 5)){ // searching sellerID user input in the array of Cart
				transac.sellerID = aCart[i].sellerID; //copies the transaction information
				transac.buyerID = buyerID;
				transac.itemList[transItemCount] = aCart[i];
				transac.totalAmount += (transac.itemList[i].quantity*transac.itemList[i].price);
				transItemCount++;
		}

	printf("   --- Summary of Transactions ---\n");
	// quantity, productID, item name, unit price, total price, 
	//below table: total amt due, payable for sellerID and sellername
	
	printf("   ============================================================================================\n");
	printf("   |   Quantity    |    Product ID  |	    Item Name	    |  Unit Price  |    Total Price   |\n");
	printf("   ============================================================================================\n");	
	for(i = 0; i < transItemCount; i++)
		printf("   | %14d| %15d| %-22s| %13.2f|  %16.2f|\n", transac.itemList[i].quantity, transac.itemList[i].productID, transac.itemList[i].itemName, 
				transac.itemList[i].price, (transac.itemList[i].quantity * transac.itemList[i].price));
	printf("   --------------------------------------------------------------------------------------------\n");

	printf("   Total amount due: %.2f\n", transac.totalAmount);
	for (i = 0; i < *pUsers; i++)
		if(sellerID == aUsers[i].userID)
			printf("   Paid to seller '%s' (userID %d)\n", aUsers[i].name, aUsers[i].userID);
		
	for(i = 0; i < *pCart; i++) // subtracting item quantity from cart quantity
		if(transac.itemList[i].productID == aCart[i].productID){
			aItems[i].quantity -= aCart[i].quantity;
		}
	
	for(i = 0; i < *pCart; i++) // removing items bought from the cart
		if(transac.itemList[i].productID == aCart[i].productID){
			j = 0;
			while (j < *pCart-1){
				aCart[j] = aCart[j+1];
				j++;
			}
		}	
}


/** This function checks out a specific item inputted by the user then displays the summary of transactions. Then it will 
	update the cart.
*/
void checkOutBySpecItem(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems, arrCart aCart, int *pCart, structTransacType transac, int productID, int buyerID)
{
	int i;
//	int cartIndex;
	
	for(i = 0; i < *pCart; i++)
		if(productID == aCart[i].productID){ // searching productID user input in the array of Cart
			transac.sellerID = aCart[i].sellerID; //copies the transaction information
			transac.buyerID = buyerID;
			transac.itemList[0] = aCart[i];
			transac.totalAmount += (transac.itemList[0].quantity*transac.itemList[0].price);
		}

	printf("   ==============================================================================================\n");
	printf("   |   Quantity    |    Product ID  |	    Item Name	    |  Unit Price  |    Total Price   |\n");
	printf("   ==============================================================================================\n");	
	
	printf("   | %14d| %15d| %-22s| %13.2f|  %13.2f|\n", transac.itemList[0].quantity, transac.itemList[0].productID, transac.itemList[0].itemName, 
				transac.itemList[0].price, (transac.itemList[0].quantity * transac.itemList[0].price));
	printf("   ----------------------------------------------------------------------------------------------\n");	
	
	printf("   Total amount due: %.2f\n", transac.totalAmount);
	for (i = 0; i < *pUsers; i++)
		if(transac.sellerID == aUsers[i].userID)
			printf("   Paid to seller '%s' (userID %d)\n", aUsers[i].name, transac.sellerID);
			
	for(i = 0; i < *pCart; i++) // subtracting item quantity from cart quantity
		if(transac.itemList[i].productID == aCart[i].productID){
			aItems[i].quantity -= aCart[i].quantity;
		}
	
	for(i = 0; i < *pCart; i++) // removing items bought from the cart
		if(transac.itemList[i].productID == aCart[i].productID){
			aCart[i] = aCart[i+1];
			(*pCart)--;
		}	
}


/** This function gets input date from the user then displays the options for checkout.
*/
void checkOutMenu(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems, arrCart aCart, int *pCart, int buyerID)
{
	int option4 = 1;
	int i;
	char dump;
	int sellerID;
	int productID;
	structTransacType transac;
	
//	do{
		printf("   Input date (month/day/year): ");
		scanf("%d%c%d%c%d", &transac.date.month, &dump, &transac.date.day, &dump, &transac.date.year);
//	} while	( !(transac.date.month>=1 && transac.date.month<=12) && !(transac.date.day>=1 && transac.date.day<=31) //checking for valid date input
//				&& !(transac.date.year>=1900 && transac.date.year<=9999) );
	
	checkIfAvailable(aItems, pItems, aCart, pCart);

	while(option4 != 0){	
		printf("\n   Select from [Check Out] options\n");
		printf("\t1: All\n\t2: By a Specific Seller\n");
		printf("\t3: Specific Item\n\t0: Exit Check Out\n");
		scanf("%d%c", &option4, &dump);
		
		switch(option4){
			case 1: { printf("   2.2.7.1 All\n");
				printf("   --- Summary of Transactions ---\n");
				// quantity, productID, item name, unit price, total price, 
				//below table: total amt due, payable for sellerID and sellername
				
				printf("   ===============================================================================================================\n");
				printf("   |	Quantity  |	Product ID  |	    Item Name	    |  Unit Price  |	  Total Price   |\n");
				printf("   ===============================================================================================================\n");
	
				for(i = 0; i < *pCart; i++)
					printf("   | %15d| %15d| %-22s| %13.2f|  %13.2f|\n", aCart[i].quantity, aCart[i].productID, aCart[i].itemName, 
							aCart[i].price, (aCart[i].quantity * aCart[i].price));
				break;
			}
			case 2: { printf("   2.2.7.2 By a Specific Seller\n");
				printf("   Enter seller ID: ");
				scanf("%d", &sellerID);
				checkOutBySpecSeller(aUsers, pUsers, aItems, pItems, aCart, pCart, transac, sellerID, buyerID);
				saveTransac(transac); // saving transactions into "Transactions.dat"	
				break;
			}
			case 3: { printf("   2.2.7.3 Specific Item\n");
				printf("   Enter product ID: ");
				scanf("%d", &productID);
				checkOutBySpecItem(aUsers, pUsers, aItems, pItems, aCart, pCart, transac, productID, buyerID);
				saveTransac(transac); // saving transactions into "Transactions.dat"
				break;
			}
			case 0: { printf("   <...2.2.7.4 Exiting Check Out Menu...>\n");
				
				break;
			}
		}
	}
}

/** This function checks if the inputted password matches with the required admin password
	before being able to enter the Admin Menu.
*/
int adminLog(string20 placePass)
{
	string20 adminPass = "H3LLo?";
	
	printf("   Please enter password for ADMIN LOG: ");
	fgets(placePass, 21, stdin);
	placePass[ strlen(placePass) - 1 ] = '\0';

	if ( strcmp(placePass, adminPass) == 0 )
		return 1;
	else
		printf("   <Error> Unauthorized access not allowed.\n");
	return 0;
}

/** This function sorts user information in increasing order according to
	user ID.
*/
void sortUserID(arrUsers aUsers, int nUsers)
{
	int i, j;
	structUserType temp;
	
	for (i = 0; i < nUsers-1; i++)
		for (j = i+1; j < nUsers; j++)
			if ( aUsers[i].userID > aUsers[j].userID ) { //checking for larger user ID
				temp = aUsers[j];
				aUsers[j] = aUsers[i];
				aUsers[i] = temp;		
			}
}

/** This function shows all users arranged by their user ID in a table following the format: 
	userID, password, name, address, phone number.	
*/
void showAllUsers(arrUsers aUsers, int nUsers)
{
	int i;
	sortUserID(aUsers, nUsers);
	
	printf("   %d user/s found.\n", nUsers);
	printf("   ===============================================================================================================\n");
	printf("   |	User ID	    |	 Password    |		Name	     |		    Address	     |      Phone no.    |\n");
	printf("   ===============================================================================================================\n");

	for (i = 0; i < nUsers; i++) {
		printf("   | %15d| %-15s| %-22s| %-30s| %18.0lf|\n", aUsers[i].userID, aUsers[i].password, aUsers[i].name, 
				aUsers[i].address, aUsers[i].contactNo);
	}
	printf("   ---------------------------------------------------------------------------------------------------------------\n");
}

/** This function shows all the users who have items to be sold (i.e., if there exists in the Items array a 
	seller ID matching the user’s ID). The display should be in table format in the following sequence: userID, 
	password, name, address, phone number, number of items for sale [not quantity].
*/
void showAllSellers(arrUsers aUsers, int *pUsers, arrItems aItems, int *pItems)
{	
	int i, j;
	int itemCount = 0;
	printf("   =======================================================================================================================================\n");
	printf("   |	User ID	    |	 Password    |		Name	     |		    Address	     |    Phone no.   |    No. Items for Sale    |\n");
	printf("   =======================================================================================================================================\n");
	
	for(i = 0; i < *pUsers; i++){
		itemCount = 0;
		for (j = 0; j < *pItems; j++)
			if( aItems[j].sellerID == aUsers[i].userID )
				itemCount++;
				
		if(itemCount > 0)		
			printf("   | %15d| %-15s| %-22s| %-30s| %15.0lf| %25d|\n", aUsers[i].userID, aUsers[i].password, aUsers[i].name, 
					aUsers[i].address, aUsers[i].contactNo, itemCount);
	}
	printf("   ---------------------------------------------------------------------------------------------------------------------------------------\n");
}

/** This function asks the user to input 2 dates to serve as the start and end dates. 
	The program then checks the contents of Transactions.dat whose dates fall within 
	the duration from start to the end dates, then returns 1 if it is.
*/
int checkTransacDate(structTransacType transac)
{
	FILE *fp;
	char dump;
	structDateType sDate, eDate;
	
	printf("   Input <start> date (month/day/year): ");
	scanf("%d%c%d%c%d", &sDate.month, &dump, &sDate.day, &dump, &sDate.year);

	printf("   Input <end> date (month/day/year): ");
	scanf("%d%c%d%c%d", &eDate.month, &dump, &eDate.day, &dump, &eDate.year);
	
	if((fp = fopen("Transactions.dat", "rb")) != NULL){
		fread(&transac, sizeof(structTransacType), 1, fp);
		
		if(transac.date.year >= sDate.year && transac.date.year <= eDate.year){
			if(transac.date.month >= sDate.month && transac.date.month <= eDate.month)
				if(transac.date.day >= sDate.day && transac.date.day <= eDate.day)
					return 1;
		}
		fclose(fp);
	} else printf("   Error opening binary file for reading.\n");
	
	return 0;
}

/** This function displays total amount of all the transactions if input date falls
	within the start and end dates.
*/
void showTotalSales(structTransacType transac)
{
	FILE *fp;
	
	if( checkTransacDate(transac) ){
		if((fp = fopen("Transactions.dat", "rb")) != NULL){
			fread(&transac, sizeof(structTransacType), 1, fp);
			printf("   Total amount of all transactions: %.2f", transac.totalAmount);
			
			fclose(fp);
		} else printf("   Error opening binary file for reading.\n");
	} else printf("   Start and end dates did not fall within duration dates.\n");
}

/** This function displays the total sales for each seller in table format in the following 
	sequence: seller ID, seller name, total sales in the duration if the input date falls
	within the start and end dates.
*/
void showSellerSales(structTransacType transac, arrUsers aUsers, int *pUsers)
{
	FILE *fp;
	int i;
	
	if( checkTransacDate(transac) ){
		if((fp = fopen("Transactions.dat", "rb")) != NULL){
			fread(&transac, sizeof(structTransacType), 1, fp);
			printf("   Total Sales for Sellers\n");
			printf("   ===========================================================\n");
			printf("   |	Seller ID  |	Seller Name  |	    Total Amount	 |\n");
			printf("   ===========================================================\n");
			
			for(i = 0; i < *pUsers; i++)
				if(transac.sellerID == aUsers[i].userID)
					printf("   | %d| %-22s| %.2f|", transac.sellerID, aUsers[i].name, transac.totalAmount);

			fclose(fp);
		} else printf("   Error opening binary file for reading.\n");
	} else printf("   Start and end dates did not fall within duration dates.\n");
}

/** This function displays the total amount for each buyer in table format in the following sequence: 
	buyer ID, buyer name, total amount bought in the duration if the input date falls within the start 
	and end dates.
*/
void showShopaholics(structTransacType transac, arrUsers aUsers, int *pUsers)
{
	FILE *fp;
	int i;
	
	if( checkTransacDate(transac) ){
		if((fp = fopen("Transactions.dat", "rb")) != NULL){
			fread(&transac, sizeof(structTransacType), 1, fp);
			
			printf("   Shopaholic Sellers\n");
			printf("   ===========================================================\n");
			printf("   |	Seller ID  |	Seller Name  |	    Total Amount	 |\n");
			printf("   ===========================================================\n");
			
			for(i = 0; i < *pUsers; i++)
				if(transac.buyerID == aUsers[i].userID)
					printf("   | %d| %-22s| %.2f|", transac.buyerID, aUsers[i].name, transac.totalAmount);
					
			fclose(fp);
		} else printf("   Error opening binary file for reading.\n");
	} else printf("   Start and end dates did not fall within duration dates.\n");
}

int 
main()
{
	int option1 = 0,
		option2 = 1,
		option3 = 1;

	int nUsers = 0; 	//counter for registered users
	int nItems = 0; 	//counter for added items
	int nCart  = 0;		// counter for item transactions

	int 	 viewSellerID;
	int 	 userID = 0; 	// placeholder currently logged-in user ID
	int		 logIndex = 0;  // placeholder for index of logged-in user
	
	string20 placePass; 	// placeholder for inputted password in Admin Menu
	char 	 dump;
	
	arrUsers users;
	arrItems items;
	arrCart  cart;
	structTransacType transac;
	
	loadUsers(users, &nUsers);
	loadItems(items, &nItems);
	
	while (option1 != 4) {
		printf("\n [MAIN MENU] Please select an option. \n");
		printf("\t[1]: Register as a User\n\t[2]: User Menu\n\t[3]: Admin Menu\n\t[4]: Exit\n");
		scanf("%d%c", &option1, &dump);
		
					printf("\n\t\t..%d loaded user/s\n", nUsers);
					printf("\t\t..%d loaded item/s\n", nItems);
		
		option2 = 1;
		if(option1 >= 1 && option1 <= 4) { // ===== MAIN MENU =====
			switch(option1)	{ 
				case 1: { // ===== [1] REGISTER USER =====
					printf("\t[Register as a User]\n"); 
					if( nUsers < MAX_USER )	{
						registerUser(users, &nUsers);
					} else printf("    Max users have been reached.");
					break;
				}
				case 2: { // ===== [2] USER MENU =====
					if ( userLogin(users, &nUsers, &userID, &logIndex) ) { //successful login
								printf("\n\t\t< Successful login. >\n");
							
								loadPreviousCart(cart, &nCart, &userID);
								printf("\t\t..%d loaded item/s in cart\n\n", nCart);

						while (option2 != 0) {
							option3 = 1;		
							printf("\n   [USER MENU]\n");
								printf("   Select from the options. \n");
								printf("\t1: Sell Menu\n\t2: Buy Menu\n\t0: Exit User Menu\n");
								scanf("%d%c", &option2, &dump);	
								
								switch(option2)	{ 
									case 1: { // 2.1 Sell Menu ---------------------------------------------
										printf("   [2.1 Sell Menu]\n"); 
										
										while (option3 != 0) {													
											printf("\n   Select from [Sell menu] options.\n");
											printf("\t1: Add New Item\n\t2: Edit Stock\n\t3: Show My Products\n\t4: Show My Low Stock Products\n\t0: Exit Sell Menu\n");
											scanf("%d%c", &option3, &dump);
											
											switch(option3) {
												case 1: { // 2.1.1 Add New Item
													printf("   2.1.1 Add New Item\n");
													addNewItem(items, &nItems, userID);
													break;
												}
												case 2: { // 2.1.2 Edit Stock
													printf("   2.1.2 Edit Stock\n");
													editStock(items, &nItems, &userID);
													break;
												}	
												case 3: { // 2.1.3 Show My Products
													printf("   2.1.3 Show My Products\n");
													showMyProducts(items, &nItems, &userID);
													printf("\n");
													break;
												}
												case 4: { // 2.1.4 Show My Low Stock Products
													printf("   2.1.4 Show My Low Stock Products\n");
													showLowStocks(items, &nItems, &userID);
													printf("\n");
													break;
												}		
												case 0: { // 2.1.5 EXIT Sell Menu
													printf("   <...2.1.5 Exit Sell Menu...>\n"); 
													break;
												} 
											}
										}
										break;
									} // -------------------------- Sell Menu ----------------------------
									
									case 2: { // 2.1 Buy Menu ----------------------------------------------
										printf("   [2.1 Buy Menu]\n"); 
										
										while (option3 != 0) {
											printf("   Select from the options.\n");
											printf("\t1: View all Products\n\t2: Show all Products by a Specified Seller\n\t3: Search Products by Category\n\t4: Search Products by Name\n");
											printf("\t5: Add to Cart\n\t6: Edit Cart\n\t7: Check Out Menu\n\t0: Exit Sell Menu\n");
											scanf("%d%c", &option3, &dump);
											
											switch(option3) {
												case 1: { // 2.2.1 View all Products
													printf("   2.2.1 View all Products\n");
													viewAllProducts(users, nUsers, items, nItems);
													break;
												}
												case 2: { // 2.2.2 Show all Products by a Specified Seller
													printf("   2.2.2 Show all Products by a Specified Seller\n");
													printf("   Enter seller ID: ");
													scanf("%d%c", &viewSellerID, &dump);
													showProductsBySeller(items, &nItems, viewSellerID);
													break;
												}	
												case 3: { // 2.2.3 Search Products by Category
													printf("   2.2.3 Search Products by Category\n");
													searchProductsByCategory(items, &nItems);
													break;
												}
												case 4: { // 2.2.4 Search Products by Name
													printf("   2.2.4 Search Products by Name\n");
													searchProductsByName(items, &nItems);
													break;
												}		
												case 5: { // 2.2.5 Add to Cart
													printf("   2.2.5 Add to Cart\n");
													addToCart(items, &nItems, cart, &nCart, userID);
													break;
												}
												case 6: { // 2.2.6 Edit Cart
													printf("   2.2.6 Edit Cart\n");
													editCart(items, &nItems, cart, &nCart, userID);
													break;
												}		
												case 7: { // 2.2.7 Check Out Menu
													printf("   2.2.7 Check Out Menu\n");
													checkOutMenu(users, &nUsers, items, &nItems, cart, &nCart, userID);
													break;
												}
												case 0: { // 2.1.5 EXIT Buy Menu
													printf("   <...2.1.5 Exiting Buy Menu..>\n");
													break;
												} 
											}
										}
										break;
									} // -------------------------- Buy Menu ----------------------------
									case 0: {
										printf("	<..Exiting User Menu..>\n");
										saveCart(cart, nCart, &userID);
										printf("   <..Cart saved.>\n");
										break;
									}
								}
							}
					} // end of successful LOG-IN 
					else { 
						printf("\t<Error: Input does not match any users.>\n"); 
						option2 = 0;
					}
					break;
				}
				case 3: { // ===== [3] ADMIN MENU =====
					printf("   [ADMIN MENU]\n");

					if ( adminLog(placePass) ) { // checking for correct ADMIN password
						printf("\n\t\t---Successful login for ADMIN.\n");
							while ( option3 != 0 ) { 
								printf("\n    Select options from ADMIN Menu.\n");
								printf("\t1: Show All Users\n\t2: Show All Sellers\n\t3: Show Total Sales in Given Duration\n");
								printf("\t4: Show Sellers Sales\n\t5: Show Shopaholics\n\t0: Back to Main Menu\n");
								scanf("%d%c", &option3, &dump);
								switch(option3)  {
									case 1: { // 3.1 Show All Users
										printf("   3.1 Show All Users\n");
										showAllUsers(users, nUsers);
										break;
									}
									case 2: { // 3.2 Show All Sellers 
										printf("   3.2 Show All Sellers\n");
										showAllSellers(users, &nUsers, items, &nItems);
										break;
									}
									case 3: { // 3.3 Show Total Sales in Given Duration
										printf("   3.3 Show Total Sales in Given Duration\n");
										showTotalSales(transac);
										break;
									}
									case 4: { // 3.4 Show Sellers Sales 
										printf("   3.4 Show Sellers Sales\n");
										showSellerSales(transac, users, &nUsers);
										break;
									}
									case 5: { // 3.5 Show Shopaholics
										printf("   3.5 Show Shopaholics\n");
										showShopaholics(transac, users, &nUsers);
										break;
									}
									case 0: { // 3.6 Back to Main Menu
										printf("   <..returning to Main Menu..\n");
										break;
									}
								}
							}
						} 
						else 
							option2 = 0;
					break;
				}
				case 4: { // ===== [4] EXIT.. =====
					saveUsers(users, nUsers);
					printf("\tUsers saved.\n");
					saveItems(items, nItems);
					printf("\tItems saved.\n");


					printf("\t\t\t%d user/sn\n", nUsers);
					printf("\t\t\t%d item/s\n\n", nItems);
					
					printf("\t<Exiting program..>\n");
					break;
				}
			}
		} else printf("<Error> Invalid input. Please try again.\n\n");
	}
	
	return 0;
}
