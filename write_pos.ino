/*
The function draws the path after reflection and before hitting the next edge.

!!! FOR NOW the function only draws the path in the fourth quadrant.
*/

unsigned int write_pos(float in_angle, unsigned int size[2]) {
  
  // initialize some local variables
  float theta = PI * (in_angle / 180);
  unsigned int destination[2];
  unsigned int playfield[size[0]][size[1]];
  unsigned int step = 0;

  // initialize matrix "playfield" to all zero
  for (unsigned int x = 0; x < size[1]; x++) {
    for (unsigned int y = 0; y < size[0]; y++) {
      playfield[y][x] = 0;
    }
  }

  // The following calculates increment in the x direction for each motor step in y direction
  while (true) {
    float step_x = (float)step / tan(theta);
    destination[0] = start[0] + step;
    destination[1] = start[1] + (unsigned int)(step_x + 0.5); //rounding the result the nearest integer value
    // Serial.print('{');
    // Serial.print(destination[0]);
    // Serial.print(',');
    // Serial.print(destination[1]);
    // Serial.print('}');
    
    // Boundary check
    if ((destination[1] + 1) > size[1] || (destination[0] + 1) > size[0]) {
      break;
    }
    else {
      playfield[destination[0]][destination[1]] = 1;
      // Serial.print('{');
      // Serial.print(destination[0]);
      // Serial.print(',');
      // Serial.print(destination[1]);
      // Serial.print('}');
    }
    step++;
  }

  // Print the matrix
  for (int a = 0; a < size[0]; a++) {
    Serial.print('{');
    for (int b = 0; b < size[1]; b++) {
      Serial.print(playfield[a][b]);
    }
    Serial.print('}');
    Serial.print('\n');
  }

  Serial.print('-');
  Serial.print('-');
  Serial.print('-');
  Serial.print('-');
  Serial.print('\n');

  return playfield;
}
