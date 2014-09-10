#include "stdafx.h"
#include "test.h"

bool unit_test(const char* file_i, const char* file_o)
{
    FILE* fp1 = fopen(file_i, "r");
    FILE* fp2 = fopen(file_o, "r");
    if (!fp1 || !fp2)
        return false;
    int data1 = 0;
    int data2 = 0;
    while (!feof(fp1))
    {
        fscanf(fp1, "%05d", &data1);
        fscanf(fp2, "%05d", &data2);
        if (data1 != data2 && !feof(fp1))
        {
            int tmp = 0;
            fscanf(fp1, "%05d", &tmp);

            if (feof(fp1) && abs(data1 - data2) == 1)
            {
                fclose(fp1);
                fclose(fp2);
                return true;
            }
            fclose(fp1);
            fclose(fp2);
            return false;

        }
    }
    fclose(fp1);
    fclose(fp2);
    return true;
}
