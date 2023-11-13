#include "math.h"
#include "stdlib.h"
#include <stdio.h>
#include "assert.h"
#include "PsimBlock.h"



// node information
char* inputArr[9] = {
	"Vdc",
	"Ia",
	"Ib",
	"Ic",
	"Vab",
	"Vbc",
	"Vca",
	"Vtri_new_PS",
	"P_Sel"
};

char* outputArr[20] = {
	"leg-A_H",
	"leg-A_L",
	"leg-B_H",
	"leg-B_L",
	"leg-C_H",
	"leg-C_L",
	"Iqe_ref_fb_intg",
	"Iqe_ref",
	"Vdc_ref",
	"theta",
	"Ta",
	"Tb",
	"Tc",
	"Vref_a",
	"Vref_b",
	"Vds_ref",
	"Ids_out",
	"Iqs_out",
	"Vds_out",
	"Vqs_out"
};


void REQUESTUSERDATA(
	int nRequestReason,
	int nRequestCode,
	int nRequestParam,
	void** ptrUserData,
	int* pnParam1,
	int* pnParam2,
	char* szParam1,
	char* szParam2
)
{
	if (nRequestCode == REQUEST_PARAM_COUNT)
	{
		//Get the number of parameters
		// int * pnParam1:  returns the number of parameters excluding a Data File name parameter.
		// int * pnParam2:  1: Data File parameter exist (only one Data File parameter is allowed)   0: no Data File parameter
		*pnParam1 = 3; // 2 parameters
		*pnParam2 = 0; // Data File parameter.
	}
	else if (nRequestCode == REQUEST_PARAM_INFO)
	{
		// Get parameter information
		// char * szParam1: Node Label  20 characters maximum.
		// char * szParam2: Node default value  50 characters maximum.
		// int * pnParam1:  1: Show Display check box     0: Do not show Display check box
		// int * pnParam2:  if *pnParam1 == 1  then:   1: Display check box is checked by default.     0: Display check box is not checked by default
		int nParam = nRequestParam;
		switch (nParam)
		{
			//Three Parameters 
		case 0:
			strcpy(szParam1, "All swithch off time [s]");
			*pnParam1 = 1; // Show Display check box
			if (nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
			{
				strcpy(szParam2, "0.1");
			}
			break;

		case 1:
			strcpy(szParam1, "PFC Start time [s]");
			*pnParam1 = 1; // Show Display check box
			if (nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
			{
				strcpy(szParam2, "0.15");
			}
			break;

		case 2:
			strcpy(szParam1, "Vdc_reference [V]");
			*pnParam1 = 1; // Show Display check box
			if (nRequestReason == ACTION_DLL_SELECTED) //new element. Set default value
			{
				strcpy(szParam2, "800");
			}
			break;

		default:
			assert(0);
			break;
		}
	}

	else if (nRequestCode == REQUEST_IN_OUT_NODES)
	{
		// Get the number of Input and Output nodes
		// int * pnParam1:  returns the number of input nodes.
		// int * pnParam2:  returns the number of output nodes.
		*pnParam1 = 9; // input nodes
		*pnParam2 = 20; // output nodes
	}

	else if (nRequestCode == REQUEST_INPUT_NODE_INFO)
	{
		// Get Input node information
		// char * szParam1: Node Label  20 characters maximum.
		int nNode = nRequestParam;
		switch (nNode)
		{
		case 0:
			strcpy(szParam1, inputArr[0]);
			break;

		case 1:
			strcpy(szParam1, inputArr[1]);
			break;

		case 2:
			strcpy(szParam1, inputArr[2]);
			break;

		case 3:
			strcpy(szParam1, inputArr[3]);
			break;

		case 4:
			strcpy(szParam1, inputArr[4]);
			break;

		case 5:
			strcpy(szParam1, inputArr[5]);
			break;

		case 6:
			strcpy(szParam1, inputArr[6]);
			break;

		case 7:
			strcpy(szParam1, inputArr[7]);
			break;

		case 8:
			strcpy(szParam1, inputArr[8]);
			break;

		default:
			assert(0);
			break;

		}

	}

	else if (nRequestCode == REQUEST_OUTPUT_NODE_INFO)
	{
		// Get Output node information
		// char * szParam1: Node Label  20 characters maximum.
		int nNode = nRequestParam;
		switch (nNode)
		{
		case 0:
			strcpy(szParam1, outputArr[0]);
			break;

		case 1:
			strcpy(szParam1, outputArr[1]);
			break;

		case 2:
			strcpy(szParam1, outputArr[2]);
			break;

		case 3:
			strcpy(szParam1, outputArr[3]);
			break;

		case 4:
			strcpy(szParam1, outputArr[4]);
			break;

		case 5:
			strcpy(szParam1, outputArr[5]);
			break;

		case 6:
			strcpy(szParam1, outputArr[6]);
			break;

		case 7:
			strcpy(szParam1, outputArr[7]);
			break;

		case 8:
			strcpy(szParam1, outputArr[8]);
			break;

		case 9:
			strcpy(szParam1, outputArr[9]);
			break;

		case 10:
			strcpy(szParam1, outputArr[10]);
			break;

		case 11:
			strcpy(szParam1, outputArr[11]);
			break;

		case 12:
			strcpy(szParam1, outputArr[12]);
			break;

		case 13:
			strcpy(szParam1, outputArr[13]);
			break;

		case 14:
			strcpy(szParam1, outputArr[14]);
			break;

		case 15:
			strcpy(szParam1, outputArr[15]);
			break;

		case 16:
			strcpy(szParam1, outputArr[16]);
			break;

		case 17:
			strcpy(szParam1, outputArr[17]);
			break;

		case 18:
			strcpy(szParam1, outputArr[18]);
			break;

		case 19:
			strcpy(szParam1, outputArr[19]);
			break;

		default:
			assert(0);
			break;
		}
	}
}
