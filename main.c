int main(int argc, char **argv)
{
    if (argc >= 5) 
    {
        if (strcmp(argv[1], "here_doc") == 0)
            printf("here_doc");
        else 
        {
            argv++;
            pipex(argv, argc - 1);
        }
    }
    return (0);
}