#ifndef FILE_GET_CONTENTS_H_INCLUDED
#define FILE_GET_CONTENTS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
extern int file_get_contents(const char *filePath, char **outputBuffer, unsigned long *outLength);
#ifdef __cplusplus
}
#endif

#endif // FILE_GET_CONTENTS_H_INCLUDED
