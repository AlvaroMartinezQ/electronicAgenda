#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define chunk 1024;
                                                                                //Declaracion de las funciones.
int menuOptions(int* a);
int addContact(void);
int deleteContact(void);
int modifyContact(void);
int contactSearch(void);
int listContacts(void);
void deleteAll(void);
int exitProgram(int *a);
                                                                                //Estructura utilizada para crear el contacto.
struct contact{
    char name[24];
    char surname[24];
    int number[8];
};
                                                                                //Llamada de la funcion principal main().
int main(/*int argc, char* argv[]*/){
    int option = 0;
    int n = 0;
    printf("Welcome to the agenda.\n");
    do{
        menuOptions(&option);
        switch (option) {
        case 1://ADD CONTACT//
            addContact();
            break;
        case 2://DELETE CONTACT//
            deleteContact();
            break;
        case 3://MODIFY CONTACT//
            modifyContact();
            break;
        case 4://CONTACT SEARCH//
            contactSearch();
            break;
        case 5://LIST ALL CONTACTS//
            listContacts();
            break;
        case 6: //DELETE THE LIST//
            deleteAll();
            break;
        case 7://EXIT//
            exitProgram(&n);
            break;
                                                                                //Caso por defecto, en caso de que se introduzca un valor no
                                                                                //valido al utilizar la consola de comandos de la agenda.
        default:
            printf("\nInvalid option entered. Please enter a valid option.\n\n");
        }
    }while (n!=99);
    return 0;
}
                                                                                //Funcion del menu de opciones de la agenda.
int menuOptions(int* a){
    printf("Press:\n "
           "1 to add a new contact.\n "
           "2 to delete a contact.\n "
           "3 to modify a contact.\n "
           "4 to search a contact (by giving a name).\n "
           "5 to list all contacts.\n "
           "6 to delete the existing list.\n "
           "7 to exit.\n");
    fflush(0);
    scanf("%d", a);
    return *a;
}
                                                                                //Funcion anyadir contacto.
int addContact(void){
    struct contact newContact;
    printf("Name of the new contact: \n");
    scanf("%s", newContact.name);
    printf("Surname of the contact: \n");
    scanf("%s", newContact.surname);
    printf("Number of the contact: \n");
    fflush(0);
    scanf("%d", newContact.number);
    printf("\n%s %s with phone number: %d.\n", newContact.name, newContact.surname, *newContact.number);

    FILE * filePointer;

    filePointer = fopen("electronicAgenda.txt", "a");

    if(filePointer == NULL){
        printf("Error while opening file. Please try again later.\n");
        return -1;
    }

    fprintf(filePointer, "%s %s: %d.\n", newContact.name, newContact.surname, *newContact.number);
    printf("\nContact saved with success!\n\n");
    fclose(filePointer);
    return 0;
}
                                                                                //Funcion borrar contacto.
int deleteContact(void){
    FILE* filePointer;
    filePointer = fopen("electronicAgenda.txt", "r");
    if(filePointer == NULL){
        printf("Error while opening file. Please try again later.\n");
        return -1;
    }
    char nameOfContact[1024];
    printf("Name of the contact to delete:\n");
    fflush(0);
    scanf("%s", nameOfContact);
    FILE* newFile;
    newFile = fopen("newFile.txt", "w");
    if(newFile == NULL){
        printf("Error, please try again later.\n");
        return -2;
    }
    char searcher[1024];
    while(fgets(searcher, sizeof(searcher), filePointer)!=NULL){
        if(strstr(searcher, nameOfContact)){
            printf("\nContact found. Deleting contact.\n\n");
        }else{
            fprintf(newFile, "%s", searcher);
        }
    }

    fclose(filePointer);
    fclose(newFile);
    remove("electronicAgenda.txt");
    rename("newFile.txt", "electronicAgenda.txt");
    return 0;
}
                                                                                //Funcion cambiar contacto. Se ha decididio hacer
                                                                                //llamada a las funciones borrar contacto y anyadir
                                                                                //contacto para ahorrar codigo y posible
                                                                                //futura complejidad.
int modifyContact(void){
    deleteContact();
    addContact();
    return 0;
}
                                                                                //Funcion buscar contacto.
int contactSearch(void){
    FILE * fileptr;
    char nameToSearch[24];
    char content[100];
    fileptr = fopen("electronicAgenda.txt", "r");
    if(fileptr == NULL){
       printf("Unable to open file. Please try again later.\n");
            return -1;
    }
    printf("Name of the contact to search: \n");
    scanf("%s", nameToSearch);
    while(fgets(content, sizeof(content), fileptr)){
        if(strstr(content, nameToSearch)){
            printf("%s is in your list of contacts.\n", content);
            return 0;
        }
    }
    printf("%s in not in your contact list.\n", nameToSearch);
    fclose(fileptr);
    return 2;
}
                                                                                //Funcion listar contactos.
int listContacts(void){
    FILE * fileptr;
    char buf[1024];
    size_t nRead;
    fileptr = fopen("electronicAgenda.txt", "r");
    if(fileptr == NULL){
        printf("Unable to open file. Please try again later.\n");
        fclose(fileptr);
        return -1;
    }
    while((nRead = fread(buf, 1, sizeof (buf), fileptr)) > 0){
        printf("\n");
        fwrite(buf, 1, nRead, stdout);
        fclose(fileptr);
        printf("\n");
        return 0;
    }
    fclose(fileptr);
    printf("\nYour list is empty.\n\n");
    return 1;
}
                                                                                //Funcion extra, borrar toda la lista para no tener que
                                                                                //borrar contacto por contacto con la funcion borrar contacto.
                                                                                //Hemos decidido que esta funcion no tenga ningun
                                                                                //tipo de retorno, que simplemente escriba por pantalla.
void deleteAll(void){
    FILE * fileptr;
    fileptr = fopen("electronicAgenda.txt", "wb");
    if(fileptr == NULL){
        printf("Unable to open file to delete.\n");
    }
    printf("\nFile has been rebooted.\n\n");
}
                                                                                //Funcion salir del programa.
int exitProgram(int* a){
    printf("Exiting the agenda...\n");
    *a = 99;
    return *a;
}
