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
 
// class default I2C address is 0x68
MPU6050 accelgyro;

String inString = "";

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
    case 1:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);  Serial.println("AccelRange setted to 2G");  			break;}
    case 2:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);  Serial.println("AccelRange setted to 4G");  			break;}
    case 3:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);  Serial.println("AccelRange setted to 8G");  			break;}
    case 4:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16); Serial.println("AccelRange setted to 16G"); 			break;}
    case 5:{ accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);  Serial.println("GyroRange setted to 250 degrees/sec");	break;}
    case 6:{ accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);  Serial.println("GyroRange setted to 500 degrees/sec");	break;}
    case 7:{ accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_1000); Serial.println("GyroRange setted to 1000 degrees/sec");	break;}
    case 8:{ accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000); Serial.println("GyroRange setted to 2000 degrees/sec");	break;}
    default:{ Serial.println ("Option not implemented");            break;}
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

  Serial.print(accelgyro.getAccelerationX());  Serial.print (",");
  Serial.print(accelgyro.getAccelerationY());  Serial.print (",");
  Serial.print(accelgyro.getAccelerationZ());  Serial.print (",");
  
  Serial.print(accelgyro.getRotationX());  Serial.print (",");
  Serial.print(accelgyro.getRotationY());  Serial.print (",");
  Serial.print(accelgyro.getRotationZ());  Serial.print (",");
  Serial.println(accelgyro.getTemperature()/340.00+36.53);

  handleOption ();
  delay(100);
}

