#include "imu.h"
#include "FrontController.h"

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}
// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data){
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();

}
void update_imu_task(void *pvParameters){
  int16_t temp1;
  int32_t temp2;
  Wire.begin();
  // Set accelerometers low pass filter at 460Hz
  I2CwriteByte(MPU9250_ADDRESS,29,0x00);
  // Set gyroscope low pass filter at 250Hz
  I2CwriteByte(MPU9250_ADDRESS,26,0x00);
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_500_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_2_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);
  // Request continuous magnetometer measurements in 16 bits
  I2CwriteByte(MAG_ADDRESS,0x0A,0x16);

  while(1){
    uint8_t Buf1[6];
    uint8_t Buf2[6];    
    I2Cread(MPU9250_ADDRESS,0x3B,6,Buf1);
    I2Cread(MPU9250_ADDRESS,0x43,6,Buf2);
    // Create 16 bits values from 8 bits data
    // Accelerometer
    temp1 = (Buf1[0]<<8 | Buf1[1]);
    temp2 = (int32_t)temp1 + 32768; 
    ax = temp2;
    temp1 = (Buf1[2]<<8 | Buf1[3]);
    temp2 = (int32_t)temp1 + 32768; 
    ay = temp2;
    temp1 = (Buf1[4]<<8 | Buf1[5]);
    temp2 = (int32_t)temp1 + 32768; 
    az = temp2;
    serial_buffer[1] = ax & 0xFF;
    serial_buffer[0] = ax >> 8;
    serial_buffer[3] = ay & 0xFF;
    serial_buffer[2] = ay >> 8;
    serial_buffer[5] = az & 0xFF;
    serial_buffer[4] = az >> 8;

    Ax = ((float)(Buf1[0]<<8 | Buf1[1]))*2/32768;
    Ay = ((float)(Buf1[2]<<8 | Buf1[3]))*2/32768;
    Az = ((float)(Buf1[4]<<8 | Buf1[5]))*2/32768;
    // Gyroscope
    temp1 = (Buf2[0]<<8 | Buf2[1]);
    temp2 = (int32_t)temp1 + 32768; 
    gx = temp2;
    temp1 = (Buf2[2]<<8 | Buf2[3]);
    temp2 = (int32_t)temp1 + 32768; 
    gy = temp2;
    temp1 = (Buf2[4]<<8 | Buf2[5]);
    temp2 = (int32_t)temp1 + 32768; 
    gz = temp2;
    // update the buffer
    serial_buffer[7] = gx & 0xFF;
    serial_buffer[6] = gx >> 8;
    serial_buffer[9] = gy & 0xFF;
    serial_buffer[8] = gy >> 8;
    serial_buffer[11] = gz & 0xFF;
    serial_buffer[10] = gz >> 8;

    Gx = ((float)(Buf2[0]<<8 | Buf2[1]))*500/32768;
    Gy = ((float)(Buf2[2]<<8 | Buf2[3]))*500/32768;
    Gz = ((float)( Buf2[4]<<8 | Buf2[5]))*500/32768;

//    // Magnetometer
//    uint8_t ST1, ST2;
//    do{
//      I2Cread(MAG_ADDRESS,0x02,1,&ST1);
//    }while (!(ST1&0x01));
    /*
    uint8_t Mag[6];  
    
    I2Cread(MAG_ADDRESS,0x03,6,Mag);
    // Create 16 bit values from 8 bit data
    temp1 = (Mag[3]<<8 | Mag[2]);
    temp2 = (int32_t)temp1 + 32768; 
    mx = temp2;
    temp1 = (Mag[1]<<8 | Mag[0]);
    temp2 = (int32_t)temp1 + 32768;
    my = temp2;
    temp1 = (Mag[5]<<8 | Mag[4]);
    temp2 = (int32_t)temp1 + 32768;
    mz = temp2;
    serial_buffer[12] = mx & 0xFF;
    serial_buffer[13] = mx >> 8;
    serial_buffer[14] = my & 0xFF;
    serial_buffer[15] = my >> 8;
    serial_buffer[16] = mz & 0xFF;
    serial_buffer[17] = mz >> 8;

    Mx = (((float)(Mag[3]<<8 | Mag[2]) - 128.0f)/256.0f + 1)*4912/32760;
    My = (((float)(Mag[1]<<8 | Mag[0]) - 128.0f)/256.0f + 1)*4912/32760;
    Mz = (((float)(Mag[5]<<8 | Mag[4]) - 128.0f)/256.0f + 1)*4912/32760;

    I2Cread(MAG_ADDRESS,0x09,1,&ST2);
    */
    vTaskDelay( 30 / portTICK_PERIOD_MS );
  }
}
