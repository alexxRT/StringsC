#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "../lib/Memory.h"
#include "../lib/Text.h"


//The most IMPORTANT function here :)))--//

int min (int a, int b) {
    return b < a ? b : a;
}
//---------------------------------------//




//-------------------------------Functions that prepare strings before comparison------------------------------//

static const char* str_prepare_begin (const char* const str)
{
    assert (str != NULL);
    int i = 0;

    for (; str[i] != '\0'; i++)
    {
        if (isalpha(str[i])) {
    
            assert (isalpha(str[i]));
            return str + i;
        }
    }
    
    return str + i;
}

static int str_prepare_end (const str* str_struct) 
{
    int i = str_struct -> len - 1;
    for (; i >= 0; i --)
    {
        if (isalpha(str_struct -> string[i]))
        {
            return i;
        }
    }

    return i;
}

//----------------------------------------------------------------------------------------------------------//



//----------------------------------------------CMP functions-----------------------------------------------//

//Support sorting strings from the beginning
int str_cmp_begin (const void* str_param1, const void* str_param2)
{
    const str* str1 = (const str*) str_param1;
    const str* str2 = (const str*) str_param2;

    #if DEBUG_STAT == 1
    {
    printf ("\n\nFIRST STRING\n");
    info_print (str1);
    printf ("\n\nSECOND STRING\n");
    info_print (str2);
    }
    #endif

    assert (str1 != NULL);
    assert (str2 != NULL);

    const char* s1 = str1 -> string;
    const char* s2 = str2 -> string;

    s1 = str_prepare_begin (s1); assert (str1 != NULL);
    s2 = str_prepare_begin (s2); assert (str2 != NULL);

    if (s1[0] == '\0' || s2[0] == '\0')
    {
        int diff = s1[0] - s2[0];

        return -diff;
    }

    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i ++)
    {
        if (s1[i] < s2[i])
        {
            return -1;
        }
        else if (s1[i] > s2[i])
        {
            return 1;
        }
    }

    return 0;
}

//Support sorting strings from the end

int str_cmp_end (const void* str_param1, const void* str_param2)
{

    const str* str1 = (const str*) str_param1;
    const str* str2 = (const str*) str_param2;

    assert (str1 != NULL);
    assert (str2 != NULL);

    const char* s1 = str1 -> string; assert (s1 != NULL);
    const char* s2 = str2 -> string; assert (s2 != NULL);

    #if DEBUG_STAT == 1
    {
        info_print (str1);
        info_print (str2);
    }
    #endif

    int begin1 = str_prepare_end (str1);
    int begin2 = str_prepare_end (str2);

    if (s1[begin1] == '\0' || s2[begin2] == '\0')
    {
        int diff = s1[begin1] - s2[begin2];
        return -diff;
    }

    int len = min (begin1, begin2);

    while (len >= 0)
    {
        if (s1[begin1] < s2[begin2])
        {
            return -1;
        }
        else if (s1[begin1] > s2[begin2])
        {
            return 1;
        }

        len --;
        begin1 --;
        begin2 --;
    }

    return 0;
}

// -----------------------------------------------------------------------------------------------------//




//-------------------------------------Sorting functions------------------------------------------------//

//This self written qsort is based on two different algorithms 
//1) Hoaro sort algorithm (by default)
//2) Lomuto sort algorithm (so slow, and too close to the simple buble sort)

static void inside_Hoare_sort (void* base, void* extra_buf, size_t nel, size_t width, int (*cmp)(const void*, const void*));
static void inside_Lomuto_sort (void* base, size_t nel, size_t width, int (*cmp)(const void*, const void*));
static void mem_swope (void* buf1, void* buf2, size_t mut_size);

void custm_qsort (void* __base, size_t __nel, size_t __width, int (*cmp)(const void*, const void*))
{
    assert (__base != NULL);

    void* extra_buf = CALLOC (__width, void);
    assert (extra_buf != NULL);

    inside_Hoare_sort  (__base, extra_buf, __nel, __width, cmp);
    //inside_Lomuto_sort (__base, __nel, __width, cmp);
    
    FREE (extra_buf);
}

static void inside_Hoare_sort (void* base, void* extra_buf, size_t nel, size_t width, int (*cmp)(const void*, const void*))
{
    if (nel <= 1) return;

    if (nel == 2) 
    {
        if (cmp (base, base + width) > 0)
        {
            mem_swope (base, base + width, width);
        }
        return;
    } 

    if (nel == 3)
    {
        void* max_elem = NULL;

        if (cmp (base, base + width) > 0) max_elem = base;

        else max_elem = base + width;

        if (cmp (max_elem, base + 2 * width) > 0) mem_swope (max_elem, base + 2 * width, width);

        if (cmp (base, base + width) > 0) mem_swope (base, base + width, width);

        return;
    }

    assert (base != NULL);
    assert (extra_buf != NULL);

    srand (time(NULL));
    size_t rand_index = rand() % (nel - 1);

    assert (rand_index < nel);
    memcpy (extra_buf, base + (rand_index * width), width);

    int left = 0;
    int right = nel - 1;

    do 
    {

    while (cmp (base + (left * width) , extra_buf) < 0) left  ++;
    while (cmp (base + (right * width), extra_buf) > 0) right --;
    
        if (left <= right)
        {
            mem_swope (base + (left * width), base + (right * width), width);

            left ++;
            right --;
        }

    }
    while (left <= right);


    inside_Hoare_sort (base, extra_buf, right + 1, width, cmp);

    if (left - right == 1)
        inside_Hoare_sort (base + left * width, extra_buf, nel - right - 1, width, cmp);
    else 
        inside_Hoare_sort (base + left * width, extra_buf, nel - right - 2, width, cmp);

}


