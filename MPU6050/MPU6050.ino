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

int acquisitionTime = 1000;

int equivAccel = MPU6050_ACCEL_FS_2_EQUIV;
int equivGyro = MPU6050_GYRO_FS_250_EQUIV;

bool acquisitionActivated = false;

void showHelp (){
  Serial.println ("1 - Show help");
  Serial.println ("2 - Start acquisition");
  Serial.println ("3 - Stop acquisition");

  Serial.println ("4 - Set AccelRange to +- 2G");
  Serial.println ("5 - Set AccelRange to +- 4G");
  Serial.println ("6 - Set AccelRange to +- 8G");
  Serial.println ("7 - Set AccelRange to +- 16G");
  
  Serial.println ("8 - Set GyroRange to +- 250 degrees/sec");
  Serial.println ("9 - Set GyroRange to +- 500 degrees/sec");
  Serial.println ("10 - Set GyroRange to +- 1000 degrees/sec");
  Serial.println ("11 - Set GyroRange to +- 2000 degrees/sec");
  
  Serial.println ("12 - Increment acquisition time in 5 ms");
  Serial.println ("13 - Increment acquisition time in 50 ms");
  Serial.println ("14 - Decrement acquisition time in 5 ms");
  Serial.println ("15 - Decrement acquisition time in 50 ms\n");
}

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
      showHelp();
    break;
    }
    case 2:{ 
      acquisitionActivated = true;
      Serial.println("Starting acquisition");  
      break;
     }
     case 3:{ 
      acquisitionActivated = false;
      Serial.println("Stoping acquisition");  ;  
      break;
     }
    case 4:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
      Serial.println("AccelRange setted to 2G");  
      equivAccel = MPU6050_ACCEL_FS_2_EQUIV; 	           	
      break;
     }
    case 5:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
      Serial.println("AccelRange setted to 4G");  
      equivAccel = MPU6050_ACCEL_FS_4_EQUIV; 	           	
      break; 
    }
    case 6:{ accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
      Serial.println("AccelRange setted to 8G");  
      equivAccel = MPU6050_ACCEL_FS_8_EQUIV; 		          
      break;
    }
    case 7:{ 
      accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
      Serial.println("AccelRange setted to 16G"); 
      equivAccel = MPU6050_ACCEL_FS_16_EQUIV;		          
      break;
    }
    case 8:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
      Serial.println("GyroRange setted to 250 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_250_EQUIV;  
      break;
    }
    case 9:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
      Serial.println("GyroRange setted to 500 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_500_EQUIV;
      break;
    }
    case 10:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_1000); 
      Serial.println("GyroRange setted to 1000 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_1000_EQUIV;
      break;
    }
    case 11:{ 
      accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000); 
      Serial.println("GyroRange setted to 2000 degrees/sec");	
      equivGyro = MPU6050_GYRO_FS_2000_EQUIV; 
      break;
    }
    case 12:{ 
      Serial.println ("Incrementing acquisition time in 5 ms");
      acquisitionTime = min (acquisitionTime + 5, 1000);
      Serial.print ("Acquisition time setted to "); Serial.print (acquisitionTime); Serial.println (" ms");
      break;
    }
    case 13:{ 
      Serial.println ("Incrementing acquisition time in 50 ms"); 
      acquisitionTime = min (acquisitionTime + 50, 1000);
      Serial.print ("Acquisition time setted to "); Serial.print (acquisitionTime); Serial.println (" ms");
      break;
    }
    case 14:{ 
      Serial.println("Decrementing acquisition time in 5 ms");
      acquisitionTime = max (acquisitionTime - 5, 5);
      Serial.print ("Acquisition time setted to "); Serial.print (acquisitionTime); Serial.println (" ms");
      break;
    }
    case 15:{ 
      Serial.println("Decrementing acquisition time in 50 ms");  
      acquisitionTime = max (acquisitionTime - 50, 5);
      Serial.print ("Acquisition time setted to "); Serial.print (acquisitionTime); Serial.println (" mz");
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

  Serial.begin(9600);

  accelgyro.initialize();
  Serial.println ("Setted adquisition time to 1000 ms");
  Serial.println ("Setted AccelRange to +- 2G");
  Serial.println ("Setted GyroRange to +- 250 degrees/sec\n");

  showHelp ();
}

void loop(){

  if (acquisitionActivated){
    Serial.print(float (accelgyro.getAccelerationX()) / equivAccel) * 9.8;  Serial.print (",");
    Serial.print(float (accelgyro.getAccelerationY()) / equivAccel) * 9.8;  Serial.print (",");
    Serial.print(float (accelgyro.getAccelerationZ()) / equivAccel) * 9.8;  Serial.print (",");
    
    Serial.print(float (accelgyro.getRotationX()) / equivGyro);   Serial.print (",");
    Serial.print(float (accelgyro.getRotationY()) / equivGyro);   Serial.print (",");
    Serial.print(float (accelgyro.getRotationZ()) / equivGyro);   Serial.print (",");
    
    Serial.println(accelgyro.getTemperature() / 340.00 + 36.53);
    delay(acquisitionTime);
  }

  handleOption ();
}
