using namespace std;
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//**** PRICES ARE SUBJECT TO CHANGE AS ARE MENU ITEMS !!!! ****//
#define BEVERAGE_NAME_LENGTH
// int order=0;
typedef struct _coffee
{
char coffeeName[55];
float pricemilk;
float pricecream;
float pricelatte;
} * coffee;
#define coffee_type (sizeof(struct _coffee))
typedef struct _TOrderItem
{
struct _coffee bevItem;
char type;
int qty;
} *TOrderItem;
#define ORDER_ITEM_SIZE (sizeof(struct _TOrderItem))
#define MAX_NUM_ITEMS_PER_ORDER (12)
#define TAX_PERCENT (0.0000) //ex. 6.5
void DisplayMenu(coffee menuArray, int N)
{
cout << "********************************************************************" << endl;
cout << " Item # coffee milk cream latte " << endl;
cout << "******************************************************************" << endl;
struct _coffee curBev;
for (int iLoop=0; iLoop<N; iLoop++)
{
curBev = menuArray[iLoop];
cout << " " << (iLoop+1) << " " << curBev.coffeeName
<< " " << " $" <<fixed << setprecision(2)
<< curBev.pricemilk << " $" <<fixed << setprecision(2)
<< curBev.pricecream << " $" <<fixed << setprecision(2)
<< curBev.pricelatte << endl;
}
cout << "**********************************************************************" <<
endl;
}
void InputOrder(coffee Coffee,int N, TOrderItem order, int * numItems)
{
bool done_flag = false;
(*numItems)=0;
while (!done_flag)
{
int itemNum = 0;
while ((itemNum<1) || (itemNum>N))
{
DisplayMenu(Coffee,N);
cout << "\n Please Enter Item # :>";
cin >> itemNum;
}
char itemtype='?';
while ((itemtype !='S') && (itemtype!='M') && (itemtype!='L'))
{
cout << "Please Enter type :>";
cin >> itemtype;
itemtype = toupper(itemtype);
}
int qty=0;
while (qty<=0)
{
cout << "Please Enter the quantity :>";
cin >> qty;
}
struct _TOrderItem curOrderItem;
curOrderItem.bevItem = Coffee[itemNum-1];
curOrderItem.type = itemtype;
curOrderItem.qty = qty;
order[(*numItems)]=curOrderItem;
(*numItems)++;
char chResponse='?';
while ((chResponse !='Y') && (chResponse !='N'))
{
cout << "Another Item ??? Y = YES N=No :>";
cin >>chResponse;
chResponse = toupper(chResponse);
}
done_flag = ((*numItems>=MAX_NUM_ITEMS_PER_ORDER) || (chResponse=='N'));
// cout << " # of items ordered =" << *numItems << endl;
}
}
float CalculateOrder(TOrderItem order,int numItems)
{
float subtotal=0;
float finalAmt=0;
//cout << " # of items ordered =" << numItems << endl;
cout << " ITEM SIZE QTY PRICE SUBTOTAL "<< endl;
for (int iLoop=0; iLoop<numItems; iLoop++)
{
float price = 0;
struct _TOrderItem curOrderItem = order[iLoop];
cout << curOrderItem.bevItem.coffeeName << " " << curOrderItem.type << " " << curOrderItem.qty;
switch (curOrderItem.type)
{
case 'S':
{
price = curOrderItem.bevItem.pricemilk;
break;
}
case 'M':
{
price = curOrderItem.bevItem.pricecream;
break;
}
case 'L':
{
price = curOrderItem.bevItem.pricelatte;
break;
}
}
subtotal = price * curOrderItem.qty;
cout << " " << fixed << setprecision(2) << price
<< " " << fixed << setprecision(2) << subtotal << endl;
finalAmt += subtotal;
}
return(finalAmt);
}
void PaymentOrder(TOrderItem order, int numItems, float amt)
{
cout << endl;
cout << " Grand Sub-Total is $" << fixed << setprecision(2) << amt << endl;
float taxAmt = amt*(TAX_PERCENT/100.00f);
cout << " Tax at " << TAX_PERCENT << " = " << fixed << setprecision(2) << taxAmt << endl;
float finalAmount = amt + taxAmt;
cout << " THE FINAL AMOUNT IS " << fixed << setprecision(2) << finalAmount << endl;
float amtTendered=0;
while (amtTendered<finalAmount)
{
cout << " Please Enter amount Tendered :> ";
cin >> amtTendered;
}
float changeAmt = amtTendered - finalAmount + 0.005;
cout << "Change due to customer = " << fixed << setprecision(2) <<changeAmt << endl;
long longIntNumAmt = (long) (changeAmt*100.00);
cout << "amount in pennies = " << longIntNumAmt << endl;
cout << longIntNumAmt/10000 << " x $100 bills " << endl; longIntNumAmt %= 10000;
cout << longIntNumAmt/5000 << " x $50 bills " << endl; longIntNumAmt %=5000;
cout << longIntNumAmt/2000 << " x $20 bills " << endl; longIntNumAmt %=2000;
cout << longIntNumAmt/1000 << " x $10 bills " << endl; longIntNumAmt %=1000;
cout << longIntNumAmt/500 << " x $5 bills " << endl; longIntNumAmt %=500;
cout << longIntNumAmt/100 << " x $1 bills " << endl; longIntNumAmt %=100;
cout << longIntNumAmt/25 << " x quarters " << endl; longIntNumAmt %=25;
cout << longIntNumAmt/10 << " x dimes " << endl; longIntNumAmt %=10;
cout << longIntNumAmt/5 << " x nickels " << endl; longIntNumAmt %=5;
cout << longIntNumAmt << " x pennies " << endl;
}
int main( int argc, char * argv[])
{
struct _coffee Coffee[] = { {"Espresso",60.00,75.00,100.00} , {"Cappuccino",80.00,90.00,125.00}, {" Latte ",100.00,125.00,150.00}, };
struct _TOrderItem order[MAX_NUM_ITEMS_PER_ORDER ];
//there are currently 12 items on the menu
{
int numItems=0;
memset( order,0,MAX_NUM_ITEMS_PER_ORDER*ORDER_ITEM_SIZE );
InputOrder(Coffee,3,order,&numItems);
float amount = CalculateOrder(order,numItems);
PaymentOrder(order,numItems,amount);
}
