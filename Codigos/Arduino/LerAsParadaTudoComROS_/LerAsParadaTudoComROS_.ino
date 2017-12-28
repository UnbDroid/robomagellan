#include <TaskScheduler.h>

#include "gps.h"
#include "comArduino.h"
#include "roscom.h"
#include "idsros.h"
#include "ultrassom.h"
#include "controlerc.h"
#include "sensortoque.h"
#include "botaoStart.h"
#include "tasksdeclarations.h"
#include "sinalLuminoso.h"


// Aqui chegam as mensagens vindas do ROS -------------------

void messageInt64Cb( const raspberry_msgs::StampedInt64& r_int64_msg){
  if(r_int64_msg.id == SINAL_LUMINOSO){
    if(r_int64_msg.data == 0){
      apagarSinalLuminoso();
    }else if(r_int64_msg.data == 1){
      acenderSinalLuminoso();
    }
  }
}

void messageFloat32Cb( const raspberry_msgs::StampedFloat32& r_float32_msg){

  if(r_float32_msg.id == VEL_REF_DIR){
    velRef.dir = r_float32_msg.data;
  }else if(r_float32_msg.id == VEL_REF_ESQ){
    velRef.esq = r_float32_msg.data;
  }

}

void messageFloat64Cb( const raspberry_msgs::StampedFloat64& r_float64_msg){
}

void taskGPSCallback(){
  leituraTinyGps();
  #ifdef ROS
    static bool old_gps_valid = false;
    if(gps_valid != old_gps_valid){
      old_gps_valid = gps_valid;
      sendInt64(GPS_VALID,gps_valid);      
    }
    if(gps_valid){
      static float old_lat = 0.0;
      if(lat != old_lat){
        old_lat = lat;
        sendFloat64(GPS_LAT,lat);
      }
      static float old_lon = 0.0;
      if(lon != old_lon){
        old_lon = lon;
        sendFloat64(GPS_LON,lon);
      }      
      static float old_hdop = 0.0;
      if(hdop != old_hdop){
        old_hdop = hdop;
        sendFloat64(GPS_HDOP,hdop);
      }
      static float old_speed = 0.0;
      if(speed != old_speed){
        old_speed = speed;
        sendFloat64(GPS_SPEED,speed);
      }     
      static bool old_gps_updated = false;
      if(gps_updated != old_gps_updated){
        old_gps_updated = gps_updated;
        sendInt64(GPS_UPDATED,gps_updated);
      }            
    }
  #endif  
}

void taskUSCallback1(){
  readUS(0);
  readUS(10);
  #ifdef ROS
      /*static int old_us1 = -1;
      if(USReadings[0] != old_us1){
        old_us1 = USReadings[0];*/
        sendInt64(US01, USReadings[0]);
      /*}
      static int old_us11 = -1;
      if(USReadings[10] != old_us11){
        old_us11 = USReadings[10];*/
        sendInt64(US11, USReadings[10]);
      //}
  #endif
}

void taskUSCallback2(){
  readUS(1);
  readUS(9);
  #ifdef ROS
    /*static int old_us2 = -1;
    if(USReadings[1] != old_us2){
      old_us2 = USReadings[1];*/
      sendInt64(US02, USReadings[1]);
    /*}
    static int old_us10 = -1;
    if(USReadings[9] != old_us10){
      old_us10 = USReadings[9];*/
      sendInt64(US10, USReadings[9]);
    //}
  #endif
}

void taskUSCallback3(){
  readUS(2);
  readUS(8);
  #ifdef ROS
    /*static int old_us3 = -1;
    if(USReadings[2] != old_us3){
      old_us3 = USReadings[2];*/
      sendInt64(US03, USReadings[2]);
    /*}
    static int old_us09 = -1;
    if(USReadings[8] != old_us09){
      old_us09 = USReadings[8];*/
      sendInt64(US09, USReadings[8]);
    //}
  #endif
}

void taskUSCallback4(){
  readUS(3);
  readUS(7);
  #ifdef ROS
    /*static int old_us4 = -1;
    if(USReadings[3] != old_us4){
      old_us4 = USReadings[3];*/
      sendInt64(US04, USReadings[3]);
    /*}
    static int old_us08 = -1;
    if(USReadings[7] != old_us08){
      old_us08 = USReadings[7];*/
      sendInt64(US08, USReadings[7]);
    //}
  #endif
}

