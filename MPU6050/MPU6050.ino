#include "I2Cdev.h"
#include "MPU6050.h"

/*
 * #define MPU6050_ACCEL_FS_2          0x00
 * #define MPU6050_ACCEL_FS_4          0x01
 * #define MPU6050_ACCEL_FS_8          0x02
 * #define MPU6050_ACCEL_FS_16         0x03
 * 
 * #define MPU6050_GYRO_FS_250         0x00
 * #define MPU6050_GYRO_FS_500         0x01
 * #define MPU6050_GYRO_FS_1000        0x02
 * #define MPU6050_GYRO_FS_2000        0x03
 */

#define MPU6050_ACCEL_FS_2_EQUIV    16384
#define MPU6050_ACCEL_FS_4_EQUIV    8192
#define MPU6050_ACCEL_FS_8_EQUIV    4096
#define MPU6050_ACCEL_FS_16_EQUIV   2048

#define MPU6050_GYRO_FS_250_EQUIV   131
#define MPU6050_GYRO_FS_500_EQUIV   65,5
#define MPU6050_GYRO_FS_1000_EQUIV  32,8
#define MPU6050_GYRO_FS_2000_EQUIV  16,4
 
// class default I2C address is 0x68
MPU6050 accelgyro;

String inString = "";

int equivAccel = MPU6050_ACCEL_FS_2_EQUIV;
int equivGyro = MPU6050_GYRO_FS_250_EQUIV;

int getOption (){
  int option = -1;
  while (Serial.available() > 0){
    int inChar = Serial.read();
    if (isDigit(inChar))  inString += (char)inChar;
    
    if (inChar == '\n') {
      option = inString.toInt();
      inString = "";
    }
  }
  return option;
}

void handleOption (){
  switch (getOption ()){
    case -1: break;
    case 1:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
      Serial.println("AccelRange setted to 2G");  
      equivAccel = MPU6050_ACCEL_FS_2_EQUIV; 	           	
      break;
     }
    case 2:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
      Serial.println("AccelRange setted to 4G");  
      equivAccel = MPU6050_ACCEL_FS_4_EQUIV; 	           	
      break; 
    }
    case 3:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
      Serial.println("AccelRange setted to 8G");  
      equivAccel = MPU6050_ACCEL_FS_8_EQUIV; 		          
      break;
    }
    case 4:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
      Serial.println("AccelRange setted to 16G"); 
      equivAccel = MPU6050_ACCEL_FS_16_EQUIV;		          
      break;
    }
    case 5:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
      Serial.println("GyroRange setted to 250 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_250_EQUIV;  
      break;
    }
    case 6:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
      Serial.println("GyroRange setted to 500 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_500_EQUIV;
      break;
    }
    case 7:{ accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_1000); 
      Serial.println("GyroRange setted to 1000 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_1000_EQUIV;
      break;
    }
    case 8:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000); 
      Serial.println("GyroRange setted to 2000 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_2000_EQUIV; 
      break;
    }
    default:{ 
      Serial.println ("Option not implemented");
      break;
    }
  }
}
void setup(){

  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  accelgyro.initialize();
  
  Serial.begin(9600);

  Serial.println ("1 - Set AccelRange to +- 2G");
  Serial.println ("2 - Set AccelRange to +- 4G");
  Serial.println ("3 - Set AccelRange to +- 8G");
  Serial.println ("4 - Set AccelRange to +- 16G");
  Serial.println ("5 - Set GyroRange to +- 250 degrees/sec");
  Serial.println ("6 - Set GyroRange to +- 500 degrees/sec");
  Serial.println ("7 - Set GyroRange to +- 1000 degrees/sec");
  Serial.println ("8 - Set GyroRange to +- 2000 degrees/sec");
}

void loop(){

  Serial.print(float (accelgyro.getAccelerationX()) / equivAccel) * 9,8;  Serial.print (",");
  Serial.print(float (accelgyro.getAccelerationY()) / equivAccel) * 9,8;  Serial.print (",");
  Serial.print(float (accelgyro.getAccelerationZ()) / equivAccel) * 9,8;  Serial.print (",");
  
  Serial.print(float (accelgyro.getRotationX()) / equivGyro);   Serial.print (",");
  Serial.print(float (accelgyro.getRotationY()) / equivGyro);   Serial.print (",");
  Serial.print(float (accelgyro.getRotationZ()) / equivGyro);   Serial.print (",");
  
  Serial.println(accelgyro.getTemperature() / 340.00 + 36.53);

  handleOption ();
  delay(100);
}
