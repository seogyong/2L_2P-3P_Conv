//*******************************************************************
//     THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO POWERSIM INC.,
//     AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
//     WITHOUT COMPANY AUTHORIZATION.
//     COPYRIGHT (c) POWERSIM INC. 2007
//     THIS WORK IS UNPUBLISHED.                          
//*******************************************************************



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Request Reasons:


#define ACTION_DLL_ReloadData		-1  //Send data from DLL to PSIM


#define ACTION_DLL_SELECTED			0  //New Element was placed on the schematic window and this DLL was selected.

// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Read only):  full path and file name of this DLL
//		char * szParam2(Write only):  copy default file path for input data file. file must exist otherwise it will be ignored
//		Allocate memory for ptrUserData (*ptrUserData = new ...)
//		all other parameters ignored
// 
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  0X0001: Data File parameter exist (only one primary Data File parameter is allowed)   0X00020000: Do not show Input/Output nodes in properties dialog box 
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): if a default file name needed then set to Full file path (260 characters maximum)  otherwise leave unchanged.
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only       0X00020000:ComboBox
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_DLL_SELECTED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		all other parameters ignored
//






#define ACTION_ELEMENT_LOAD			1  //Previously saved element is  being loaded from file or being pasted as part of copy/paste operation

// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Read only):  binary data that was provided by DLL at save time. (DLL version, File Version, ...)
//		int * pnParam1(Read only):   number of valid bytes in szParam1
//		char * szParam2(Read, Write): Selected Input file path if any
//		Allocate memory for ptrUserData if needed (*ptrUserData = new ...)
//
//
// 
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  0X0001: Data File parameter exist (only one primary Data File parameter is allowed)   0X00020000: Do not show Input/Output nodes in properties dialog box 
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): Input file path (260 characters maximum).
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_LOAD, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//





#define ACTION_ELEMENT_SAVE			2  //Saving element to file or to buffer(Copy/paste operation)

// REQUESTUSERDATA(ACTION_ELEMENT_SAVE, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		char * szParam1(Write only):  copy binary data to be saved in .SCH file(DLL version, File Version, ...) (maximum 1000 bytes)
//		int * pnParam1(Write only):   number of valid bytes in szParam1
//		char * szParam2(Read only): Selected Input file path 
//
//
// REQUESTUSERDATA(ACTION_ELEMENT_SAVE, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 




#define ACTION_INPUTFILE_CHANGED	3  //a new input file was selected

// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Selected Input file path 
//		 int * pnParam1(Write only):  0: Reject the file    1: set to 1 or Leave unchanged to accept the file
//
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_PARAM_COUNT, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter.
//		 int * pnParam2(Read, Write):  0X0001: Data File parameter exist (only one primary Data File parameter is allowed)   0X00020000: Do not show Input/Output nodes in properties dialog box 
//		 char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
//		 char * szParam2(Read only):  string ID associated with the element
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_DATAFILE_INFO, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 char * szParam1(Read, Write): Label  20 characters maximum.
//		 char * szParam2(Read, Write): Input file path (260 characters maximum).
//		 int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read, Write): parameter Label  20 characters maximum.
//		 char * szParam2(Read, Write): parameter default value  50 characters maximum.
//		 int * pnParam1(Read, Write):  0X00000001: Show Display check box     0X00000002: Read Only
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_IN_OUT_NODES, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		 Get the number of Input and Output nodes
//		 int * pnParam1(Read, Write):  returns the number of input nodes.
//		 int * pnParam2(Read, Write):  returns the number of output nodes.
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_INPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of input nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Input node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_OUTPUT_NODE_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of output nodes - 1 (set in REQUEST_IN_OUT_NODES)'
//		 Get Output node information
//		 char * szParam1(Read, Write): Node Label  20 characters maximum.
//		 int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
//
//
// REQUESTUSERDATA(ACTION_INPUTFILE_CHANGED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//







#define ACTION_PARAMETERS_CHANGED	4  //parameters were changed in the property dialog box.
//       you may Modify parameters and update user data based on new parameters 
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//
//
//
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_PARAM_INFO, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called several times with  "nRequestParam" set to  0 to 'number of parameters - 1 (set in REQUEST_PARAM_COUNT)'
//		 Get parameter information
//		 char * szParam1(Read Only): parameter Label.
//		 char * szParam2(Read, Write): parameter value.
//		 set *pnParam2 = 1  to reload all parameters and number of input/output nodes
//
//
// REQUESTUSERDATA(ACTION_PARAMETERS_CHANGED, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//





#define ACTION_ELEMENT_DELETE	5  //element is being deleted or file is being closed

