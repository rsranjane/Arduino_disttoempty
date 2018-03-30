

#include <LiquidCrystal.h>
LiquidCrystal lcd( 2, 3, 4, 5, 6, 7); //(rs, enable, d4, d5, d6, d7)
#define hallsensor 27


#define trigPin 12    //for oil level sensor
#define echoPin 11
long duration;
long distanceCm;
int oil_level1;
int oil_level2;
boolean LED = 23;

#define trigPin1 9     //for  fuel level sensor
#define echoPin1 10
long duration1;
long distanceCm1;
int fuel_level1;
int fuel_level2;
boolean LED1 = 13;



float change;

float displacement2;
float mileage1;

unsigned long  val;
unsigned long val1;
unsigned int rpm;
unsigned long newmil;
unsigned long oldmil;
unsigned int durn;



void reading1();
void reading2();
void rrpm();
void mileage();

int level;
int level1;
int dist;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(hallsensor, INPUT);

  ////////////////////////initializing all the variables////////////////////

  float oil_level1 = 0;        /////for reading 1
  float fuel_level1 = 0;
  float distance1 = 0;

  float oil_level2 = 0;         ///// for reading 2
  float fuel_level2 = 0;
  float distance2 = 0;



  displacement2 = 0;

  float mileage1 = 0;

  int pulse = 0;
  int counter = 0;
  int count = 0;
  int passedtime = 0;

  int rpm = 0;
  int newmil = 0;
  int oldmil = 0;

  int level = 0;
  int level1 = 0;
  int dist = 0;
}

void loop() {




  digitalWrite(trigPin, LOW);     //creating a wave for transmission for oil level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  digitalWrite(trigPin1, LOW);    //creating  a wave for transmission for fuel level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  rrpm();
  delay(1000);

}


void rrpm()
{


  val = 0;
  val1 = 0;
  int rpm = 0;
  int durn = 0;
  val = pulseIn(hallsensor, LOW);

  if (val > 1)
  {
    oldmil = millis();
    delay(20);

    val1 = pulseIn(hallsensor, LOW);
    if ( val1 > 1)
    {
      newmil = millis();
      durn = newmil - oldmil;

      rpm = 30000 / durn;
      Serial.println("the value of rpm is :  ");
      Serial.println(rpm);
       lcd.setCursor(7, 1);
  lcd.print("rpm:");
  lcd.setCursor(11, 1);
  lcd.print(rpm);


      displacement2 = rpm * 3.14 * 5;
      Serial.println("value of diplacment  is :");
      Serial.print(displacement2);
      Serial.println("            ");

 mileage();
 
   mileage1 = displacement2 /10;
  Serial.println("The mileage achieved is : ");
  Serial.println(mileage1);
  dist = mileage1 * fuel_level1;
  lcd.setCursor(6, 0);
  lcd.print("di:");
  lcd.setCursor(10, 0);
  lcd.print (dist);
    }
  }
 
  
}

void mileage()
{

 float mileage1 = 0.00;
  float change = 0 ;
  
  reading1();
  delay(5000);

  reading2();
  delay(50);

  

  change = fuel_level1 - fuel_level2;
  Serial.println(change);

 

}

void reading1() {

  digitalWrite(trigPin, LOW);     //creating a wave for transmission for oil level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  digitalWrite(trigPin1, LOW);    //creating  a wave for transmission for fuel level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);


  duration = pulseIn(echoPin, HIGH);       //Algorithm for level measurement of oil
  distanceCm = duration * 0.034 / 2;
  level = distanceCm * 10.00;           //15 indicates the height of oil tank in cm
  oil_level1 = level;


  duration1 = pulseIn(echoPin1, HIGH);       //Algorithm for level measurement of fuel
  distanceCm1 = duration * 0.034 / 2;
  level1 = distanceCm1 * 10.00;           //25 indicates the height of oil tank in cm
  fuel_level1 = level1;





  if (oil_level1 <= 30)
  {

    digitalWrite(LED, HIGH);

  }

  if (fuel_level1 <= 30)
  {

    digitalWrite(LED1, HIGH);

    delay(1000);

  }
}

void reading2() {

  digitalWrite(trigPin, LOW);     //creating a wave for transmission for oil level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);



  duration = pulseIn(echoPin, HIGH);       //Algorithm for level measurement of oil
  distanceCm = duration * 0.034 / 2;
  level = distanceCm * 10;           //15 indicates the height of oil tank in cm
  oil_level2 = level;

  digitalWrite(trigPin1, LOW);    //creating  a wave for transmission for fuel level sensor
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);       //Algorithm for level measurement of fuel
  distanceCm1 = duration1 * 0.034 / 2;
  level1 = distanceCm1 * 10;           //25 indicates the height of oil tank in cm
  fuel_level2 = level1;



  lcd.setCursor(0, 0);
  lcd.print("o:");
  lcd.print(level);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("f:");
  lcd.print(level1);
  lcd.print("%");

  if (oil_level2 <= 30)
  {

    digitalWrite(LED, HIGH);

  }

  if (fuel_level2 <= 30)
  {

    digitalWrite(LED1, HIGH);

  }
}


