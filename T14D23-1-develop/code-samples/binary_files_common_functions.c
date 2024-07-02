// Function of reading a record of a given type from a file by its serial number.
struct my_struct read_record_from_file(FILE *pfile, int index)
{
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index)
{
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

// Function of mutual transfer of two records in the file by their indexes.
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2)
{
    // Read both records from file to variables
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile)
{
    int size = 0;
    fseek(pfile, 0, SEEK_END);    // Move the position pointer to the end of the file.
    size = ftell(pfile);          // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);                // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}

// Function to get count of records in file
int get_records_count_in_file(FILE *pfile)
{
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}
