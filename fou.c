#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
   
    struct servent *service;
    char service_name[30];
    char protocol[30];
    int port;

    setservent(1); // 1 pour garder le fichier ouvert
    setprotoent(1);

   while(1){ 
    printf("\n\tEntrer le nom du service recherché ou le numéro de port du service, ou bien 'all' pour tous les afficher\n\n\tPour quitter, taper 'exit'\n");
    scanf("%s", service_name);
    port = atoi(service_name);
    
        if (strcmp(service_name, "exit") == 0){
        break;
        }
        else{
            if (strcmp(service_name, "all") == 0){

                while ((service = getservent()) != NULL) {
                    printf("Nom officiel : %s\n", service->s_name);
                    printf("Port : %d\n", ntohs(service->s_port));
                    printf("Protocole : %s\n", service->s_proto);
                    printf("Alias : ");
                    for (char **alias = service->s_aliases; *alias != NULL; alias++) {
                        printf("%s ", *alias);
                    }
                    printf("\n\n");
                }
            }
            else{
                printf("\n\tEntrer le nom du protocole\n");
                scanf("%s", protocol);
                service= getservbyname(service_name, protocol);
                if (service == NULL) {
                    service = getservbyport(htons(port), protocol);
                    if(service == NULL){
                        fprintf(stderr, "Service non trouvé\n");
                    }
                    else{
                    printf("Nom officiel : %s\n", service->s_name);
                    printf("Port : %d\n", ntohs(service->s_port));
                    printf("Protocole : %s\n", service->s_proto);
                    printf("Alias : ");
                    for (char **alias = service->s_aliases; *alias != NULL; alias++) {
                        printf("%s ", *alias);
                    }
                    }
                }
                else{
                    printf("Nom officiel : %s\n", service->s_name);
                    printf("Port : %d\n", ntohs(service->s_port));
                    printf("Protocole : %s\n", service->s_proto);
                    printf("Alias : ");
                    for (char **alias = service->s_aliases; *alias != NULL; alias++) {
                        printf("%s ", *alias);
                    }
                }
                printf("\n\n");
            }
        }
    }
    endprotoent();
    endservent();

    return 0;
}
