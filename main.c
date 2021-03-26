#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "Shamir.h"
#include "argparse.h"


static const char *const usages[] = {
    "ShamirTool [options] [[--] args]",
    "ShamirTool [options]",
    NULL,
};


int main(int argc,const char** argv)
{
    uint32_t k = 0;
    int64_t secret = 0;
    uint32_t output_number = 0;
    int verbose = 0;
    int hide = 0;
    int decode = 0;
    char* points = NULL;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN(0, "hide", &hide, "Hide key",NULL,0,0),
        OPT_BOOLEAN(0, "decode", &decode, "Decode Shamir points",NULL,0,0),
        OPT_BOOLEAN('v', "verbose", &verbose, "More verbose output",NULL,0,0),
        OPT_INTEGER(0, "secret", &secret, "The number to hide",NULL,0,0),
        OPT_INTEGER('k', "key", &k, "Key number for Shamir",NULL,0,0),
        OPT_INTEGER(0, "output-point", &output_number, "Number of output point (from 0 to x)",NULL,0,0),
        OPT_STRING(0,"points",&points,"All points for Shamir decode (format : '3,1413.4,1514'",NULL,0,0),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "\nThis program is for create point with Shamir and resolv secret", "\nExample : \n\t./ShamirTool --points \"3,1415.4,1514\" -k 2 --decode\n\t./ShamirTool --secret 777 -k 2 --hide --output-point 5");
    argc = argparse_parse(&argparse, argc, argv);

    if(secret != 0 && k > 0 && hide)
    {
        shamir* s = sh_create(k,secret);

        if(verbose)
        {
            sh_print(s);
        }

        for(uint32_t i=1;i<output_number+1;i+=1)
        {
            double val = sh_compute_x(s,i);
            printf("[%u] = %.lf (%u,%.lf)\n",i,val,i,val);
        }
        sh_destroy(s);
    }else if(decode && points != NULL && k > 0)
    {
        char** tmp = malloc( k * sizeof(char*) );
        char *ptr = strtok(points, ".");
        for(uint32_t i=0;i<k;i+=1)
        {
            tmp[i] = malloc(50 * sizeof(char));
            snprintf(tmp[i],50,"%s",ptr);
            ptr = strtok(NULL,".");
            printf("[%d] = %s\n",i,tmp[i]);
        }

        printf("Secret : %.lf\n",sh_evaluate(k,tmp,k));
        
        for(uint32_t i=0;i<k;i+=1)
        {
            free(tmp[i]);
        }
        free(tmp);
    }
    else
    {
        argparse_usage(&argparse);
    }

    return 0;
}