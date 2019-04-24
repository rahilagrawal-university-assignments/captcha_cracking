int read_pbm(char filename[], int height, int width, int pixels[height][width]);
int get_pbm_dimensions(char filename[], int *height, int *width);
void print_image(int height, int width, int pixels[height][width]);
void get_bounding_box(int height, int width, int pixels[height][width], int *start_row, int *start_column, int *box_height, int *box_width);
void copy_pixels(int height, int width, int pixels[height][width], int start_row, int start_column, int copy_height, int copy_width, int copy[copy_height][copy_width]);
double get_horizontal_balance(int height, int width, int pixels[height][width]);
double get_vertical_balance(int height, int width, int pixels[height][width]);
int number_black_pixels(int height, int width, int pixels[height][width]);
void get_sums(int height, int width, int pixels[height][width], int *sum_row, int *sum_column);
void number_of_holes(int height, int width, int pixels[height][width], int *holes , int *hole_location);
int number_white_pixels(int height, int width, int pixels[height][width]);
int guess_captcha(int height, int width, int pixels[height][width]);

