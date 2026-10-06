 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>


typedef struct{
    char name[50];
    int telefono;
}contactos;

void buscar_contacto(contactos *mi_agenda,int numero_contactos);
contactos* insertar_contacto(contactos *mi_agenda, int *numero_contactos);
contactos* actualizar_contacto(contactos *mi_agenda,int*numero_contactos);
contactos* eliminar_contacto(contactos *mi_agenda,int*numero_contactos);
void guardar_archivo(contactos *mi_agenda,int numero_contactos);
contactos* cargar_archivo(contactos *mi_agenda,int *numero_contactos);

int main(){
contactos *mi_agenda=NULL; // Crea estructura dinámica

int numero_contactos=0; // Para el indice de realloc e ir creando mas contactos.
int option=0; //Opcion para el switch
char car_extra; 

mi_agenda=cargar_archivo(mi_agenda,&numero_contactos);

    do{
        printf("\n\n---Bienvenido a la agenda virtual---\n\n");
        printf("Elige una opcion:\n1-Buscar un contacto.\n2-Insertar un contacto.\n");
        printf("3-Actualizar un contacto.\n4-Eliminar un contacto\n5-Salir.\n");

        

        if(scanf("%d%c",&option,&car_extra)==2 && car_extra=='\n'){
            
            switch(option){
                case 1:{
                    buscar_contacto(mi_agenda,numero_contactos);

                    break;
                }
        

                case 2:
                    mi_agenda = insertar_contacto(mi_agenda,&numero_contactos);

                    break;

                case 3:
                    mi_agenda= actualizar_contacto(mi_agenda,&numero_contactos);
                    break;

                case 4:
                    mi_agenda = eliminar_contacto(mi_agenda,&numero_contactos);

                    break;

                case 5:
                    printf("Saliendo de la agenda. Adios\n");
                    guardar_archivo(mi_agenda,numero_contactos);
                    
                    free(mi_agenda);
                    break;

                default:
                    printf("Opcion incorrecta, debe marcar 1,2,3,4 o 5, intentelo de nuevo.\n");
            }

    
        }
        else{
            printf("Opcion incorrecta, no introducir letras ni simbolos.\n");
            while(getchar()!='\n');
        }

    }while(option!=5);
    
    printf("\nPulsa ENTER para cerrar la ventana...");
    getchar();
    
    
    return 0;

}

void buscar_contacto(contactos *mi_agenda,int numero_contactos){

    printf("Ha elegido la opcion 1\n");

    if(numero_contactos==0){ //Si contactos es 0 marca vacia y sale.
        printf("La agenda esta vacia.\n");
        return;
    }

    char buscar[50];
    int encontrado=0;

    printf("Introduce el nombre del contacto a buscar: ");
    scanf("%s",buscar);

    for(int i=0;i<numero_contactos;i++){
        if(strcmp(buscar,mi_agenda[i].name)==0){
            encontrado=1;
            printf("\nContacto encontrado:\n");
            printf("Nombre: %s, Telefono: %d.\n",mi_agenda[i].name,mi_agenda[i].telefono);
            break;
            }
        }
    if(encontrado==0){
        printf("Contacto no encontrado.\n");
        }


}

contactos* insertar_contacto(contactos *mi_agenda, int *numero_contactos){
    printf("Ha elegido la opcion 2:\n");

    *numero_contactos +=1; //Aumento en 1 para tener espacio para otro contacto nuevo
    contactos *temp = (contactos*)realloc(mi_agenda,(*numero_contactos)*sizeof(contactos));

    if(temp!=NULL){ //Si temp no es NULL pasamos temp a mi_agenda
        mi_agenda = temp;
        int correcta = 1; //Flag para isalpha
        printf("Introduce el nombre del contacto: "); //Pedimos nombre y tlf
        scanf("%s",mi_agenda[(*numero_contactos)-1].name);
        printf("\nIntroduce el numero del contacto: ");
        scanf("%d",&mi_agenda[(*numero_contactos)-1].telefono);

        for(int j=0;j<strlen(mi_agenda[(*numero_contactos)-1].name);j++){
            if(!isalpha(mi_agenda[(*numero_contactos)-1].name[j])){
                correcta = 0; //Si no son letras marcamos 0 
                *numero_contactos-=1; //Restamos 1 para elimininar el espacio y salimos
                printf("Error has introducido mal el nombre, solo se admite letras.\n");
    
                break;

            }

        }
        if(correcta==1 && mi_agenda[(*numero_contactos)-1].telefono >=100000000 && mi_agenda[(*numero_contactos)-1].telefono<=999999999){
            printf("\nContacto guardado correctamente.\n");
        }
        else{
            *numero_contactos-=1; //Si falla algun requisito restamos 1 para eliminar el espacio
            printf("Has introducido mal el numero, son 9 digitos\n");
        }
                       
    }
    else{ //Si es NUll temp no hay memoria y restamos el hueco q haya creado.
        printf("Error: no hay memoria suficiente.\n");
        *numero_contactos-=1;
    }
    return mi_agenda; //Devolvemos la agenda actualizada

}