static void inside_Lomuto_sort (void* base, size_t nel, size_t width, int (*cmp)(const void*, const void*))
{
    if (nel <= 1) return;

    assert (base != NULL);

    int position = 0;
    void* base_elem = base + (nel - 1) * width;


    for (int i = 0; i < nel - 1; i ++)
    {
        if (cmp (base + width * i, base_elem) < 0)
        {
            mem_swope (base + width * position, base + width * i, width);

            position ++;
        }
    }

    mem_swope (base + width * (nel - 1), base + width * position , width);
  
    inside_Lomuto_sort (base                         , position          , width, cmp);
    inside_Lomuto_sort (base + width * (position + 1), nel - position - 1, width, cmp);
}

//Simple buble sort, also works :)

static int single_iteration (void* base, void* swope, size_t __nel, size_t __width, int (*cmp)(const void*, const void*));

void buble_sort (void* __base, size_t __nel, size_t __width, int (*cmp)(const void*, const void*)) 
{
    void* swope = CALLOC (__width, void);
    assert (swope != NULL); 

    while (single_iteration(__base, swope, __nel, __width, cmp))
        ; 

    FREE (swope);
}

static int single_iteration (void* base, void* swope, size_t __nel, size_t __width, int (*cmp)(const void*, const void*))
{
    int swope_counter = 0;

    for (int i = 0; i < __nel - 1; i ++)
    {

        #if DEBUG_STAT == 1
        {
        printf ("\n\nBEFORE SWOPE:\n");

        printf ("\n\n[%d] elem\n", i);
        info_print ((str*)(base + __width * i), stderr);

        printf ("\n\n[%d] elem\n", i + 1);
        info_print ((str*)(base + __width * (i + 1)), stderr);
        }
        #endif

        int result = cmp (base + __width*i, base + __width*(i + 1));
        
        if (result > 0) 
        {

            mem_swope (base + __width*(i + 1), base + i*__width, __width);
    
            #if DEBUG_STAT == 1
            {
            printf ("\n\nAFTER SWOPE:\n");

            printf ("\n\n[%d] elem\n", i);
            info_print ((str*)(base + __width * i), stderr);

            printf ("\n\n[%d] elem\n", i + 1);
            info_print ((str*)(base + __width * (i + 1)), stderr);
            }
            #endif

            swope_counter ++;

        }    
    }

    return swope_counter;

}


//This function helps to switch two memory blocks effectivly
static void mem_swope (void* buf1, void* buf2, size_t mut_size)
{
    assert (buf1 != NULL);
    assert (buf2 != NULL);

    short const int ll_bytes = sizeof (long long int); // 8 bytes
    short const int l_bytes  = sizeof (int); // 4 bytes
    short const int s_bytes  = sizeof (short int); // 2 bytes
    short const int c_bytes  = sizeof (char); // 1 byte

    long long int *buf1_ll = (long long int *)(buf1);
    long long int *buf2_ll = (long long int *)(buf2);
    int pos = 0;

    while (mut_size >= ll_bytes)
    {
        long long int temp = 0;
        temp = buf1_ll[pos];
        buf1_ll[pos] = buf2_ll[pos];
        buf2_ll [pos] = temp;

        pos ++;
        mut_size -= ll_bytes;
    }

    long int *buf1_l = (long int *)(buf1);
    long int *buf2_l = (long int *)(buf2);

    while (mut_size >= l_bytes)
    {
        long int temp = 0;
        temp = buf1_l[pos];
        buf1_l [pos] = buf2_l [pos];
        buf2_l [pos] = temp;

        pos ++;
        mut_size -= l_bytes;
    }

    short int *buf1_s = (short int*)buf1_l;
    short int *buf2_s = (short int*)buf2_l;

    while (mut_size >= s_bytes)
    {
        short int temp = 0;
        temp = buf1_s[pos];
        buf1_s [pos] = buf2_s [pos];
        buf2_s [pos] = temp;

        pos ++;
        mut_size -= s_bytes;
    }

    char *buf1_c = (char*)buf1_s;
    char *buf2_c = (char*)buf2_s;

    while (mut_size >= s_bytes)
    {
        char temp = 0;
        temp = buf1_c[pos];
        buf1_c [pos] = buf2_c [pos];
        buf2_c [pos] = temp;

        pos ++;
        mut_size -= c_bytes;
    }
}

//-------------------------------------------------------------------------------------------------------//

//---------------------------------------Functions for strings output------------------------------------//

//For seporate string debug info 
static void info_print (const str* str, FILE* file)
{
    fprintf (file, "  struct address - [%p]\n", str);

    if (!str) 
    {
        return;
    }

    fprintf (file, "  string address - [%p] string len - [%lu] ", str -> string, str -> len);
    fprintf (file, "  string itself [%s]\n", str -> string);
    fprintf (file, "\n");
}


void massiv_fprint (const str struct_str[], size_t size, const char* file_name)
{
    FILE* output_file = fopen(file_name, "w");
    assert (output_file != NULL);

    for (int i = 0; i < size; i ++)
    {   
        if (struct_str[i].string[0] != '\0')
            fprintf (output_file, "%d  [%s]\n", i, struct_str[i].string);
    }

    fclose (output_file);
}

void massiv_print (const str struct_str[], size_t size, const char* const param)
{
    printf ("\n%s:\n\n", param);

    for (int i = 0; i < size; i ++)
    {
        info_print (struct_str + i, stderr);
    }

    printf ("%s ended\n\n", param);
} 


//----------------------------------------------------------------------------------------------------//