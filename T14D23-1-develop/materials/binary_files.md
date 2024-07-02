# Binary files
Files on a computer can be stored in two ways:
* Text files - human-readable files, union of various characters.
* Binary files - files "understandable" by the computer. Representing a sequential set of bytes.

**Disadvantages of binary files** - special programs are needed to prepare the file. \
**Advantages of binary files** - direct access to data, the ability to position to any place in the file, reading data can be direct without using an array, data is stored in the same form as in RAM, no time is spent on conversion and no extra memory for storing a text copy, so when there is not enough RAM, you can use binary files instead of text files, you can simultaneously read and write to a binary file.

# Basic functions for working with binary files

| Function prototype   | Description |
| ----------- | ----------- |
| `FILE * fopen(const char * fname, const char * mode);`      | Opening a file, returns a pointer to a file descriptor. It is important what type of opening (mode) is specified. Returns null on error. |
| `int fclose(FILE *fp);`   | Closing a file        |
| `size_t fread(void * ptrvoid, size_t size, size_t count, FILE * filestream);`   | The function reads `count` elements of `size` bytes, from the stream, and stores it in the block of memory pointed by `ptrvoid`. The stream position indicator is incremented by the total number of bytes written. The return value is the total number of elements successfully read. |
| `size_t fwrite(const void * ptrvoid, size_t size, size_t count, FILE * filestream);`   | The function writes `count` elements of size `size` bytes, from the block of memory pointed by the `ptrvoid`. The stream position indicator is incremented by the total number of bytes written. Return value is the total number of elements that were successfully written.        |
| `int fseek(FILE * filestream, long int offset, int origin);`   | Moves the position pointer in the file stream by the number of the `offset` bytes relative to `origin` : `SEEK_SET` - Start of file, `SEEK_CUR` - Current position of file, `SEEK_END` - End of file       |
| `long int ftell(FILE * filestream);`   | Returns the number of bytes from the beginning of the file to the current position pointer of the file stream `filestream` |
| `void rewind (FILE * filestream);`   | Sets the internal file position indicator to the start position (beginning of the file).        |
| `int fflush(FILE * filestream);`   | If the stream was opened for writing (or if it was opened for updating and the last I/O was an output), any unwritten data in the output buffer is written to the file. If the argument is a null pointer, then the open file is cleared. In all other cases, the behavior depends on the specific implementation of the library. In some implementations, clearing a stream that is open for reading causes its input buffer to be cleared (but this is not standard behavior). Stream remains open after calling `fflush.`       |
