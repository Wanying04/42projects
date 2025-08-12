void sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i = 0;
    unsigned int j;
    unsigned int min_idx;
    int tmp;

    while (i < size - 1)
    {
        min_idx = i;
        j = i + 1;
        while (j < size)
        {
            if (tab[j] < tab[min_idx])
                min_idx = j;
            j++;
        }
        if (min_idx != i)
        {
            tmp = tab[i];
            tab[i] = tab[min_idx];
            tab[min_idx] = tmp;
        }
        i++;
    }
}