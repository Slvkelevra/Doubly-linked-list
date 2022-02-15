#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_TITLE 50
#define DIM_GENRE 50
#define DIM_NAME 50



struct song{
    char title[DIM_TITLE];
    char genre[DIM_GENRE];
    float length;
    struct song* prev;
    struct song* next;
    
};typedef struct song Song;

struct playlist{
    char name[DIM_NAME];
    Song* top;
};typedef struct playlist PlayList;

void mostrarListaEnlazada(PlayList *pl);

Song* nextSong(Song* s){
    if(s->next!=NULL){
        return s->next;
    }else{
        return NULL;
    }
}

Song* prevSong(Song* s){
    if(s->prev!=NULL){
        return s->prev;
    }else{
        return NULL;
    }
}

//*****************************************************************************
//                  FUNCION acquireSong
//Su funcion es alocar una nueva cancion en memoria
Song* acquireSong(){
    //Alocamos un nuevo espacio de memoria de tamaño Song
    Song* new_s = (Song*)malloc(sizeof(Song));
    //Pedimos todos los datos por pantalla
    printf("\nInserta el titulo -> ");
    scanf("%[^\n]s", new_s->title);
    getchar();

    printf("Inserta el genero -> ");
    scanf("%[^\n]s", new_s->genre);
    getchar();

    printf("Inserta la duracion -> ");
    scanf("%f", &(new_s->length));
    getchar();

    new_s->prev = NULL;
    new_s->next = NULL;
    
    return new_s;
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION printSong
//Su funcion es imprimir una cancion
void printSong(Song* t){
    printf("TITULO    :\t %s \n", t->title);
    printf("GENERO    :\t %s \n", t->genre);
    printf("DURACION   :\t %f \n\n", t->length);
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION findSong
//Su funcion es buscar una cancion a lo largo de una lista ordenada
Song* findSong(PlayList * pl,char tittle[]){
    
    //Apuntamos a la primera
    Song *puntador=pl->top;
    
    //Recorremos todas las canciones
    while(puntador != NULL){
        
        //Comparamos los nombres.Si son iguales,devolemos la cancion
        if(strcmp(puntador->title,tittle)==0){
            return puntador;
        }else{
            //Si no son iguales y no hemos llegado al final,proxima cancion
            if(puntador->next!=NULL){
                puntador=nextSong(puntador);
                
            }else{
                //Hemos llegado al final y no la encontramos(puntador.next==NULL
                return NULL;
            }
        }
    }
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION insertSong
//Su funcion es ingresar una nueva cancion en una lista.No devuelve nada
void insertSong(PlayList* pl,Song* s){
    
    //Si el nombre es correcto
    if(s->title != NULL){
        //Si la lista esta vacia,se inserta como la primera
        if(pl->top==NULL){
            pl->top=s;
        
        //la lista tiene al menos 1 elemento
        }else{
            
            //Comprobamos que no haya una cancion con el mismo nombre
            if(findSong(pl, s->title) == NULL){
                
                Song *puntador=pl->top;
                Song *previa=NULL;
                
               
                // <0 si primera es menor que segunda
                // >0 si primera es mayor que segunda
                // ==0 si son iguales
                while(puntador!=NULL && strcmp(puntador->title,s->title)<0){
                    previa=puntador;
                    puntador=nextSong(puntador);
                }
                
                //Si se debe insertar como la ultima
                if(puntador==NULL){
                    previa->next=s;
                    s->prev=previa;
                    s->next=NULL;
                    
                }else{
                    //Si debe insertarse como la primera
                    if(previa==NULL){
                        pl->top=s;
                        s->next=puntador;
                        puntador->prev=s;
                        s->prev=NULL;
                        
                    }else{
                        //Se debe insertar entre medias
                        //IMPORTANTE: no hay filtro,ya que puede ocurrir que
                        //se inserte la penultima,o se inserte la segunda.Se
                        //deja sin filtro y se da por hecho que se debe insertar
                        //entre dos canciones.Ya procuramos antes de llegar aqui
                        //de saberlo con certeza.
                            puntador->prev=s;
                            previa->next=s;
                            s->prev=previa;
                            s->next=puntador;
                    } 
                }  
            }     
        }
    }
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION deleteSong
// Su funcion es borrar una canción de la lista,ajustando los punteros
void deleteSong(PlayList* pl,Song* s){

    if(findSong(pl, s->title) == NULL){
        printf("\n No existe\n.");
    }else{
        
        //Si solo hay una
        //Si es la ultima
        //Si es la primera
        //Si es entre medias

        //Si solo hay un elemento
        if(s->prev==NULL && s->next==NULL){
            free(s);
            pl->top=NULL;
            printf("\nSolo habia una canción.Se ha borrado con exito\n");
           
        }
        //Si es la primera y hay por lo menos dos
        if(s->prev==NULL && s->next!=NULL){
            //Ponemos la segunda como inicio de la lista
            pl->top=nextSong(s);
            //Ponemos el campo de la segunda a null,ya que ahora es la primera
            nextSong(s)->prev=NULL;
            //Eliminamos la cancion
            free(s);
           
        //Si es la ultima
        }else{
            if(s->next==NULL){
                //Ponemos el campo next de la anterior a null
                prevSong(s)->next=NULL;
                free(s);
        //Si está entre medias
            }else{
                //Ponemos campo prev de la siguiente apuntando a la anterior
                nextSong(s)->prev=prevSong(s);
                //Ponemos el campo next de la anterior apuntando a la siguiente
                prevSong(s)->next=nextSong(s);
                free(s);
            } 
        }
    }
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION printPlayList
//Su funcion es estampar toda la lista por pantalla    
void printPlayList(PlayList* pl){
    
    //Si no hay ninguna cancion
    if(pl->top==NULL){                  
        printf("\nError.PlayList vacia \n ");
    }else{
        //Puntero para recorrer la lista
        Song *puntador=pl->top;
        while(puntador != NULL){
            //Estampamos cancion
            printSong(puntador);
            //Avanzamos a la siguiente
            puntador =nextSong(puntador);
        }
    }
}
//*****************************************************************************

//*****************************************************************************
//              FUNCION modifySong
//Su funcion es buscar la cancion que queremos cambiar y darle un nuevo nombre
void modifySong(PlayList * pl,Song* s){
    
    //Buscamos la cancion.Si no la encuentra,devuelve "su cancion no esta..."
    if(findSong(pl, s->title) == NULL){
        printf("\nSu cancion no esta en la lista");
    }else{
        //Creamos una nueva cancion(más sencillo) y le damos el nuevo nombre
        Song* new_s = (Song*)malloc(sizeof(Song));
        printf("\nInsert title -> ");
        scanf("%[^\n]s", new_s->title);
        getchar();
        
        new_s->length=s->length;
        new_s->next=s->next;
        new_s->prev=s->prev;
        strcpy(new_s->genre,s->genre);

        //Borramos la original
        deleteSong(pl,s);
        //Insertamos la nueva
        insertSong(pl, new_s);
    }
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION mostrarListaEnlazada
//Su funcion es mostrar una lista enlazada lo más real posible,para conseguir
//entender lo que hace este programa.Enlaza las estructuras con dos campos:
//la cancion previa y la cancion siguiente.
void mostrarListaEnlazada(PlayList *pl){
    
    //Declaramos puntero que recorrerá la lista
    Song *puntador=pl->top;
    //Recorremos mostrando las canciones hasta que la proxima cancion sea NULL
    while(puntador!=NULL){
        printf("%s-%s-%s\n",puntador->prev->title,puntador->title,
                puntador->next->title);
        puntador=nextSong(puntador);
    }
    printf("Fin de la lista\n\n");
}
//*****************************************************************************

//*****************************************************************************
//                  FUNCION mergePlayList
//Su funcion es mezclar dos listas en una tercera.Las listas A y B se consideran
//ya ordenadas.Creamos una copia de la cancion a insertar en la lista,para evitar
//cambiar los punteros de las listas originales A y B.Esta funcion requiere una
//cantidad considerable de memoria(si la lista es grande) en comparacion con el
//posible metodo de hacer un array de punteros.
void mergePlayList(PlayList* primera,PlayList *segunda,PlayList* mezcla){

    //Declaramos los punteros que recorrerán las listas
    Song *puntero_a=primera->top;
    Song *puntero_b=segunda->top;
    Song *puntero_mezcla=mezcla->top;

    //Recorrermos hasta que los dos hayan llegado hasta el final
    while(puntero_a!=NULL && puntero_b!=NULL){
        //si es menor y no ha llegado al final
        if(strcmp(puntero_a->title,puntero_b->title)<0 && puntero_a!=NULL){
            //Alocamos una copia de la cancion a añadir en la nueva lista
            Song* new_s = (Song*)malloc(sizeof(Song));
            strcpy(new_s->genre,puntero_a->genre);
            new_s->length=puntero_a->length;
            new_s->next=puntero_a->next;
            new_s->prev=puntero_a->prev;
            strcpy(new_s->title,puntero_a->title);
            //Insertamos en la lista
            insertSong(mezcla,new_s);
            //Avanzamos el puntero de la lista a
            puntero_a=nextSong(puntero_a);
            //Avanzamos el puntero de la lista mezcla
            puntero_mezcla=nextSong(puntero_mezcla);
        }
        //Si es mayor y no ha llegado al final 
        if((puntero_a->title,puntero_b->title)>0 && puntero_b!=NULL){
            
            Song* new_s = (Song*)malloc(sizeof(Song));
            strcpy(new_s->genre,puntero_b->genre);
            new_s->length=puntero_b->length;
            new_s->next=puntero_b->next;
            new_s->prev=puntero_b->prev;
            strcpy(new_s->title,puntero_b->title);
            insertSong(mezcla,new_s);
            puntero_b=nextSong(puntero_b);
            puntero_mezcla=nextSong(puntero_mezcla);
        }
    }
}
//*****************************************************************************



//                          FUNCION MAIN
//*****************************************************************************
//*****************************************************************************

int main()
{

    PlayList p;
    PlayList j;
    PlayList mezcla;
    
    char tittle_trovata[50];
    strcpy(p.name, "Rap");
    strcpy(j.name, "Techno");
    strcpy(mezcla.name, "Lista mezcla");
    p.top = NULL;
    j.top=NULL;
    mezcla.top=NULL;
    
        
    Song *una=acquireSong();
    insertSong(&p,una);
      
    Song *dos=acquireSong();  
    insertSong(&p,dos);
    
    Song *tres=acquireSong();  
    insertSong(&j,tres);
    
    Song *cuatro=acquireSong();  
    insertSong(&j,cuatro);
    
    
    
    //Mezclar ambas listas
    //mergePlayList(&p,&j,&mezcla);
    
    //Imprimir nueva lista
    //printPlayList(&mezcla);
    
    //Imprimir lista con segundo metodo
    //printf("\nLista mezclada:\n");
    //mostrarListaEnlazada(&p);
    
    //Modificar cancion
    //modifySong(&p,una);
    
    //Buscar cancion
    //printf("cancion a buscar: ");
    //scanf("%s",tittle_trovata);
    //printSong(findSong(&p,tittle_trovata));
    

    return 0;
}

