#include <stdio.h>
#include <string.h>

typedef struct{/*object strucute, contains object name, object type and quantity*/
    char name[40];
    char type[40];
    int quantity;
}object;

typedef struct{/*object inventory structure. Contains tab named inventory, lenth of 100; 
able to hold 100 objects. Contains a object_number later used to know if inventory is full*/
    object inventory[100];
    int object_number;
}objectsinventory;

void add_to_object_inventory(objectsinventory *anInventory, char *name, int addedquantity){
    for(int i=0;i<anInventory->object_number;i++){
        if (strcmp(anInventory->inventory[i].name, name) == 0){/*==0 is used in strings comparition process. 
        If strings got the same lenth, the returned number is 0*/
            anInventory->inventory[i].quantity += addedquantity;/*adds the added quantity to the current quantity*/
            return;
        }
    }
    strcpy(anInventory->inventory[anInventory->object_number].name, name);/*ajoute le nom de l''objet dans l'inventaire*/
    anInventory->inventory[anInventory->object_number++];
    anInventory->inventory[anInventory->object_number].quantity = addedquantity; 
    anInventory->object_number++;
}

void remove_object(objectsinventory *anInventory, char *name, int removed_quantity){
    for(int i=0;i<anInventory->object_number;i++){
        if (strmcp(anInventory->inventory[i].name, name)==0){
            if (((anInventory->inventory[anInventory->object_number].quantity)-removed_quantity)<0){
                printf("text : not enough objects");
            }
            else
            {
                
            }
        }
    }
}

int main(){
    return 0;
}