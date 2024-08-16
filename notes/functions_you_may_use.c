mlx_init: Initialises the MLX library. Must be called before using any other functions.

mlx_new_window: Creates a new window instance.

mlx_hook: Registers events.

mlx_loop: Loops over the MLX pointer, triggering each hook in order of registration.

mlx_xpm_file_to_image: Converts an XPM file to an MLX image pointer.

mlx_put_image_to_window: Puts your image to the screen at the given coordinates.
//mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y );

mlx_destroy_image: Frees the image.

mlx_destroy_window: Frees the window instance.

mlx_destroy_display: Frees MLX.

mlx_get_data_addr(): returns information about the created image, allowing a user to modify it later.
//mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );

int	mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );
/*
The mlx_pixel_put () function draws a defined pixel in the window win_ptr using the (x, y)
coordinates, and the specified color. The origin (0, 0) is the upper left corner of the 
window, the x and y axis respectively pointing right and down.
The connection identifier mlx_ptr is needed.
*/








I recommend visiting 42Docs, as they have done a great job 
documenting the MLX (linked in additional resources).

man ./minilibx-linux/man/man1/mlx.1
