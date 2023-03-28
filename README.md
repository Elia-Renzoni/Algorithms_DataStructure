# Algorithms and Data Structure 
> * Exercises of Algorithms and Data Structure Teaching. University of Urbino - Bachelor's Degree in Applied Computer Science
> * Sequentail and Deterministic Algorithms. 

## Array Algorithms > 
| Search Algorithms | Sort Algorithms |
|-------------------|-----------------|
| Linear Search     | Insert Sort     |
| Binary Search     | Select Sort     |
|                   | Bubble Sort     |
|                   | Merge Sort      |
|                   | Quick Sort      |
|                   | Heap Sort       |
|                   | Counting Sort   |
|                   | Radix Sort      |
|                   | Bucket Sort     |

* Linear Search : 
```C
int linear_research(int array[], int num_element, int value) {

    int index_loop;

    for (index_loop = 0; 
            (index_loop < num_element && array[index_loop] != value);
         index_loop++) {}

    return ((index_loop < num_element)? 
                        index_loop : NOT_FOUND);

}
```
* Binary Search : 
```C
int binary_research(int array[], int num_element, int value_s) {

    int index_sx,
        index_dx,
        index_mx;

    for (index_sx = 0, index_dx = num_element - 1, index_mx = (index_sx + index_dx) / 2;
            ((index_sx < index_dx) && (array[index_mx] != value_s));
         index_mx = (index_sx + index_mx) / 2)

         if (array[index_mx] > value_s)
            index_dx = index_mx - 1;
         else
            index_sx = index_mx + 1;

    return ((index_sx < index_dx)? 
                    index_mx : NOT_FOUND);
    
}
```
* Insert Sort : 
```C
void insertsort(int array[], int numero_elementi) {

    int value_ins,
        f_index,
        s_index;
    
    for (f_index = 1; (f_index < numero_elementi); f_index++) {

        for (value_ins = array[f_index], s_index = f_index - 1;
                ((s_index >= 0) && (array[s_index] > value_ins));
            s_index--)
            array[s_index + 1] = array[s_index];
        
        if (s_index + 1 != f_index)
            array[s_index + 1] = value_ins;
    }
}
```
* Select Sort : 
```C
void selectsort(int array[], int num_of_element) {

    int min_value,
        index_min_value,
        ex_index,
        in_index;

    for (ex_index = 0; (ex_index < num_of_element - 1); ex_index++) {

        for (min_value = array[ex_index], index_min_value = ex_index, in_index = ex_index + 1;
                (in_index < num_of_element);
             in_index++)

            if (array[in_index] < min_value) {
                min_value = array[in_index];
                index_min_value = in_index;
            }

        if (index_min_value != ex_index) {
            array[index_min_value] = array[ex_index];
            array[ex_index] = min_value;
        }
    }

}
```
* Bubble Sort : 
```C
/**
 * @brief bubblesort algorithm => T(n) = O(n^2)
 * 
 */
void bubblesort(int array[], int num_elements) {

    int tmp, i, j;

    for (i = 1; (i < num_elements); i++) {

        for (j = num_elements - 1; (j >= i); j--)
        
            if (array[j] < array[j - 1]) {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }

    }

}
```

## List Algorithms > 

