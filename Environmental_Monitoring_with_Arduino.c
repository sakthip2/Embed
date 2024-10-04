#include <Wire.h>
#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
 
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_MPU6050 mpu;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  dht.begin();

  if (!mpu.begin()) 
  {
    Serial.println("Can't find MPU");
    while (1) 
    {
      delay(10);
    }
  }

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
