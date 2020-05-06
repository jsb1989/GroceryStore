#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DailyTransaction{ 
//Stores Customers Order
int code,quantity;
float price,total_cost;
char name[30];
struct DailyTransaction *next;
}DT;

typedef struct MasterList{ 
//Stores the total order for the day
int code, quantity;
float price, total_cost;
char name[30];
struct MasterList *next;
}ML;

void Add_Item(int code,char name[29],int Quantity,float price,DT **head){
//Adds product to Customers order
DT *node=(DT*)malloc(sizeof(DT));
node->code=code;
strcpy(node->name,name);
node->quantity=Quantity;
node->price=price;
node->total_cost=(price*Quantity);
node->next=NULL;
  if(*head==NULL){
	  *head=node;
  }else{
  node->next=*head;
  *head=node;
  }
}

void AddToMaster(int code,char name[29],int Quantity, float price,ML **MasterHead){
//Adds product to total for the day
ML *node=(ML*)malloc(sizeof(ML));
node->code=code;
strcpy(node->name,name);
node->quantity=Quantity;
node->price=price;
node->total_cost=(price*Quantity);
node->next=NULL;
  if(*MasterHead==NULL){
	  *MasterHead=node;
  }else{
  node->next=*MasterHead;
  *MasterHead=node;
  }
}

void CustRec(int i,struct DailyTransaction* CNode){ 
//Prints Customers Receipt
int Total_Q=0;
float Total_Sale=0;
printf("Customer #%d Receipt\n",i+1);
printf("Code\tName            price\tQuantity\ttotal\n");
    while (CNode!=NULL) { 
        printf(" %d   %s\t    %.2f\t\t%d\t\t%.2f\n", CNode->code,CNode->name,CNode->price,CNode->quantity,CNode->total_cost);
        Total_Q+=CNode->quantity;
        Total_Sale+=CNode->total_cost;
        CNode=CNode->next; 
    } 
  printf("\t\t\t\t\t        Total:  %d\t\t%.2f\n",Total_Q,Total_Sale);
} 

int Duplicate(int search,DT *head){ 
//searches nodes in the customers order list to see if any duplicate exist
DT*CNode;
CNode=head;
while(CNode!=NULL){
	if(CNode->code==search){
	return 1;
	}
  CNode=CNode->next;
}
return 0;
}

int MLDuplicate(int search, ML *masterhead){
//searches nodes in the total order list to see if any duplicate exist
ML*CNode;
CNode=masterhead;
while(CNode!=NULL){
	if(CNode->code==search){
	return 1;
	}
  CNode=CNode->next;
}
return 0;
}

void AddToItem(int search, int Quantity,DT *head){
//Adds to already existing node if it exists in the customers order
DT*CNode;
CNode=head;
while(CNode!=NULL){
  if(CNode->code==search){
    CNode->quantity+=Quantity;
    CNode->total_cost=CNode->price*CNode->quantity;
  }
  CNode=CNode->next;
}
}

void AddToItemML(int search, int Quantity,ML *masterhead){
//Adds to already existing node if it exists in the total order list
ML*CNode;
CNode=masterhead;
while(CNode!=NULL){
  if(CNode->code==search){
    CNode->quantity+=Quantity;
    CNode->total_cost=CNode->price*CNode->quantity;
  }
  CNode=CNode->next;
}
}

void ClearCustRec(DT **head){
//clears the linked list for the customers order
DT* CNode = *head;
  while(CNode!=NULL){
  CNode=CNode->next;
  free(*head);
  *head=CNode;
  }
}

void ClearTotalOrder(ML **masterhead){
//clears the linked list for the customers order
ML* CNode = *masterhead;
  while(CNode!=NULL){
  CNode=CNode->next;
  free(*masterhead);
  *masterhead=CNode;
  }
}

void PrintInventRep(int i,ML *masterhead){
//Prints the inventory report for the day
ML*CNode;
CNode=masterhead;
int Total_Items_Sold=0;
float Total_sales=0;
printf("Code\t Item Name\t\t Num Items\t TotSale\n");
while(CNode!=NULL){
	if(CNode->code>=(i+1)){
    if(CNode->code<=(i+100)){
	  printf("%d     %s\t     %d        %.2f\n",CNode->code,CNode->name,CNode->quantity,CNode->total_cost);
    Total_Items_Sold+=CNode->quantity;
    Total_sales+=CNode->total_cost;
    }
	}
CNode=CNode->next;
}
printf("\n");
printf("Total Items Sold:\t\t%d\n", Total_Items_Sold);
printf("Total Sales:\t\t%.2f\n",Total_sales);
printf("-----------------------------------------------\n");
}