// REQUESTUSERDATA(ACTION_ELEMENT_DELETE, REQUEST_BEGIN, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//		Delete alocated memory for ptrUserData ( delete *ptrUserData; )
//
// REQUESTUSERDATA(ACTION_ELEMENT_DELETE, REQUEST_END, 0, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
// 
//



#define ACTION_PARAMETERS_ACTION	10  // a button was pressed in the property dialog box.
//       
// REQUESTUSERDATA(ACTION_PARAMETERS_ACTION, REQUEST_BEGIN, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called when a button was pressed in the property dialog box. "nRequestParam" set to  parameter's index (Zero based) 
//		 Get parameter information
//		 char * szParam1: empty
//		 char * szParam2(Read, write): parameter value. 
//		 int * pnParam1 (Read only): HWND of the dialog box
//		 int * pnParam2 (write) set to = 1  to reload all parameters and number of input/output nodes
//


#define ACTION_PARAMETERS_NOTIFY	11  //parameters were changed in the property dialog box.
//       
// REQUESTUSERDATA(ACTION_PARAMETERS_NOTIFY, REQUEST_BEGIN, nRequestParam, void ** ptrUserData, int * pnParam1, int * pnParam2, char * szParam1, char * szParam2);
//	 this is called everytime text in editbox or selection of Combobox changes. "nRequestParam" set to  parameter's index (Zero based) 
//		 Get parameter information
//		 char * szParam1: empty
//		 char * szParam2(Read only): parameter value. changes to this value are ignored
//		 set *pnParam2 = 1  to reload all parameters and number of input/output nodes
//




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Request Codes:


// 
#define REQUEST_BEGIN	10	
	// all values depend on "int nRequestReason"  value

#define REQUEST_END		11	
	// all values depend on "int nRequestReason"  value


// Get the number of Input and Output nodes
#define REQUEST_IN_OUT_NODES	1	
	// int * pnParam1(Read, Write):  returns the number of input nodes.
	// int * pnParam2(Read, Write):  returns the number of output nodes.
	//nRequestParam, szParam1, szParam2 : ignore



// Get the number of parameters
#define REQUEST_PARAM_COUNT		2   
	// int * pnParam1(Read, Write):  returns the number of parameters excluding a Data File name parameter or Grid data.
    // int * pnParam2(Read, Write):  //0X00000001: Data File parameter exist (only one primary Data File parameter is allowed)   
									 //0X00000004: Grid data list exist (only one Grid is allowed)   
									 //0X00020000: Do not show Input/Output nodes in properties dialog box 

	// char * szParam1(Read, Write):  File Open Dialog Filter for InputFile. By Default set to  "All Files|*.*||"
	// char * szParam2(Read only):  string ID associated with the element
	//nRequestParam :ignore


// Get Input node information
#define REQUEST_INPUT_NODE_INFO	3
	//int nRequestParam : Zero based node index (node1: 0,  node2: 1,  node3: 2, ...)
	// char * szParam1(Read, Write): Node Label  20 characters maximum.
	//int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
	//pnParam2, szParam2 : ignore



// Get Output node information
#define REQUEST_OUTPUT_NODE_INFO 4  
	//int nRequestParam : Zero based node index (node1: 0,  node2: 1,  node3: 2, ...)
	// char * szParam1(Read, Write): Node Label  20 characters maximum.
	//int * pnParam1(Read, Write) node type: ( 0:Neutral  1:Control  2:Power   4:Mechanical )
	//pnParam2, szParam2 : ignore



// Get Data File information
#define REQUEST_DATAFILE_INFO	5 
	// char * szParam1(Read, Write): Label  20 characters maximum.
	// char * szParam2(Read Only): Full path and file name of Selected file.
	// int * pnParam1(Read, Write):  1: Show Display check box     0: Do not show Display check box
	//nRequestParam, szParam2, pnParam2 : ignore



