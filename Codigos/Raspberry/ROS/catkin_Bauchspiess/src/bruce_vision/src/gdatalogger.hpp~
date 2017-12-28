/*****************************************************************************
// File: GDataLogger.h
// Contents: Header for GDataLogger functions.
// Author: G. A. Borges.
*****************************************************************************/
#ifndef GDATALOGGER_H
#define GDATALOGGER_H

#define GDATALOGGER_MAXVARIABLES 10

typedef struct{
	char VariableName[100];
	char VariableUnit[50];
	long int GMatlabDataFileIndex;
	double *CircularQueue;
	GQUEUECONTROL CircularQueueControl;
} GDATALOGGERVARIABLE,*PGDATALOGGERVARIABLE;

typedef struct{
	GDATALOGGERVARIABLE Variables[GDATALOGGER_MAXVARIABLES];
	int m_NumberOfVariables;
	GMATLABDATAFILECONFIG GMatlabDataFileConfig;
}GDATALOGGER,*PGDATALOGGER;

int gDataLogger_Init(PGDATALOGGER pgDataLogger, char *filename, char *dirname);
int gDataLogger_DeclareVariable(PGDATALOGGER pgDataLogger, char *varname, char *varunit, int queuesize);
int gDataLogger_InsertVariable(PGDATALOGGER pgDataLogger, char *varname, double* varvalue, int size);
int gDataLogger_MatfileUpdate(PGDATALOGGER pgDataLogger);
int gDataLogger_Close(PGDATALOGGER pgDataLogger);

#endif
