#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include<windows.h>
#include<string.h>

typedef struct category category;
typedef struct product product;

COORD coord = {0, 0};

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct category
{
    char name[50];
    int counter_products;
    product *products;
};
struct product
{
    int id;
    char name[50];
    float price;
    char size;
    int quantity;
};

int counter_categories=0;
 int number=0;
category *categories=NULL;

void AddCategory()
{
    char ch;
    categories = realloc(categories ,(counter_categories+1)*sizeof(category));
    do{

         printf("Enter Category Name: ");
         scanf(" %[^\n]s",categories[counter_categories].name);
         printf("Do you want to Enter an additional category? (y/n) ");
         ch=getche();
         printf("\n");
         categories[counter_categories].counter_products=0;
         categories[counter_categories].products=NULL;
         counter_categories++;
         categories = realloc(categories, (counter_categories + 1) * sizeof(category));

    }while(ch != 'n' );
}

void Display()
{
     if (counter_categories ==0)
         {
             printf("No categories entered\n");
         }
     for (int i=0;i<counter_categories;i++)
    {
       printf("%d-The products of %s\n",i+1,categories[i].name);
       for(int j=0;j<categories[i].counter_products;j++)
       {
           printf("ID: %d\n",categories[i].products[j].id);
           printf("Name: %s\n",categories[i].products[j].name);
           printf("Size: %c\n",categories[i].products[j].size);
           printf("Price: %f\n",categories[i].products[j].price);
           printf("Quantity: %d\n",categories[i].products[j].quantity);
       }
    }
}

void AddProduct() {
    int counter_products;
    char ch;//y-n
     if (counter_categories ==0)
     {
         printf("No categories entered\n");
     }
    for (int i = 0; i < counter_categories; i++) {
        printf("%d-%s\n", i + 1, categories[i].name);
        printf("how many products do you need to add? ");
        scanf("%d", &counter_products);

        categories[i].products = realloc(categories[i].products, (categories[i].counter_products + counter_products) * sizeof(product));

        for (int j = categories[i].counter_products; j < categories[i].counter_products + counter_products; j++) {
            printf("The product of %s\n", categories[i].name);
            printf("Enter ID: ");
            scanf("%d", &categories[i].products[j].id);
            printf("Enter Name: ");
            scanf(" %[^\n]s", categories[i].products[j].name);
            printf("Enter Size (S/M/L): ");
            scanf(" %c", &categories[i].products[j].size);
            printf("Enter Price: ");
            scanf("%f", &categories[i].products[j].price);
            printf("Enter Quantity: ");
            scanf("%d", &categories[i].products[j].quantity);
        }
        categories[i].counter_products += counter_products;
    }
}


void MoveProduct() {
    if (counter_categories==0)
    {
        printf("No categories entered\n");
        return;
    }
    char moved_product[50], dest_category[50], src_category[50];
    printf("Enter the name of category from which you want to move the product: ");
    scanf(" %[^\n]s", src_category);
    printf("Enter the name of product you want to move: ");
    scanf(" %[^\n]s", moved_product);
    printf("Enter the name of category where the product will be moved: ");
    scanf(" %[^\n]s", dest_category);

    int src_index = -1, dest_index = -1;


    for (int i = 0; i < counter_categories; i++) {
        if (strcmp(categories[i].name, src_category) == 0) {
            src_index = i;
        }
        if (strcmp(categories[i].name, dest_category) == 0) {
            dest_index = i;
        }
    }

    if (src_index == -1 || dest_index == -1) {
        printf("Invalid category names entered.\n");
        return;
    }
    if (categories[src_index].counter_products==0)
    {
        printf("No products entered.\n");
        return;
    }


    for (int j = 0; j < categories[src_index].counter_products; j++) {
        if (strcmp(categories[src_index].products[j].name, moved_product) == 0) {
            categories[dest_index].products = realloc(categories[dest_index].products, (categories[dest_index].counter_products + 1) * sizeof(product));

            categories[dest_index].products[categories[dest_index].counter_products] = categories[src_index].products[j];
            categories[dest_index].counter_products++;

            for (int k = j; k < categories[src_index].counter_products - 1; k++) {
                categories[src_index].products[k] = categories[src_index].products[k + 1];
            }
            categories[src_index].counter_products--;

            printf("Product '%s' moved from '%s' to '%s'\n", moved_product, src_category, dest_category);
            return;
        }
    }

    printf("Product '%s' not found in '%s'\n", moved_product, src_category);
}


void SellProduct()
{
char ch;
    do {
    int flag=0;
    char selled_product[20];
       if (counter_categories ==0)
        {
            printf("No categories entered\n");
            return;
        }
        printf("Enter the name of product that you want to sell ");
        scanf(" %[^\n]s",selled_product);
       for (int i=0;i<counter_categories;i++)
       {
           for (int j=0; j<categories[i].counter_products;j++)
           {
            if(strcmp(categories[i].products[j].name,selled_product) ==0&&categories[i].products[j].quantity>0)
               {
                   categories[i].products[j].quantity--;
                   flag=1;
               }
           }
       }
       if (flag ==1)
       {
           printf("sell done\n");

       }
       if (flag==0){
         printf("Invalid product Quantity \n");
       }
                printf("Do you want to Enter an additional Product to Sell? (y/n) ");
         ch=getche();
         printf("\n");
    }while(ch!='n');
Display();

}

void FreeMemory()
{
    for (int i=0;i<counter_categories;i++)
    {
        free(categories[i].products);
    }
    free(categories);
}
int main()
{
    int option=1;
    int last_option= 7;
    char choice;
    while(1)
    {
        system("cls");
        gotoxy(30,5);
        SetColor(14);
        printf("Main Menu");
        SetColor(15);
        for (int i=1;i<=last_option;i++)
        {
            gotoxy(30,6+i);
            if (option == i)
            {
                SetColor(3);
                if (i==7)
                {
                    SetColor(12);
                }
            }
            else{
                SetColor(15);
            }
            if (i==option)
            {
                printf("%d>>",i);
            }
            else{
                printf("%d-",i);
            }
            switch(i)
            {
            case 1:
                printf("Home");
                break;
            case 2:
                printf("New Category");

                break;
            case 3:
                printf("New Product");
                break;
            case 4:
                printf("Sell Product");
                break;
            case 5:
                printf("Move Product");
                break;
            case 6:
                printf("Display");
                break;
            case 7:
                printf("Exit");
                break;
            }
        }

        choice=getch();
        switch(choice)
        {
        case 72:
            if(option>1)
            {
                option--;
            }
            break;
        case 80:
            if(option<=last_option)
            {
                option++;
            }
            break;
        case 13:
            switch(option)
            {
            case 1:
                system("cls");
                printf("Welcome in my coffee shop\n");
                printf("Back to menu to be able to use my application\n");
                system("pause");
                break;
            case 2:
                system("cls");
                printf("Categories: \n");
                printf("-----------\n");
                AddCategory();
                system("pause");
                break;
            case 3:
                system("cls");
                printf("Products \n");
                AddProduct();
                system("pause");
                break;
            case 4:
                system("cls");
                printf("Sell Product:\n");
                printf("-------------\n");
                SellProduct();
                system("pause");
                break;
            case 5:
                system("cls");
                printf("Moving Product:\n");
                printf("---------------\n");
                MoveProduct();
                system("pause");
                break;
            case 6:
                system("cls");
                printf("Display:\n");
                printf("--------\n");
                Display();
                system("pause");
                break;
            case 7:
                FreeMemory();
                exit(0);
                break;
            }
            break;
        }
}    }

