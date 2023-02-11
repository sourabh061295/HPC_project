
#include <iostream>

int main() 
{
    int tile_neighbours[4], external_tile_mask[4];
    int left, right, bottom, top;
    int t_xmin, t_xmax, t_ymin, t_ymax;
    int t_left, t_right, t_bottom, t_top;
	int chunk_x_cells = 480;
	int chunk_y_cells = 192;
    int global_left = 481;
    int global_bottom = 769;
    int tiles_per_chunk = 1;

	int chunk_mesh_ratio = (double) chunk_x_cells / (double) chunk_y_cells;

	int tile_x = tiles_per_chunk;
	int tile_y = 1;

	int split_found = 0; // Used to detect 1D decomposition
	for (int t = 1; t <= tiles_per_chunk; ++t) {
		if (tiles_per_chunk % t == 0) {
			int factor_x = tiles_per_chunk / (double) t;
			int factor_y = t;
			// Compare the factor ratio with the mesh ratio
			if (factor_x / factor_y <= chunk_mesh_ratio) {
				tile_y = t;
				tile_x = tiles_per_chunk / t;
				split_found = 1;
				break;
			}
		}
	}

	if (split_found == 0 ||
	    tile_y == tiles_per_chunk) { // Prime number or 1D decomp detected
		if (chunk_mesh_ratio >= 1.0) {
			tile_x = tiles_per_chunk;
			tile_y = 1;
		} else {
			tile_x = 1;
			tile_y = tiles_per_chunk;
		}
	}

	int chunk_delta_x = chunk_x_cells / tile_x;
	int chunk_delta_y = chunk_y_cells / tile_y;
	int chunk_mod_x = chunk_x_cells % tile_x;
	int chunk_mod_y = chunk_y_cells % tile_y;


	int add_x_prev = 0;
	int add_y_prev = 0;
	int tile = 0; // Used to index globals.chunk.tiles array

    std::cout << "============================" << std::endl;
	std::cout << "chunk_x_cells = "<< chunk_x_cells << "| chunk_y_cells = " << chunk_y_cells << std::endl;
	std::cout << "tile_x = " << tile_x << "| tile_y = " << tile_y << std::endl;
	std::cout << "chunk_delta_x = " << chunk_delta_x << "| chunk_delta_y = " << chunk_delta_y << std::endl;
	std::cout << "chunk_mod_x = " << chunk_mod_x << "| chunk_mod_y = " << chunk_mod_y << std::endl;
	std::cout << "============================" << std::endl;

	for (int ty = 1; ty <= tile_y; ++ty) {
		for (int tx = 1; tx <= tile_x; ++tx) 
        {
            std::cout << "\tty = " << ty << "| tx = " << tx << std::endl;
		    std::cout << "\ttile = " << tile << std::endl;
		    std::cout << "\t-------------------------" << std::endl;
			int add_x = 0;
			int add_y = 0;
			if (tx <= chunk_mod_x) add_x = 1;
			if (ty <= chunk_mod_y) add_y = 1;
            std::cout << "\tadd_x = " << add_x << "| add_y = " << add_y << std::endl;
            std::cout << "\tadd_x_prev = " << add_y_prev << "| add_y_prev = " << add_x_prev << std::endl;
            std::cout << "\t-------------------------" << std::endl;

			int left = global_left + (tx - 1) * chunk_delta_x + add_x_prev;
			int right = left + chunk_delta_x - 1 + add_x;
			int bottom = global_bottom + (ty - 1) * chunk_delta_y + add_y_prev;
			int top = bottom + chunk_delta_y - 1 + add_y;

            std::cout << "\tleft = " << left << std::endl;
            std::cout << "\tright = " << right << std::endl;
            std::cout << "\tbottom = " << bottom << std::endl;
            std::cout << "\ttop = " << top << std::endl;
            std::cout << "\t-------------------------" << std::endl;

			tile_neighbours[0] = tile_x * (ty - 1) + tx - 1;
			tile_neighbours[1] = tile_x * (ty - 1) + tx + 1;
			tile_neighbours[2] = tile_x * (ty - 2) + tx;
			tile_neighbours[3] = tile_x * (ty) + tx;


			// initial set the external tile mask to 0 for each tile
			for (int i = 0; i < 4; ++i) {
				external_tile_mask[i] = 0;
			}

			if (tx == 1) {
				tile_neighbours[0] = -1;
				external_tile_mask[0] = 1;
			}
			if (tx == tile_x) {
				tile_neighbours[1] = -1;
				external_tile_mask[1] = 1;
			}
			if (ty == 1) {
				tile_neighbours[2] = -1;
				external_tile_mask[2] = 1;
			}
			if (ty == tile_y) {
				tile_neighbours[3] = -1;
				external_tile_mask[3] = 1;
			}

            std::cout << "\ttile_left = " << tile_neighbours[0] << std::endl;
            std::cout << "\ttile_right = " << tile_neighbours[1] << std::endl;
            std::cout << "\ttile_bottom = " << tile_neighbours[2] << std::endl;
            std::cout << "\ttile_top = " << tile_neighbours[3] << std::endl;
            std::cout << "\t-------------------------" << std::endl;

			if (tx <= chunk_mod_x) add_x_prev = add_x_prev + 1;

			t_xmin = 1;
			t_xmax = right - left + 1;
			t_ymin = 1;
			t_ymax = top - bottom + 1;

            std::cout << "\tt_xmin = " << t_xmin  << std::endl;
            std::cout << "\tt_xmax = " << t_xmax  << std::endl;
            std::cout << "\tt_ymin = " << t_ymin  << std::endl;
            std::cout << "\tt_ymax = " << t_ymax << std::endl;
            std::cout << "\t-------------------------" << std::endl;

			tile = tile + 1;
            std::cout << "#####################################" << std::endl;
		}
		add_x_prev = 0;
		if (ty <= chunk_mod_y) add_y_prev = add_y_prev + 1;
	}

	return 0;
}