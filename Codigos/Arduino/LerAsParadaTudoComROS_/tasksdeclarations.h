#ifndef TASKDECLARATIONS_H
#define TASKDECLARATIONS_H

// Tasks ------------------------------------------------
#define ROS
#define PERIODO 200

Scheduler runner;

void taskGPSCallback();

void taskUSCallback1();
void taskUSCallback2();
void taskUSCallback3();
void taskUSCallback4();
void taskUSCallback5();
void taskUSCallback6();
void taskBotaoCallback();
void taskShowUSReadingCallback(); // Essa é a task que printa as coisas no SERIAL, ela deve estar desabilitada para que haja comunicacao com o ROS

void taskROSCallback(); // Somente deve ser usada sem a taskShowUSReadingCallback habilitada

void taskComArduinoCallback();

Task taskGPS(PERIODO, TASK_FOREVER, &taskGPSCallback);

Task taskUS1(PERIODO, TASK_FOREVER, &taskUSCallback1);
Task taskUS2(PERIODO, TASK_FOREVER, &taskUSCallback2);
Task taskUS3(PERIODO, TASK_FOREVER, &taskUSCallback3);
Task taskUS4(PERIODO, TASK_FOREVER, &taskUSCallback4);
Task taskUS5(PERIODO, TASK_FOREVER, &taskUSCallback5);
Task taskUS6(PERIODO, TASK_FOREVER, &taskUSCallback6);
Task showUSReadings(PERIODO, TASK_FOREVER, &taskShowUSReadingCallback);

Task taskBotao(PERIODO, TASK_FOREVER, &taskBotaoCallback);

Task taskROS(PERIODO,TASK_FOREVER, &taskROSCallback);

Task taskComArduino (30, TASK_FOREVER, &taskComArduinoCallback);

void start_TASKS(){
  runner.init();

  runner.addTask(taskComArduino);
  runner.addTask(taskGPS);
  runner.addTask(taskUS1);
  runner.addTask(taskUS2);
  runner.addTask(taskUS3);
  runner.addTask(taskUS4);
  runner.addTask(taskUS5);
  runner.addTask(taskUS6);
  #ifdef ROS
   runner.addTask(taskROS); // NUNCA ADICIONAR ELA JUNTO COM A showUSReadings
  #else
   runner.addTask(showUSReadings); // NUNCA ADICIONAR ELA JUNTO COM A TASKROS
  #endif
  
  runner.addTask(taskBotao);
  
  taskGPS.enable();
  taskUS1.enable();
  taskUS2.enable();
  taskUS3.enable();
  taskUS4.enable();
  taskUS5.enable();
  taskUS6.enable();
  #ifdef ROS
    taskROS.enable(); // NUNCA HABILITAR ELA JUNTO COM A showUSReadings
  #else
    showUSReadings.enable(); // NUNCA HABILITAR ELA JUNTO COM A TASKROS   
  #endif 
  taskComArduino.enable();
  taskBotao.enable();
}

#endif
