#include "../lib/Text.h"
#include "../lib/StringsSort.h"

int main ()
{
    TEXT text = {};


    TxtCreate (&text, "./Tests/Test_1.txt", "r");

    custm_qsort  (text.str_array, text.num_of_str, sizeof(text.str_array[0]), str_cmp_begin);
    massiv_print (text.str_array, text.num_of_str, "TEST_1");

    TxtDestroy (&text);



    TxtCreate (&text, "./Tests/Test_2.txt", "r");

    custm_qsort   (text.str_array, text.num_of_str, sizeof(text.str_array[0]), str_cmp_begin);
    massiv_fprint (text.str_array, text.num_of_str, "./Tests/Sorted_Hamlet.txt");

    TxtDestroy (&text);


    return 0;
}