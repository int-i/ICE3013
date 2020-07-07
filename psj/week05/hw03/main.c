#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char chunk_id[5];
    int chunk_size;
    char format[5];
    char subchunk1_id[5];
    int subchunk1_size;
    short audio_format;
    short num_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char subchunk2_id[5];
    int subchunk2_size;

    int fd = open("swvader03.wav", O_RDONLY);
    chunk_id[read(fd, chunk_id, 4)] = '\0';
    read(fd, &chunk_size, 4);
    format[read(fd, format, 4)] = '\0';
    subchunk1_id[read(fd, subchunk1_id, 4)] = '\0';
    read(fd, &subchunk1_size, 4);
    read(fd, &audio_format, 2);
    read(fd, &num_channels, 2);
    read(fd, &sample_rate, 4);
    read(fd, &byte_rate, 4);
    read(fd, &block_align, 2);
    read(fd, &bits_per_sample, 2);
    subchunk2_id[read(fd, subchunk2_id, 4)] = '\0';
    read(fd, &subchunk2_size, 4);
    close(fd);

    FILE* stream = fopen("sw2-wav.txt", "w");
    fprintf(stream, "Chunk ID: %s\n", chunk_id);
    fprintf(stream, "Chunk Size: %d\n", chunk_size);
    fprintf(stream, "Format: %s\n", format);
    fprintf(stream, "Subchunk1 ID: %s\n", subchunk1_id);
    fprintf(stream, "Subchunk1 Size: %d\n", subchunk1_size);
    fprintf(stream, "Audio Format: %d\n", audio_format);
    fprintf(stream, "Num Channels: %d\n", num_channels);
    fprintf(stream, "Sample Rate: %d\n", sample_rate);
    fprintf(stream, "Byte Rate: %d\n", byte_rate);
    fprintf(stream, "Block Align: %d\n", block_align);
    fprintf(stream, "Bits per Sample: %d\n", bits_per_sample);
    fprintf(stream, "Subchunk2 ID: %s\n", subchunk2_id);
    fprintf(stream, "Subchunk2 Size: %d\n", subchunk2_size);
    fclose(stream);
    return 0;
}
