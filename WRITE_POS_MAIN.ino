/*

*/

#define PI 3.1415926535897932384626433832795
float in_angle = 45.0; // defines the angle of incidence, range is 0 to 180 for now
unsigned int size[2] = {12, 36}; // {# of rows, # of columns}

// start location is set to be first row, middle column, for now:
unsigned int start[2] = {0, (unsigned int)(size[1] / 2 + 0.5)}; 

// float y_edge = (float)(size[1] - start[1]) * tan(theta);
// char startedge = 'top';
// char hitedge = 'right';

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned int playfield = write_pos(in_angle,size);
}
