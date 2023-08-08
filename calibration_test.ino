// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

double ax = 0;
double ay = 0;
double az = 0;
double gx = 0;
double gy = 0;
double gz = 0;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }


  calibration(ax,ay,az,gx,gy,gz,1000);
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}


void calibration(double & ax, double & ay, double & az, double & gx, double & gy, double & gz, int t){
   for(int i = 0; i < t; i++) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      
      ax+=a.acceleration.x;
      ay+=a.acceleration.y;
      az+=a.acceleration.z;
      gx+=g.gyro.x;
      gy+=g.gyro.y;
      gz+=g.gyro.z;
      
   }
    ax = ax/(t+1);
    ay = ay/(t+1);
    az = az/(t+1);
    gx = gx/(t+1);
    gy = gy/(t+1);
    gz = gz/(t+1);

    Serial.println("AN SDIJANHDUIHADIHDIA ");
    Serial.println(az);
  }



void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  /* Print out the values */
  Serial.print(a.acceleration.x - ax);
  Serial.print('_');
  Serial.print(a.acceleration.y - ay);
  Serial.print('_');
  Serial.print(a.acceleration.z - az);
  Serial.print('_');
  Serial.print(g.gyro.x - gx);
  Serial.print('_');
  Serial.print(g.gyro.y - gy);
  Serial.print('_');
  Serial.print(g.gyro.z - gz);
  
  Serial.println("");
  delay(500);
}