// Get parameter information
#define REQUEST_PARAM_INFO 6  
	//int nRequestParam(Read only) : Zero based parameter index (parameter1: 0,   parameter2: 1,    parameter3: 2, ...)
	// char * szParam1(Read, Write): Label,  20 characters maximum.
	// char * szParam2(Read, Write): value,  50 characters maximum.
	// int * pnParam1(Read, Write):  Options: DLLBLOCK_OPTION_DISPLAY_CHECKBOX,DLLBLOCK_OPTION_READ_ONLY,DLLBLOCK_OPTION_DISABLE,
    //                                        DLLBLOCK_OPTION_STATIC,DLLBLOCK_OPTION_COMBOBOX,DLLBLOCK_OPTION_FILE,DLLBLOCK_OPTION_ACTION
				//   REQUEST_PARAM_INFO	 szParam1 format for ComboBox (DLLBLOCK_OPTION_COMBOBOX) is:  [label];[ListItem1];[ListItem2];[ListItem3];...;		ex.:  "Jumper type;Master;Slave"
				//   REQUEST_PARAM_INFO	 szParam1 format for File (DLLBLOCK_OPTION_FILE)         is:  [label];[File Filter]     ex.:    "Output file;Image Files|*.bmp;*.jpg;*.gif|Wave Files|*.wav||All Files|*.*||"
				//   REQUEST_PARAM_INFO	 szParam1 format for Button (DLLBLOCK_OPTION_ACTION) is:  [label];[button text]   
	//pnParam2 : if 0 on input, set to 1 to reload everything.  if -1 on input then ignore 

// Grid Data information
#define REQUEST_GRIDDATA_COUNT	21 
	// int * pnParam1(Read, Write):  HIWORD: number of rows,  LOWORD: number of columns
    // int * pnParam2(Read, Write):  //GRID Options:
	// char * szParam1(Read, Write): Column Labels  (20 characters maximum) separated by ';'
	//nRequestParam, szParam2 : ignore

// Grid Data information
#define REQUEST_GRIDCELL_INFO	22 
	// int nRequestParam(Read only) : Grid cell location: [HIWORD: zero based row index,  LOWORD: zero based column index] (Row 1 Column 1: 00000000,   Row 1 Column 2: 00010002,    ...)
	// char * szParam2(Read, Write): value,  50 characters maximum.
	// int * pnParam1(Read, Write):  DLLBLOCK_OPTION_READ_ONLY,DLLBLOCK_OPTION_DISABLE, DLLBLOCK_OPTION_STATIC,DLLBLOCK_OPTION_COMBOBOX, DLLBLOCK_OPTION_ACTION
	//				szParam1 format for ComboBox (DLLBLOCK_OPTION_COMBOBOX) is:  ;[ListItem1];[ListItem2];[ListItem3];...;		ex.:  ";Master;Slave"
	//				szParam1 format for Button (DLLBLOCK_OPTION_ACTION)     is:  ;[button text]   
	//pnParam2 : if 0 on input, set to 1 to reload everything.  if -1 on input then ignore 
	//szParam1: ignore




		
		
		
				 		
		
		
		
		
		
		
		

    


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DLLBLOCK_OPTION_DISPLAY_CHECKBOX		0X00000001
#define DLLBLOCK_OPTION_READ_ONLY				0X00000002
#define DLLBLOCK_OPTION_DISABLE					0X00000004


#define DLLBLOCK_OPTION_EDITTYPE				0X000F0000 

// data is displayed as static text. It's read only  
//   REQUEST_PARAM_INFO	 szParam1 format for Static text is:  [label]		ex.:  "Jumper type"
#define DLLBLOCK_OPTION_STATIC					0X00010000 

// data is restricted to list of values. will show as a combobox in propertybox. 
//   REQUEST_PARAM_INFO	 szParam1 format for ComboBox is:  [label];[ListItem1];[ListItem2];[ListItem3];...;		ex.:  "Jumper type;Master;Slave"
#define DLLBLOCK_OPTION_COMBOBOX				0X00020000 

//   REQUEST_PARAM_INFO	 szParam1 format for File is:  [label];[File Filter]     ex.:    "Output file;Image Files|*.bmp;*.jpg;*.gif|Wave Files|*.wav||All Files|*.*||"
//   this option does not apply to primary filename.
#define DLLBLOCK_OPTION_FILE					0X00040000 


//   REQUEST_PARAM_INFO	 szParam1 format for Button is:  [label];[button text]   
//	If label is not required then  szParam1 should be  ; plus button text. For example for button text of "Settings...", szParam1 should be: ";Settings..."
//  For "Open output file" as label and "..." as button text szParam1 should be: "Open output file;..."
#define DLLBLOCK_OPTION_ACTION					0X00080000 

//   REQUEST_PARAM_INFO	 szParam1 format for checkbox is:  [button text]   
#define DLLBLOCK_OPTION_ACTIONCHECKBOX			0X00090000 

// Parameter is shown on the left on top of node names.
#define DLLBLOCK_OPTION_PRIMARY					0X00000100 


// data is converted to a floating point value for simulation  
//   PSIM will handle formulas, variables and postfix characters for simulation
#define DLLBLOCK_OPTION_FLOATVALUE				0X00100000 


