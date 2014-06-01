//BETTER file_get_contents than any other fuck
const char * file_get_contents(char *filename)
{
char * buffer = 0;
long length;
FILE * f = fopen (filename, "rb");

if (f)
{
fseek (f, 0, SEEK_END);
length = ftell (f);
fseek (f, 0, SEEK_SET);
buffer = malloc (length);
if (buffer)
{
fread (buffer, 1, length, f);
}
fclose (f);
}
else
{
printf("Idk but it seems like something went wrong....\n");
}
if (buffer)
{
return buffer;
}
else
{
printf("Idk but it seems like something went wrong....\n");
}
}
