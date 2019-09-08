#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct person{

    char name[51];
    char agency[51];
    int age;
    struct person* next;

}person;

typedef struct agency{

    char nameAgency[51];
    int cashier;
    int numbPersonP;
    person* headP;
    int numbPerson;
    person* head;
    
}agency;

agency initAgency(char nameAgency[51], int cashier){

    agency element;
    element.cashier = cashier;
    element.numbPerson = 0;
    element.numbPersonP = 0;
    strcpy(element.nameAgency, nameAgency);
    element.headP = NULL;
    element.head = NULL;
    return element;
}

person* initPerson(char nameAgency[51], char namePerson[51], int age){

    person* element = (person*)malloc(sizeof(person));
    element->next = (person*)malloc(sizeof(person));
    
    strcpy(element->name, namePerson);
    strcpy(element->agency, nameAgency);

    return element;
}

int main(int argc, char const *argv[])
{
    
    FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

    int numbAgency, numbCashier, numbPerson, age, index;
    char nameAgency[51], namePerson[51];

    fscanf(input, "%d", &numbAgency);

    agency* vectorAgencies = (agency*)malloc(numbAgency*sizeof(agency));

    for(int i = 0; i < numbAgency; i++){

        fscanf(input, "%s %d", nameAgency, &numbCashier);
        vectorAgencies[i] = initAgency(nameAgency, numbCashier);

    }

    fscanf(input, "%d", &numbPerson);

    char c[1];

    for(int i = 0; i < numbPerson; i++){
        fscanf(input,"%c %50[^|]%*c %50[^|]%*c %d", c, nameAgency, namePerson, &age);

        for(index = 0; index < numbAgency; index++){
            if(!((strcmp(nameAgency, vectorAgencies[index].nameAgency)))){
                if(age < 60){
                    vectorAgencies[index].numbPerson++;
                    if(vectorAgencies[index].head == NULL){
                        vectorAgencies[index].head = initPerson(nameAgency, namePerson , age);
                    }
                    else{
                        person* aux = vectorAgencies[index].head;
                        while(aux->next != NULL){
                            aux = aux->next;
                        }
                        aux->next = initPerson(nameAgency, namePerson , age);
                    }
                }
                else{
                    vectorAgencies[index].numbPersonP++;
                    if(vectorAgencies[index].headP == NULL){
                        vectorAgencies[index].headP = initPerson(nameAgency, namePerson , age);
                    }
                    else{
                        person* aux = vectorAgencies[index].headP;
                        while(aux->next != NULL){
                            aux = aux->next;
                        }
                        aux->next = initPerson(nameAgency, namePerson , age);
                    }
                }
                break;
            }
        }
    }

    person* aux;

    while(numbPerson > 0){
        for(int x = 0; x < numbAgency; x++){
            if(vectorAgencies[x].numbPerson > 0){
                fprintf(output,"%s:", vectorAgencies[x].nameAgency);
            }
            for(int f = 0; f < vectorAgencies[x].cashier; f++){
                if(vectorAgencies[x].numbPersonP > 0){
                
                    vectorAgencies[x].numbPersonP--;
                    numbPerson--;
                    if(f + 1 < vectorAgencies[x].cashier){
                        fprintf(output,"%s,", vectorAgencies[x].headP->name);
                    }
                    else{
                        fprintf(output,"%s", vectorAgencies[x].headP->name);
                    }
                    aux = vectorAgencies[x].headP->next->next;
                    vectorAgencies[x].headP = aux;
                    
                }
                else if(vectorAgencies[x].numbPerson > 0){
                    
                    vectorAgencies[x].numbPerson--;
                    numbPerson--;
                    if(f + 1 < vectorAgencies[x].cashier && vectorAgencies[x].numbPerson > 0){
                        fprintf(output,"%s,", vectorAgencies[x].head->name);
                    }
                    else{
                        fprintf(output,"%s", vectorAgencies[x].head->name);
                    }
                    aux = vectorAgencies[x].head->next->next;
                    vectorAgencies[x].head = aux; 
                }
            }
            fprintf(output, "\n");
        }
    }
    
    fclose(input);
	fclose(output);

    return 0;
}