void PrintSumRep(int AmountOfCust,ML *masterhead){
//Prints the summary report for the day
int Total_Items_Sold=0;
float Total_sales=0;
  for(int i=100;i<900;){
    ML*CNode;
    CNode=masterhead;
    int Cat_Amount_Sold=0;
    float Cat_Sales=0;
    while(CNode!=NULL){
	    if(CNode->code>=(i+1)){
       if(CNode->code<=(i+100)){
        Cat_Amount_Sold+=CNode->quantity;
        Cat_Sales+=CNode->total_cost;
        Total_Items_Sold+=CNode->quantity;
        Total_sales+=CNode->total_cost;
        }
	    }
    CNode=CNode->next;
    }
    switch(i){
      case 100:
        printf("%d \tFood Vegetables\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 200:
        printf("%d \tFood Meats\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 300:
        printf("%d \tFood Grains\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 400:
        printf("%d \tFood Frozen\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 500:
        printf("%d \tFood Canned\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 600:
        printf("%d \tToiletries\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 700:
        printf("%d \tCleaning Supplies\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
      case 800:
        printf("%d \tOther\t\t\t\t %d\t\t\t       %.2f\n",i,Cat_Amount_Sold,Cat_Sales);
        i+=100;
        break;
    }
  }
printf("------------------------------------------------------\n");
printf("Total Customers:\t\t%d\n",AmountOfCust);
printf("Total Items Sold:\t\t%d\n", Total_Items_Sold);
printf("Total Sales:\t\t   %.2f\n",Total_sales);
}

void SortDT(DT *head){
// sorts customers order from lowest to highest base of the code #
DT *CNode;
DT *NewCNode;
int temp1,temp2;
float temp3,temp4;
char temp5[30];
for(CNode= head; CNode->next!=NULL;CNode=CNode->next){
	for(NewCNode=CNode->next; NewCNode!=NULL; NewCNode=NewCNode->next){
		if(CNode->code>NewCNode->code){
		temp1=CNode->code;
		CNode->code=NewCNode->code;
		NewCNode->code=temp1;

		temp2=CNode->quantity;
		CNode->quantity=NewCNode->quantity;
		NewCNode->quantity=temp2;

		temp3=CNode->price;
		CNode->price=NewCNode->price;
		NewCNode->price=temp3;

		temp4=CNode->total_cost;
		CNode->total_cost=NewCNode->total_cost;
		NewCNode->total_cost=temp4;

		temp5[29]=CNode->name[29];
		CNode->name[29]=NewCNode->name[29];
		NewCNode->name[29]=temp5[29];
		}
	}
}
}
void SortML(ML *masterhead){
// sorts total order for the day, from lowest to highest base of the code #
ML *CNode;
ML *NewCNode;
int temp1,temp2;
float temp3,temp4;
char temp5[30];
for(CNode= masterhead; CNode->next!=NULL;CNode=CNode->next){
	for(NewCNode=CNode->next; NewCNode!=NULL; NewCNode=NewCNode->next){
		if(CNode->code>NewCNode->code){
		temp1=CNode->code;
		CNode->code=NewCNode->code;
		NewCNode->code=temp1;

		temp2=CNode->quantity;
		CNode->quantity=NewCNode->quantity;
		NewCNode->quantity=temp2;

		temp3=CNode->price;
		CNode->price=NewCNode->price;
		NewCNode->price=temp3;

		temp4=CNode->total_cost;
		CNode->total_cost=NewCNode->total_cost;
		NewCNode->total_cost=temp4;

		temp5[29]=CNode->name[29];
		CNode->name[29]=NewCNode->name[29];
		NewCNode->name[29]=temp5[29];
		}
	}
}
}
int main(){

int AmountOfCust=0,j=1,EOD=0;

DT *head= NULL;
ML *MasterHead=NULL;

for(int i=0; i<=AmountOfCust; i++){
  int Exit=0;
  while(Exit==0){
    int code,Quantity,CustDone=0;
    char name[30];
    float price;
    printf("Product Code: ");
    scanf("%d",&code);
    if(code<100 || code>900){
    printf("PRODUCT CODE NOT BETWEEN 100-900\n"); 
    printf("Product Code: ");
    scanf("%d",&code);
    }
    printf("Name of product:");
    scanf(" %[^\n]s", name);
    printf("Price:");
    scanf("%f",&price);
    printf("Quantity: ");
    scanf("%d",&Quantity);
    int answer=0;
    if(Duplicate(code,head)==1){
      printf("PRODUCT CODE ALREADY MATCHES EXISTING PRODUCT WOULD YOU LIKE TO CONTINUE AND ADD QUANTITY TO THE EXISTING PRODUCT CODE? (0 to continue)\n");
      scanf("%d",&answer);
      if(answer==0){
      AddToItem(code,Quantity,head);
      } else {
      answer=1;  
      }
    } else{
      Add_Item(code,name,Quantity,price,&head);
    }
    if(MLDuplicate(code, MasterHead)==1){
      if(answer==0){
      AddToItemML(code,Quantity,MasterHead);
      }
    } else{
      AddToMaster(code,name,Quantity,price,&MasterHead);
    }
    printf("Does Customer have more items? (0 for Yes, 1 for No)");
    scanf("%d", &CustDone);
    printf("\n");
    answer=0;
    if(CustDone==1){
      answer=0;
      Exit=1; 
    }
  }
  SortDT(head);
  CustRec(i,head);
  ClearCustRec(&head);
  printf("End Of Day?: (0 for Yes, 1 for No)");
  scanf("%d",&EOD);
  if(EOD==0){
    SortML(MasterHead);
    i=AmountOfCust+1;
  }
  AmountOfCust++;
}
printf("\n");
printf("***********Category Inventory Report***********\n");
  for(int i=99;i<899;){ //prints the corresponding category
    switch(i){
      case 99:
        printf("Category Name: Food Vegetables\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 199:
        printf("Category Name: Food Meats\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 299:
        printf("Category Name: Food Grains\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 399:
        printf("Category Name: Food Frozen\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 499:
        printf("Category Name: Food Canned\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 599:
        printf("Category Name: Toiletries\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 699:
        printf("Category Name: Cleaning Supplies\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        i+=100;
        printf("\n");
        break;
      case 799:
        printf("Category Name: Other\n");
        printf("Category Code: %d\n", i+1);
        PrintInventRep(i, MasterHead);
        printf("\n");
        i+=100;
        break;
    }
  }   
printf("\n");
printf("****************Daily Summary Report****************\n");
printf("Code\tCategoryName\t#Items Sold\t\tTotal Sales Amt\n");
printf("----\t------------\t-----------\t\t---------------\n");
PrintSumRep(AmountOfCust,MasterHead);
ClearTotalOrder(&MasterHead);
return 0;
}