void taskUSCallback5(){
  readUS(4);
  readUS(6);
  #ifdef ROS
    /*static int old_us5 = -1;
    if(USReadings[4] != old_us5){
      old_us5 = USReadings[4];*/
      sendInt64(US05, USReadings[4]);
    /*}
    static int old_us07 = -1;
    if(USReadings[6] != old_us07){
      old_us07 = USReadings[6];*/
      sendInt64(US07, USReadings[6]);
   // }
  #endif
}

void taskUSCallback6(){
  readUS(5);
  #ifdef ROS
    /*static int old_us6 = -1;
    if(USReadings[5] != old_us6){
      old_us6 = USReadings[5];*/
      sendInt64(US06, USReadings[5]); 
    //}    
  #endif
}

void taskShowUSReadingCallback(){
  Serial.print("US Readings: ");
  Serial.println(millis());
  unsigned long t1 = millis();
  for(unsigned i=0; i<SONAR_NUM;i++){
    Serial.print("US ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(USReadings[i]);
    Serial.println("cm");
  }
  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(channel_value1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(channel_value2);
  Serial.print("Mandei:"); Serial.println(velRef.dir);
  Serial.print("Mandei:"); Serial.println(velRef.esq);
  Serial.print("Channel 3: ");
  Serial.println(channel_value3);
  Serial.print("Toque: ");      Serial.println(sensorToque);
  Serial.print("Vel esq: "); Serial.println(velAtual.esq);
  Serial.print("Vel dir: "); Serial.println(velAtual.dir);
  Serial.print("Botao Verde: ");Serial.println(botaoVerde);
  Serial.print("Botao Preto: ");Serial.println(botaoPreto);
  Serial.print("Trava de seguranca: ");Serial.println(travaSeguranca);
 
  unsigned long t2 = millis();
  Serial.print("Demorei ");
  Serial.println(t2-t1);
  Serial.println(" "); 
}

void taskBotaoCallback(){
  sensorToque = lerSensorToque();
  botaoPreto = lerBotaoPreto();
  botaoVerde = lerBotaoVerde();
  #ifdef ROS
    static bool old_sensor_toque = false;
    if(old_sensor_toque != sensorToque){
      old_sensor_toque = sensorToque;
      sendInt64(SENSOR_TOQUE, sensorToque); 
    }
    static bool old_botao_verde = false;
    if(old_botao_verde != botaoVerde){
      old_botao_verde = botaoVerde;
      sendInt64(BOTAO_VERDE, botaoVerde);
    }
    static bool old_botao_preto = false;
    if(old_botao_preto != botaoPreto){
      old_botao_preto = botaoPreto;
      sendInt64(BOTAO_PRETO, botaoPreto);
    }    
  #endif
}
void taskComArduinoCallback(){
  processarControleRC(velRef.dir,velRef.esq);

  if(travaSeguranca){
    velRef.dir = 0;
    velRef.esq = 0;    
  }
  
  velRefRaw.dir = vel2Raw(velRef.dir);
  velRefRaw.esq = vel2Raw(velRef.esq);
  
  ET.sendData();
  if(ET2.receiveData()){
    velAtual.dir = velFromRaw(velAtualRaw.dir);
    velAtual.esq = velFromRaw(velAtualRaw.esq);
    #ifdef ROS
      static float old_vel_atual_dir = -999999;
      if(old_vel_atual_dir != velAtual.dir){
        old_vel_atual_dir = velAtual.dir;
        sendFloat64(VEL_ATUAL_DIR,velAtual.dir);
      }
      static float old_vel_atual_esq = -999999;
      if(old_vel_atual_esq != velAtual.esq){
        old_vel_atual_esq = velAtual.esq;
        sendFloat64(VEL_ATUAL_ESQ,velAtual.esq);
      }
    #endif
  }
    
}

void setup() {
  // put your setup code here, to run once:

  #ifdef ROS
    initializeRosCom();
  #else
    Serial.begin(115200);
  #endif
  
  delay(1000);

  start_COMARDUINO();

  start_RC();

  start_TASKS();
  
  startSENSORTOQUE();

  startBotoes();

  start_GPS();

  startSINALLUMINOSO();
  /*acenderSinalLuminoso();
  delay(10000);
  apagarSinalLuminoso();*/  

  //start_SD();
  
}

void loop() {

  
  // put your main code here, to run repeatedly:
  //esquerda_eixo(50,50);
  runner.execute();
  #ifdef ROS
    nh.spinOnce();
  #endif
}
