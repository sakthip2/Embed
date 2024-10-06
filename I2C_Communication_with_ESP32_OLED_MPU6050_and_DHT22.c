#include <Wire.h>
#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

Adafruit_MPU6050 mpu;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
  display.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println(F("SSD1306 Allocation Failed"));
    for(;;);
  }
  if (!mpu.begin()) 
  {
    Serial.println("Can't find MPU");
    while (1) 
    {
      delay(10);
    }
  }
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  delay(2000);


  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("Environmental Monitor Initialized");
}

void loop() 
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float Temperature = dht.readTemperature();
  float Humidity = dht.readHumidity();

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Temp: ");
  display.println(Temperature);

  //display.clearDisplay();
  display.setCursor(0,10);
  display.print("Humidity: ");
  display.println(Humidity);

  display.setCursor(0,20);
  display.print("Accel X: ");
  display.print(a.acceleration.x);

  display.setCursor(0,30);
  display.print("Accel Y: ");
  display.print(a.acceleration.y);

  display.setCursor(0,40);
  display.print("Gyro Z: ");
  display.print(g.gyro.z);

  display.display();

  Serial.println("Environmental Monitor:");
  Serial.print("Temp: ");
  Serial.print(Temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.println(" %");

  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.println(" m/s^2");

  Serial.print("Accel Y: ");
  Serial.print(a.acceleration.y);
  Serial.println(" m/s^2");

  Serial.print("Gyro Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  delay(2000);
}
