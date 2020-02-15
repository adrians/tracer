#include <stdio.h>

int main(){
    printf("{\"data\": [\n");
    for (int i = 0; i < 4000; i = i+10){

        int voltage = i;
        int current = voltage*10;

        if(i != 0){
                printf(",");
        }
        printf("[%d.%03d, %d.%03d]\n",
                        voltage/1000,
                        voltage%1000,
                        current/1000,
                        current%1000
        );
    }
    printf("]}\n");
    return 0;
}
