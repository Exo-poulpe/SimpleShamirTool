#include "Shamir.h"


double _sh_greater_random(int64_t value)
{
    return (double)(rand() % (int64_t)pow(value,2) + value);
}

// Create and fill table with value
shamir* sh_create(uint16_t k,int64_t secret)
{
    shamir* s = malloc( 1 * sizeof(shamir));
    s->key_number = k;
    s->secret = secret;
    s->tab_size = k;
    s->table = malloc(s->tab_size * sizeof(double));
    s->table[0] = secret;
    for(uint32_t i=1;i<s->tab_size;i+=1){ s->table[i] = _sh_greater_random(s->secret); }
    return s;
}


void sh_destroy(shamir* s)
{
    s->key_number = 0;
    s->secret = INT64_MIN;
    s->tab_size = 0;
    free(s->table);
    s->table = NULL;
    free(s);
}


void sh_print(shamir* s)
{
    printf("Key number : %u\n",s->key_number);
    printf("Secret : %ld\n",s->secret);
    printf("Table size : %u\n",s->tab_size);
    printf("%.lf ",s->table[0]);
    for(uint32_t i=1;i<s->tab_size;i+=1)
    {
        printf("+ %.lfx^%u",s->table[i],i);
    }
    printf("\n");
}


double sh_evaluate(uint32_t k,char** points,uint32_t points_number)
{
    if(k > points_number){ return INT64_MIN; }

    double res = 0;
    double tmp = 1;
    // String type : 10,21478174716 => int(10)  int(21478174716)
    for(uint32_t i=0;i<points_number;i+=1)
    {
        uint32_t tmp_size = strlen(points[i]) + 1;
        char* tmp_str = malloc(tmp_size * sizeof(char));
        snprintf(tmp_str,tmp_size,"%s",points[i]);        

        int64_t pos = atol(strtok(tmp_str, ","));
        double value = atol(strtok(NULL, ","));

        for(uint32_t j=0;j<points_number;j+=1)
        {
            if(j==i){continue;}
            uint32_t tmp_size_2 = strlen(points[j]) + 1;
            char* tmp_str_2 = malloc(tmp_size_2 * sizeof(char));
            snprintf(tmp_str_2,tmp_size_2,"%s",points[j]); 

            // printf("%s\n",points[j]);
            int64_t pos2 = atol(strtok(tmp_str_2, ","));
            // (pos,value)
            // printf("(0-%ld)/(%ld-%ld)\n",pos2,pos,pos2);
            tmp *= (double)(0-pos2)/(pos-pos2);
            free(tmp_str_2);
        }

        tmp *= value;
        // printf("tmp : %.lf\n",tmp);
        res += tmp;
        // printf("res : %.lf\n",res);
        tmp = 1;
        free(tmp_str);
    }

    return res;
}


double sh_compute_x(shamir* s, uint32_t x)
{
    double res = s->table[0];
    for(uint32_t i=1;i<s->tab_size;i+=1)
    {
        res += s->table[i] * x;
    }
    return res;
}