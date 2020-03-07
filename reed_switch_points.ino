const int reedSwitch = 2;

int reedStatus = 0;
int points = 0;

const int row = 10;
const int column = 10;
int matrix[row][column] = {0}; //[row][column]

void setup()
{
  pinMode(reedSwitch, INPUT);
  Serial.begin(9600);
}

void reflect()
{
  //plot new position matrix
}


void loop()
{
  reedStatus = digitalRead(reedSwitch);
  for(int c=0; c<=row-1; c++) {
    //if ball is in 2nd last row
    if(matrix[row-2][c] == 1 || matrix[1][c] == 1){
      if (reedStatus == HIGH) { //hit the paddle
        reflect;
      } else { //did not hit the paddle
        points++;
        delay(500);
      }
    } 
  }
}
    
