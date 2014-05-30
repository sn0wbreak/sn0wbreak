
int file_exists(const char filename[]) {
    struct stat stbuf;
    if (stat(filename, &stbuf) == -1) {
        return (0);
    }
    return (1);
}

