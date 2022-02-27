/*************************************************************************
    > File Name: hw0.c
    > Author: Eric chen
    > Mail: 90996066er@gmail.com
    > Created Time: 2022-02-15
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
//#include <time.h>

const int MAXDIGIT = 1000;

struct Large_int{
    int num[MAXDIGIT];
};

void init(struct Large_int *raw);
void input(const char inputs[], struct Large_int*);
void swap(struct Large_int*,struct Large_int*);
void copy(const struct  Large_int*,struct Large_int*);
void divide_2(struct Large_int *input);
struct Large_int* multi_2( struct Large_int*,int k);
int former_bigger(const struct Large_int*,const struct Large_int*);
int is_even(const struct Large_int*);
int is_zero(const struct Large_int*);
struct Large_int* minus(const struct Large_int*,const struct Large_int* );
struct Large_int* gcd(struct Large_int*,struct Large_int*);
void print(const struct Large_int*);

int main(int argc,char *argv[]){
    //clock_t timestart,timeend;

    char input1[MAXDIGIT] = {0};
    char input2[MAXDIGIT] = {0};
    struct Large_int *i1 = (struct Large_int*)malloc(sizeof(struct Large_int));
    struct Large_int *i2 = (struct Large_int*)malloc(sizeof(struct Large_int));
    //struct Large_int i1;
    //struct Large_int i2;
    init(i1);
    init(i2);
    //init(&i1);
    //init(&i2);
    scanf("%s %s",input1,input2);
    //timestart = clock();
    input(input1,i1);
    input(input2,i2);
    //input(argv[1],i1);
    //input(argv[2],i2);
    struct Large_int* ptr;
    //ptr = gcd(&i1,&i2);
    ptr = gcd(i1,i2);
    print(ptr);
    free(i1);
    free(i2);
    free(ptr);
    //timeend = clock();
    //double diff = (double)(timeend - timestart);
    //printf("\nspend %f sec\n",diff/CLOCKS_PER_SEC);

    return 0 ;
}

void input(const char inputstring[],struct Large_int *inits){
    int i = (int)strlen(inputstring);
    int temp;
    char tempp ;
    for (int j = i - 1;j >= 0; j-- ){
        tempp = inputstring[j];
        temp =  atoi(&tempp);
        inits->num[MAXDIGIT - i + j] = temp;
    }
}
void init(struct Large_int *raw){
    for(int i = 0; i< MAXDIGIT ;i++){
        raw->num[i] = 0;
    }
}

void swap(struct Large_int* n,struct Large_int* m){
    int temp;
    for(int i = 0; i < MAXDIGIT ;i++){
        temp = n->num[i];
        n->num[i] = m->num[i];
        m->num[i] = temp;
    }
}

void copy(const struct Large_int* n ,struct Large_int* m){
    for(int i = 0 ; i < MAXDIGIT; i++){
        m->num[i] =  n->num[i];
    }
}

int former_bigger(const struct Large_int *former,const struct Large_int *later){
    for(int i = 0 ; i < MAXDIGIT ;i++){
        if(former->num[i] > later->num[i]){
            return 1;//bigger
        }else if(former->num[i] < later->num[i]){
            return 0;//smaller
        }else{
            continue;
        }
    }
    return 0; //same
}

int is_even(const struct Large_int* input){
    if(input->num[MAXDIGIT-1]%2 == 0)
        return 1;
    else
        return 0;
}
int is_zero(const struct Large_int* input){
    for(int i = 0; i < MAXDIGIT ;i++){
        if(input->num[i] != 0)
            return 0;
    }
    return 1;
}

void divide_2(struct Large_int *input){
    int temp_before=0,temp_after;
    for(int i = 0; i < MAXDIGIT ;i++){
        temp_after = (input->num[i] + (10*temp_before))%2;
        input->num[i] = (input->num[i] + (10*temp_before))/2;
        temp_before = temp_after;
    }
}

struct Large_int* minus(const struct Large_int *input1, const struct Large_int *input2){
    struct Large_int* ptr = malloc(sizeof(struct Large_int));
    copy(input1,ptr);
    for(int i = MAXDIGIT - 1;i >= 0; i--){
        if(ptr->num[i] >= input2->num[i]) // 不需借位
            ptr->num[i] -= input2->num[i];

        else if(ptr->num[i] < input2->num[i]){ //需借位
            ptr->num[i] = 10 + ptr->num[i] - input2->num[i]; //因為a > b所以必無負數
            for(int j = i - 1 ; j >= 0; j--){
                if(j != 0){
                    ptr->num[j] -= 1;
                    break;
                }
                else {
                    ptr->num[j] = 9;
                }
            }
        }
    }

    return ptr;
}

struct Large_int* multi_2( struct Large_int* input,int k){
    struct Large_int* ptr = malloc(sizeof(struct Large_int));
    int temp_before = 0,temp_after;
    copy(input,ptr);
    for(int i = 0; i < k ;i++){
        for(int j = MAXDIGIT - 1;j >= 0;j--){
            temp_after = (ptr->num[j]*2+temp_before) / 10;
            ptr->num[j] = (ptr->num[j]*2+temp_before) % 10;
            temp_before = temp_after;
        }
    }
    return ptr;
}

void print(const struct Large_int* input){
    int status = 0;
    for(int i = 0; i< MAXDIGIT; i++){
        if(input->num[i] != 0 || status)
            status = 1;
        if(status)
            printf("%d",input->num[i]);
    }
}

struct Large_int* gcd(struct Large_int* n, struct Large_int* m){
    int i = 0;
    void* ptr;
    //struct Large_int* trash_can;
    if (former_bigger(n,m)){
        swap(m,n);
    }
    while(!is_zero(n) && !is_zero(m)) {
        if (is_even(n) && is_even(m)) {
            i++;
            divide_2(n);
            divide_2(m);
        }else if (is_even(n)){
            divide_2(n);
        }else if(is_even(m)){
            divide_2(m);
        }
        if (former_bigger(n,m)){
            swap(m,n);
        }
        ptr = minus(m,n);
        m = ptr;
        assert(m == ptr);
        free(ptr);
        assert(m == ptr);
        //ptr = NULL;
        //free(trash_can);
    }
    return multi_2(n,i);
}

