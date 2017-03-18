#ifndef TASKDECLARATIONS_H
#define TASKDECLARATIONS_H

// Tasks ------------------------------------------------

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
void taskShowUSReadingCallback();

void taskROSCallback();

void taskENCODERCallback();

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

Task taskENCODER (30, TASK_FOREVER, &taskENCODERCallback);

void start_TASKS(){
  runner.init();

  runner.addTask(taskENCODER);
  //runner.addTask(taskGPS);
  runner.addTask(taskUS1);
  runner.addTask(taskUS2);
  runner.addTask(taskUS3);
  runner.addTask(taskUS4);
  runner.addTask(taskUS5);
  runner.addTask(taskUS6);
  runner.addTask(showUSReadings);
  
  runner.addTask(taskBotao);
  //runner.addTask(taskROS);
  
  //taskGPS.enable();
  taskUS1.enable();
  taskUS2.enable();
  taskUS3.enable();
  taskUS4.enable();
  taskUS5.enable();
  taskUS6.enable();
  showUSReadings.enable();
  //taskROS.enable();
  taskENCODER.enable();
  taskBotao.enable();
}

#endif