contactos* actualizar_contacto(contactos *mi_agenda,int*numero_contactos){
    printf("Ha elegido la opcion 3:\n");

    if((*numero_contactos)==0){ 
        printf("La agenda esta vacia.\n");
        return mi_agenda;
    }

    char buscar[50]; 
    int encontrados=0; 
    char temp_name[50]; //var temp para el nombre
    int temp_telefono; // var temp para el tlf
    int correct =1; // Flag para isalpha
    int indice=-1; // Guardar el indice de la palabra que busco

    printf("Introduce el nombre del contacto a actualizar: ");
    scanf("%s",buscar);

    for(int i=0;i<(*numero_contactos);i++){ //Busco el nombre
        if(strcmp(buscar,mi_agenda[i].name)==0){
            encontrados=1; //Encontrado
            indice = i; //Guardo indice
            printf("\nIntroduce el nuevo nombre y telefono:\n");
            printf("Nombre: ");  //Pido nuevos nombres y tlf
            scanf("%s",temp_name);
            printf("\nTelefono: ");
            scanf("%d",&temp_telefono);
            break;
        }
    }
    if(encontrados==1){ //Si encontramos el nombre
        for(int h=0;h<strlen(temp_name);h++){
            if(!isalpha(temp_name[h])){ //Si no son letras rompemos.
                correct =0;
                break;
            }
        }
        //Si son letras y cumple las requisitos q pongamos
        if(correct==1 && temp_telefono>=100000000 && temp_telefono<=999999999){
            if(indice!=-1){ // Si el indice no es basura
                strcpy(mi_agenda[indice].name,temp_name); //Copio el nombre temp a contactos
                mi_agenda[indice].telefono = temp_telefono; // Tb copio el tlf
                printf("Contacto actualizado correctamente.\n");

                }
        }
        else{
            //Si algo falla entramos aqui
                            
            printf("Nombre o telefono a actualizar no valido.\n");
            }

    }
    else{ //Si no lo encontro entra aqui
        printf("Contacto no encontrado.\n");
        }
    return mi_agenda;
}

contactos* eliminar_contacto(contactos* mi_agenda,int *numero_contactos){
    printf("Ha elegido la opcion 4:\n");

    if((*numero_contactos)==0){ 
        printf("La agenda esta vacia.\n");
        return mi_agenda;
        }

    char buscar[50]; //Contacto a buscar para eliminar
    int encontrado=0; // flag para encontrarlo
    int pos_eliminar=-1; // Indice para poder eliminar el contacto

    printf("Introduce el nombre del contacto a eliminar: ");
    scanf("%s",buscar);

    for(int i=0;i<(*numero_contactos);i++){
        if(strcmp(buscar,mi_agenda[i].name)==0){
            encontrado=1; // Si encontramos el contacto
            pos_eliminar=i; //Guardamos su posicion
            break;
        }
    }
    if(encontrado==1){
        //Miramos desde la pos guardada hacia adelante
        // copiando el contacto siguiente en la posicion l
        // para ir moviendo el contacto q queremos eliminar
        // al final
        for(int l=pos_eliminar;l<(*numero_contactos)-1;l++){ //n_contacos-1 para q no coja basura al final
            strcpy(mi_agenda[l].name,mi_agenda[l+1].name);
            mi_agenda[l].telefono=mi_agenda[l+1].telefono;

            }
        (*numero_contactos) -=1; //Restamos 1 al numero de contactos
        if((*numero_contactos)==0){ //Si fuese el ultimo contacto
            // Liberamos manualmente para no destruir la estructura agenda
            free(mi_agenda);
            mi_agenda=NULL;
            printf("Ultimo contacto eliminado, lista vacia.\n");
            }
        else{
            //Creamos realloc temporal por si hay problemas con los nuevos numero_contactos
            contactos*temp_2 = (contactos*)realloc(mi_agenda,(*numero_contactos)*sizeof(contactos));
            if(temp_2!=NULL){ //Si no es NULL pasamos a mi_agenda
                mi_agenda = temp_2;
                printf("Contacto eliminado correctamente.\n");
                }
            }

        }
    else{ //Si no se encunetra el contacto
        printf("Contacto no se puede eliminar porque no se encuentra en contactos.\n");
        }
    return mi_agenda;

}

void guardar_archivo(contactos *mi_agenda, int numero_contactos){
    //Abrimos archivo con w q sobreescribe lo que haya
    FILE *archivo=fopen("agenda.txt","w");

    if(archivo==NULL){ //Comprobamos q no sea NULL el archivo
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int i=0;i<numero_contactos;i++){
        // Escribir todos los contactos en el archivo
        fprintf(archivo,"%d %s %d\n",i+1,mi_agenda[i].name,mi_agenda[i].telefono);
    }
    fclose(archivo);//Cerramos

}

contactos* cargar_archivo(contactos *mi_agenda,int *numero_contactos){
    FILE *archivo=fopen("agenda.txt","r");

    if(archivo==NULL){ 
        printf("El archivo no existe, creando uno nuevo...\n");
        return mi_agenda; 
    }
    
    // Variables temporales para fscanf
    int id_temp;
    char name_temp[50];
    int tlf_temp;
    
    // Leemos linea a linea usando el "espejo" del formato fprintf.
    while(fscanf(archivo,"%d %s %d\n",&id_temp,name_temp,&tlf_temp)==3){

        // Hacemos hueco en la matriz dinamica (realloc)
        (*numero_contactos) +=1;
        contactos *temp=(contactos*)realloc(mi_agenda,(*numero_contactos)*sizeof(contactos));

        if(temp!=NULL){
            mi_agenda=temp;

            //Copiamos las variables temp a nuestra matriz
            strcpy(mi_agenda[(*numero_contactos)-1].name,name_temp);
            mi_agenda[(*numero_contactos)-1].telefono=tlf_temp;
        }
    }
    fclose(archivo); //Cerramos archivo
    printf("Contactos guardados correctamente\n");
    return mi_agenda;
}