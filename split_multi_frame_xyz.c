/*  Split multi-frame xyz files into individual files.  */

# include <stdio.h>
# include <string.h>

int main(int argc, char const *argv[])
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    char if_name[BUFSIZ + 1] = "";
    char of_name[BUFSIZ + 1] = "";
    unsigned int if_name_len = 0;
    FILE *if_p = NULL;
    FILE *of_p = NULL;
    unsigned int num_geoms = 1;
    unsigned int num_atoms = 0;
    char buf[BUFSIZ + 1] = "";
    unsigned int const appendix_len = strlen(".xyz");
    unsigned int const split_index_length = 8;
    unsigned int const symbol_len = strlen("_");
    char print_format[6] = "";
    char screen_hint_format[30] = "";

    if (argc == 1)
    {
        puts("Usage: split_multi_frame.exe [filename2] [filename2] [filename3] ...");
        puts("Split multi-frame xyz files into individual files.");
        return 0;
    }
    sprintf(print_format, "%%0%uu", split_index_length);
    sprintf(screen_hint_format, "Generating for frame %%%uu\r", split_index_length);
    for (i = 1; i < argc; ++ i)
    {
        strcpy(if_name, argv[i]);
        if_name_len = strlen(if_name);
        if (strcmp(if_name + if_name_len - appendix_len, ".xyz"))
            continue;
        strcpy(of_name, if_name);
        strcpy(of_name + if_name_len - appendix_len, "_");
        if_p = fopen(if_name, "rt");
        if (! if_p)
            continue;
        printf("Dealing %s ...\n", if_name);
        j = 1;
        while (! feof(if_p))
        {
            sprintf(of_name + if_name_len - appendix_len + symbol_len, print_format, j);
            strcpy(of_name + if_name_len - appendix_len + symbol_len + split_index_length, ".xyz");
            fgets(buf, BUFSIZ, if_p);
            if (sscanf(buf, "%u", & num_atoms) != 1)
                break;
            of_p = fopen(of_name, "wt");
            fputs(buf, of_p);
            fgets(buf, BUFSIZ, if_p);
            fputs(buf, of_p);
            for (k = 0; k < num_atoms; ++ k)
            {
                fgets(buf, BUFSIZ, if_p);
                fputs(buf, of_p);
            }
            fclose(of_p);
            of_p = NULL;
            printf(screen_hint_format, j);
            ++ j;
        }
        puts("");
        fclose(if_p);
        if_p = NULL;
    }

    return 0;
}

