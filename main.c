int main(int argc, char **argv)
{
    if (argc >= 5) 
    {
        argv++;
        pipex(argv, argc - 1);
    }
    return (0);
}