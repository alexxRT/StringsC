#ifndef SORT_H
#define SORT_H

int  str_cmp_begin (const void* str_param1, const void* str_param2);
int  str_cmp_end   (const void* str_param1, const void* str_param2);
void custm_qsort   (void* __base, size_t __nel, size_t __width, int (*cmp)(const void*, const void*));
void buble_sort    (void* __base, size_t __nel, size_t __width, int (*cmp)(const void*, const void*)) ;

void massiv_fprint (const str struct_str[], size_t size, const char* const file_name);
void massiv_print  (const str struct_str[], size_t size, const char* const param);

#endif
