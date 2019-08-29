#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct person{

    char name[51];
    char agency[51];
    int age;
    int priority;
    int order;

}person;

typedef struct agency{

    char nameAgency[51];
    int cashier;
    int numbPerson;

}agency;

agency initAgency(char nameAgency[51], int cashier){

    agency element;
    element.cashier = cashier;
    element.numbPerson = 0;
    strcpy(element.nameAgency, nameAgency);

    return element;
}

person initPerson(char nameAgency[51], char namePerson[51], int age, int password){

    person element;

    if(age < 60){
        element.priority = 0;
    }
    else{
        element.priority = 1;
    }

    element.order = password;
    strcpy(element.name, namePerson);
    strcpy(element.agency, nameAgency);

    return element;
}

void heapifyMax(person *root, uint32_t lenght, uint32_t index){
 
    person aux;
    
    uint32_t father = index;
    uint32_t left = 2*index + 1;
    uint32_t right = 2*index + 2;

    if(left < lenght && root[left].priority >= root[father].priority  ){
        if(root[left].order < root[father].order){
            father = left;

        }
        if(root[left].priority > root[father].priority){
            father = left;
        }
    }
    if(right < lenght && root[right].priority  >= root[father].priority ){
        if(root[right].order < root[father].order){
            father = right;

        }
        if(root[right].priority > root[father].priority){
            father = right;
        }
    }
    if(father != index){

        aux = root[index];
        root[index] = root[father];
        root[father] = aux;
        heapifyMax(root, lenght, father);
    }

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

    person* vectorPerson = (person*)malloc(numbPerson*sizeof(person));
    char c[1];

    for(int i = 0; i < numbPerson; i++){

        fscanf(input,"%c %50[^|]%*c %50[^|]%*c %d", c, nameAgency, namePerson, &age);
      
        for(index = 0; index < numbAgency; index++){
            if(!((strcmp(nameAgency, vectorAgencies[index].nameAgency)))){
                vectorAgencies[index].numbPerson++;
                break;
            }
        }

        vectorPerson[i] = initPerson(nameAgency, namePerson , age, vectorAgencies[index].numbPerson);

    }

    for (int i = numbPerson - 1; i >= 0; i--){

        heapifyMax(vectorPerson, numbPerson, i);
    }

    int aux;
    while(numbPerson > 0){
        for(int x = 0; x < numbAgency; x++){
            if(vectorAgencies[x].numbPerson > 0){
                fprintf(output,"%s:", vectorAgencies[x].nameAgency);
            }
            int aux = vectorAgencies[x].cashier;
            for(int f = 0; f < vectorAgencies[x].cashier; f++){
                for(int z = 0; z < numbPerson; z++){
                    if(strcmp(vectorAgencies[x].nameAgency, vectorPerson[z].agency) == 0){
                        vectorAgencies[x].numbPerson--;
                        aux--;
                        if(aux > 0 && vectorAgencies[x].numbPerson > 0){
                            fprintf(output,"%s,", vectorPerson[z].name);
                        }
                        else{
                            fprintf(output,"%s", vectorPerson[z].name);
                        }
                        
                        vectorPerson[z] = vectorPerson[numbPerson - 1];
                        vectorPerson[numbPerson - 1].priority = -2;
                        numbPerson--;

                        for (int i = numbPerson - 1; i >= 0; i--){

                            heapifyMax(vectorPerson, numbPerson, i);
                        }
                        break;

                    }
                }
            }
            if(numbPerson >0){
                fprintf(output,"\n");
            }
        }
    }

    fclose(input);
	fclose(output);

    return 0;
}
