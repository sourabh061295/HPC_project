#include <iostream>
#define NUM_FIELDS 4

int main() 
{
    int tile = 1;
	int tiles[tile];
    int t_bottom = -1;
    int chunk_bottom = -1;
    int depth = 2;
    int y_inc;
    int field_type = 1;
    int left_right_offset = 5790;
    int xmin = 1;
    int xmax = 490;
    int ymin = 1;
    int ymax = 192;
    int right_snd_buffer[965 * 20];
    int field[482][194];

	int t_offset = (t_bottom - chunk_bottom) * depth;

    // These array modifications still need to be added on, plus the donor data location changes as in update_halo
    if (field_type == 1) y_inc = 0;
    if (field_type == 2) y_inc = 1;
    if (field_type == 3) y_inc = 0;
    if (field_type == 4) y_inc = 1;

    // DO k=y_min-depth,y_max+y_inc+depth
    // Perform double loop from 0:198
    for(int y = ymin - depth + 1; y < ymax + y_inc + depth + 2; ++y)
    {
        for (int j = 0; j < depth; ++j) 
        {
            int index = left_right_offset + t_offset + j + (y + depth - 1) * depth;
            right_snd_buffer[index] = field[xmin + 1 + j][y];
        }
    }
    return 0;
}