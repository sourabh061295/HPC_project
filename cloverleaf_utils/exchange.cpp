#include <iostream>
#define NUM_FIELDS 4

int main() 
{
	int left_right_offset[NUM_FIELDS];
	int bottom_top_offset[NUM_FIELDS];
    int fields[NUM_FIELDS] = {};
    int depth = 2;
    int globals_x_max = 960;
    int globals_y_max = 960;
    int chunk_neighbours[4];
    int tile_neighbours[4];
    int tiles_per_chunk = 1;

	int request[4] = {0};
	int message_count = 0;

	int end_pack_index_left_right = 0;
	int end_pack_index_bottom_top = 0;

    // Make all fields true
    for (int f = 0; f < NUM_FIELDS; ++f) 
    {
        fields[f] = 1;
    }

    // Make some chunk neighbours as external
    chunk_neighbours[0] = -1;
    chunk_neighbours[1] = 2;
    chunk_neighbours[2] = -1;
    chunk_neighbours[3] = 3;

    // Make all tile neighbours as external
    tile_neighbours[0] = 1;
    tile_neighbours[1] = 1;
    tile_neighbours[2] = 1;
    tile_neighbours[3] = 1;

    std::cout << "============================" << std::endl;
	std::cout << "globals_x_max = "<< globals_x_max << "| globals_y_max = " << globals_y_max << std::endl;
	std::cout << "end_pack_index_left_right = " << end_pack_index_left_right << std::endl;
	std::cout << "end_pack_index_bottom_top = " << end_pack_index_bottom_top << std::endl;
	std::cout << "============================" << std::endl;

	for (int field = 0; field < NUM_FIELDS; ++field) 
    {
		if (fields[field] == 1) 
        {
		    std::cout << "\t-------------------------" << std::endl;
            std::cout << "\tfield = " << field << std::endl;
			left_right_offset[field] = end_pack_index_left_right;
			bottom_top_offset[field] = end_pack_index_bottom_top;
			end_pack_index_left_right += depth * (globals_y_max + 5);
			end_pack_index_bottom_top += depth * (globals_x_max + 5);
            std::cout << "\tleft_right_offset[" << field << "] = " << left_right_offset[field] << std::endl;
            std::cout << "\tbottom_top_offset[" << field << "] = " << bottom_top_offset[field] << std::endl;
            std::cout << "\tend_pack_index_left_right = " << end_pack_index_left_right << std::endl;
	        std::cout << "\tend_pack_index_bottom_top = " << end_pack_index_bottom_top << std::endl;

		}
	}

	if (chunk_neighbours[0] != -1) 
    {
		// do left exchanges
		// Find left hand tiles
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[0] == 1)
            {
                std::cout << "Packing left....." << std::endl;
				// clover_pack_left(globals, tile, fields, depth, left_right_offset);
			}
		}

        std::cout << "Sending and receiving left....." << std::endl;
		// send and recv messages to the left
		// clover_send_recv_message_left(globals,
		//                               globals.chunk.left_snd_buffer,
		//                               globals.chunk.left_rcv_buffer,
		//                               end_pack_index_left_right,
		//                               1, 2,
		//                               request[message_count], request[message_count + 1]);
		message_count += 2;
	}

	if (chunk_neighbours[1] != -1) 
    {
		// do right exchanges
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[1] == 1) 
            {
                std::cout << "Packing right....." << std::endl;
				// clover_pack_right(globals, tile, fields, depth, left_right_offset);
			}
		}
        
        std::cout << "Sending and receiving right....." << std::endl;
		// send message to the right
		// clover_send_recv_message_right(globals,
		//                                globals.chunk.right_snd_buffer,
		//                                globals.chunk.right_rcv_buffer,
		//                                end_pack_index_left_right,
		//                                2, 1,
		//                                request[message_count], request[message_count + 1]);
		message_count += 2;
	}

	// make a call to wait / sync
	// globals.queue.wait_and_throw();
	// MPI_Waitall(message_count, request, MPI_STATUS_IGNORE);

	// unpack in left direction
	if (chunk_neighbours[0] != -1) {
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[0] == 1) 
            {
                std::cout << "Unpacking left....." << std::endl;
				// clover_unpack_left(globals, fields, tile, depth, left_right_offset);
			}
		}
	}

	// unpack in right direction
	if (chunk_neighbours[1] != -1) {
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[1] == 1) 
            {
                std::cout << "Unpacking right....." << std::endl;
				// clover_unpack_right(globals, fields, tile, depth, left_right_offset);
			}
		}
	}

	message_count = 0;
	for (int &i : request) i = 0;

	if (chunk_neighbours[2] != -1) 
    {
		// do bottom exchanges
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[2] == 1) 
            {
                std::cout << "Packing bottom....." << std::endl;
				// clover_pack_bottom(globals, tile, fields, depth, bottom_top_offset);
			}
		}

        std::cout << "Sending and receiving bottom....." << std::endl;
		// send message downwards
		// clover_send_recv_message_bottom(globals,
		//                                 globals.chunk.bottom_snd_buffer,
		//                                 globals.chunk.bottom_rcv_buffer,
		//                                 end_pack_index_bottom_top,
		//                                 3, 4,
		//                                 request[message_count], request[message_count + 1]);
		message_count += 2;
	}

	if (chunk_neighbours[3] != -1) {
		// do top exchanges
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[3] == 1) 
            {
                std::cout << "Packing top....." << std::endl;
				// clover_pack_top(globals, tile, fields, depth, bottom_top_offset);
			}
		}

        std::cout << "Sending and receiving top....." << std::endl;
		// send message upwards
		// clover_send_recv_message_top(globals,
		//                              globals.chunk.top_snd_buffer,
		//                              globals.chunk.top_rcv_buffer,
		//                              end_pack_index_bottom_top,
		//                              4, 3,
		//                              request[message_count], request[message_count + 1]);
		message_count += 2;

	}

	// need to make a call to wait / sync
	// globals.queue.wait_and_throw();
	// MPI_Waitall(message_count, request, MPI_STATUS_IGNORE);

	// unpack in top direction
	if (chunk_neighbours[3] != -1) {
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[3] == 1) 
            {
                std::cout << "Unpacking top....." << std::endl;
				// clover_unpack_top(globals, fields, tile, depth, bottom_top_offset);
			}
		}
	}

	// unpack in bottom direction
	if (chunk_neighbours[2] != -1) {
		for (int tile = 0; tile < tiles_per_chunk; ++tile) 
        {
			if (tile_neighbours[2] == 1) 
            {
                std::cout << "Unpacking bottom....." << std::endl;
				// clover_unpack_bottom(globals, fields, tile, depth, bottom_top_offset);
			}
		}
	}
}
