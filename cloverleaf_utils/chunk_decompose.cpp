#include <iostream>

int main()
{
	int chunk_neighbours[4];
	int left, right, bottom, top;
	int number_of_chunks = 10;
	int x_cells = 960;
	int y_cells = 960;

	// 2D Decomposition of the mesh

	double mesh_ratio = (double)x_cells / (double)y_cells;

	int chunk_x = number_of_chunks;
	int chunk_y = 1;

	int split_found = 0; // Used to detect 1D decomposition

	double factor_x, factor_y;

	for (int c = 1; c <= number_of_chunks; ++c)
	{
		if (number_of_chunks % c == 0)
		{
			factor_x = number_of_chunks / (double)c;
			factor_y = c;
			// Compare the factor ratio with the mesh ratio
			if (factor_x / factor_y <= mesh_ratio)
			{
				chunk_y = c;
				chunk_x = number_of_chunks / c;
				split_found = 1;
				break;
			}
		}
	}

	if (split_found == 0 || chunk_y == number_of_chunks)
	{
		if (mesh_ratio >= 1.0)
		{
			chunk_x = number_of_chunks;
			chunk_y = 1;
		}
		else
		{
			chunk_x = 1;
			chunk_y = number_of_chunks;
		}
	}

	int delta_x = x_cells / chunk_x;
	int delta_y = y_cells / chunk_y;
	int mod_x = x_cells % chunk_x;
	int mod_y = y_cells % chunk_y;

	int add_x_prev = 0;
	int add_y_prev = 0;
	int cnk = 1;

	std::cout << "============================" << std::endl;
	std::cout << "x_cells = " << x_cells << "| y_cells = " << y_cells << std::endl;
	std::cout << "chunk_x = " << chunk_x << "| chunk_y = " << chunk_y << std::endl;
	std::cout << "delta_x = " << delta_x << "| delta_y = " << delta_y << std::endl;
	std::cout << "mod_x = " << mod_x << "| mod_y = " << mod_y << std::endl;
	std::cout << "============================" << std::endl;

	for (int cy = 1; cy <= chunk_y; ++cy)
	{
		for (int cx = 1; cx <= chunk_x; ++cx)
		{
			std::cout << "\tcy = " << cy << "| cx = " << cx << std::endl;
			std::cout << "\tcnk = " << cnk << std::endl;
			std::cout << "\t-------------------------" << std::endl;
			int add_x = 0;
			int add_y = 0;
			if (cx <= mod_x)
				add_x = 1;
			if (cy <= mod_y)
				add_y = 1;
			std::cout << "\tadd_x = " << add_x << "| add_y = " << add_y << std::endl;
			std::cout << "\tadd_x_prev = " << add_y_prev << "| add_y_prev = " << add_x_prev << std::endl;
			std::cout << "\t-------------------------" << std::endl;

			left = (cx - 1) * delta_x + 1 + add_x_prev;
			right = left + delta_x - 1 + add_x;
			bottom = (cy - 1) * delta_y + 1 + add_y_prev;
			top = bottom + delta_y - 1 + add_y;

			std::cout << "\tleft = " << left << std::endl;
			std::cout << "\tright = " << right << std::endl;
			std::cout << "\tbottom = " << bottom << std::endl;
			std::cout << "\ttop = " << top << std::endl;
			std::cout << "\t-------------------------" << std::endl;

			chunk_neighbours[0] = chunk_x * (cy - 1) + cx - 1;
			chunk_neighbours[1] = chunk_x * (cy - 1) + cx + 1;
			chunk_neighbours[2] = chunk_x * (cy - 2) + cx;
			chunk_neighbours[3] = chunk_x * (cy) + cx;

			if (cx == 1)
				chunk_neighbours[0] = -1;
			if (cx == chunk_x)
				chunk_neighbours[1] = -1;
			if (cy == 1)
				chunk_neighbours[2] = -1;
			if (cy == chunk_y)
				chunk_neighbours[3] = -1;

			std::cout << "\tchunk_left = " << chunk_neighbours[0] << std::endl;
			std::cout << "\tchunk_right = " << chunk_neighbours[1] << std::endl;
			std::cout << "\tchunk_bottom = " << chunk_neighbours[2] << std::endl;
			std::cout << "\tchunk_top = " << chunk_neighbours[3] << std::endl;
			std::cout << "\t-------------------------" << std::endl;

			if (cx <= mod_x)
				add_x_prev = add_x_prev + 1;

			cnk = cnk + 1;
			std::cout << "#####################################" << std::endl;
		}
		add_x_prev = 0;
		if (cy <= mod_y)
			add_y_prev = add_y_prev + 1;
	}
	return 0;
}