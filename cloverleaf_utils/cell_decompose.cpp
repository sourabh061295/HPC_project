#include <iostream>

int main()
{
    int cell_neighbours[25][4];
    int external_cell_mask[25][4];
    int x_cells = 5;
    int y_cells = 5;
    int total_cells = x_cells * y_cells;
    int delta_x = x_cells;
    int delta_y = y_cells;
    int c_left, c_right, c_bottom, c_top;

    std::cout << "============================" << std::endl;
    std::cout << "x_cells = " << x_cells << "| y_cells = " << y_cells << std::endl;
    std::cout << "total_cells = " << total_cells << std::endl;
    std::cout << "============================" << std::endl;

    // Used to index globals.cells array
    int cell = 0;
    for (int cy = 1; cy <= y_cells; ++cy)
    {
        for (int cx = 1; cx <= x_cells; ++cx)
        {
            std::cout << "\tcy = " << cy << "| cx = " << cx << std::endl;
            std::cout << "\tcell = " << cell << std::endl;
            std::cout << "\t-------------------------" << std::endl;
            cell_neighbours[cell][0] = cell - 1;
            cell_neighbours[cell][1] = cell + 1;
            cell_neighbours[cell][2] = cell - delta_y;
            cell_neighbours[cell][3] = cell + delta_y;

            // initial set the external tile mask to 0 for each tile
            for (int i = 0; i < 4; ++i)
            {
                external_cell_mask[cell][i] = 0;
            }

            if (cx == 1)
            {
                cell_neighbours[cell][0] = -1;
                external_cell_mask[cell][0] = 1;
            }
            if (cx == x_cells)
            {
                cell_neighbours[cell][1] = -1;
                external_cell_mask[cell][1] = 1;
            }
            if (cy == 1)
            {
                cell_neighbours[cell][2] = -1;
                external_cell_mask[cell][2] = 1;
            }
            if (cy == y_cells)
            {
                cell_neighbours[cell][3] = -1;
                external_cell_mask[cell][3] = 1;
            }

            c_left = cell_neighbours[cell][0];
            c_right = cell_neighbours[cell][1];
            c_top = cell_neighbours[cell][2];
            c_bottom = cell_neighbours[cell][3];

            std::cout << "\tleft = " << cell_neighbours[cell][0] << "," << c_left << std::endl;
            std::cout << "\tright = " << cell_neighbours[cell][1] << "," << c_right << std::endl;
            std::cout << "\tbottom = " << cell_neighbours[cell][2] << "," << c_top << std::endl;
            std::cout << "\ttop = " << cell_neighbours[cell][3] << "," << c_bottom << std::endl;

            for (int i = 0; i < 4; ++i)
            {
                if (!(external_cell_mask[cell][i] == 1) && (cell_neighbours[cell][i] == -1))
                    std::cout << "ERROR for " << cell << "," << i << std::endl;
                std::cout
                    << "External masks = " << external_cell_mask[cell][i] << std::endl;
            }

            std::cout << "\t-------------------------" << std::endl;

            cell++;
        }
    }
    return 0;
}