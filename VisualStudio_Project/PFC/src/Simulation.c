#include <math.h>
#include "Parameters.h"
#include "function.h"
#include <malloc.h>


double m_t_off_switch;
double m_t_start;
double m_Vdc_reference;


void SimulationBegin(const char* szId, int nInputCount, int nOutputCount, int nParameterCount, const char** pszParameters,
	int* pnError, char* szErrorMsg, void** ptrUserData, int nThreadIndex, void* pAppPtr)
{
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	int nParamStartIndex = 0;
	// value of parameter 1
	m_t_off_switch = atof(pszParameters[nParamStartIndex + 0]);
	// value of parameter 1
	m_t_start = atof(pszParameters[nParamStartIndex + 1]);
	// value of parameter 2
	m_Vdc_reference = atof(pszParameters[nParamStartIndex + 2]);
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////


	// Allocate	memory and initialize all variables here.
	MyData* data = (MyData*)malloc(sizeof(MyData));

	data->P_Sel = 0;
	data->t_cnt = 0.;
	data->fg = 60.;
	data->w_cc = 1000.;
	data->JetaPLL = 0.707;
	data->WnPLL = 500.;
	data->Lg = 0.005;
	data->Rg = 0.05;


	//AD
	data->Vdc = 0.;
	data->Ia = 0.;
	data->Ib = 0.;
	data->Ic = 0.;
	data->Vab_out = 0.;
	data->Vbc_out = 0.;
	data->Vca_out = 0.;
	data->Vtri_new_PS = 0.;


	//For Coordinates transformation
	data->Va_out = 0.;
	data->Vb_out = 0.;
	data->Vc_out = 0.;
	data->Vds_out = 0.;
	data->Vqs_out = 0.;
	data->Ids_out = 0.;
	data->Iqs_out = 0.;
	data->Vde_out = 0.;
	data->Vqe_out = 0.;
	data->Ide_out = 0.;
	data->Iqe_out = 0.;


	//voltage APF
	data->APF_w_v = 0., data->Kt_v = 0., data->La_v = 0., data->V_qs_APF = 0., data->Vgrid_old = 0.;
	//current APF
	data->APF_w_c = 0., data->Kt_c = 0., data->La_c = 0., data->I_qs_APF = 0., data->Igrid_old = 0.;



	//PLL
	data->theta = 0.;
	data->Vm = 0.;
	data->WcPLL = 0.;
	data->La = 0.;
	data->Lb = 0.;
	data->Vde_out_Flt = 0.;
	data->Vde_out_old = 0.;
	data->Vqe_out_Flt = 0.;
	data->Vqe_out_old = 0.;
	data->Vde_out_err = 0.;
	data->Vde_out_ref = 0.;
	data->KpPLL = 0.;
	data->KiPLL = 0.;
	data->Vde_out_err_intg = 0.;
	data->wde_ref = 0.;
	data->w_rated = 0.;
	data->Vde_ref_unlimit = 0.;
	data->Vqe_ref_unlimit = 0.;
	data->Vde_ref_anti = 0.;
	data->Vqe_ref_anti = 0.;


	//Voltage control
	data->Power = 0., data->Idc = 0., data->KpVC = 0., data->KiVC = 0., data->Vdc_err = 0.;
	data->Iqe_ref_fb_intg = 0., data->Iqe_ref_fb = 0., data->Iqe_ref_ff = 0., data->Vdc_ref = 0.;


	//Current control
	data->Ide_ref = 0.;
	data->Iqe_ref = 0.;
	data->Ide_err = 0.;
	data->Iqe_err = 0.;
	data->Kpc = 0.;
	data->Kpc_d = 0.;
	data->Kpc_q = 0.;
	data->Kic = 0.;
	data->Kac = 0.;
	data->Kac_d = 0.;
	data->Kac_q = 0.;
	data->Vde_ref_fb_intg = 0.;
	data->Vqe_ref_fb_intg = 0.;
	data->Vde_ref_fb = 0.;
	data->Vqe_ref_fb = 0.;
	data->Vde_ref_ff = 0.;
	data->Vqe_ref_ff = 0.;
	data->Vde_ref = 0.;
	data->Vqe_ref = 0.;
	data->Vds_ref = 0.;
	data->Vqs_ref = 0.;
	data->Vref_a = 0.;
	data->Vref_b = 0.;
	data->Vref_c = 0.;


	// Switching condition
	data->Vmax = 0.;
	data->Vmin = 0.;
	data->Vsn = 0.;
	data->Vref_an = 0.;
	data->Vref_bn = 0.;
	data->Vref_cn = 0.;
	data->Ta = 0.;
	data->Tb = 0.;
	data->Tc = 0.;

	// Inverter switching (2-Level)
	data->Sa1 = 0;
	data->Sa2 = 0;
	data->Sb1 = 0;
	data->Sb2 = 0;
	data->Sc1 = 0;
	data->Sc2 = 0;


	//ThirdHarmonics_Compentation_PR()
	data->GainPR3 = 5.;
	data->Ids_3rd_err = 0., data->Iqs_3rd_err = 0., data->Kt_PR = 0., data->Ki_PR = 0.;
	data->W0_PR = 0., data->Wc_3rd_PR = 0.;
	data->a1_3rd = 0., data->a2_3rd = 0., data->b0_3rd = 0., data->b1_3rd = 0., data->b2_HC_3rd = 0.;
	data->V_3rd_refPR = 0., data->V_3rd_refPR_old1 = 0., data->V_3rd_refPR_old2 = 0.;
	data->Ids_err_old1 = 0., data->Ids_err_old2 = 0.;
	data->Vds_Ref_comp = 0., data->Vqs_Ref_comp = 0.;

	//FifthHarmonics_Compentation()
	data->Ide5th = 0., data->Iqe5th = 0.;
	data->Wc5th = 0., data->Fcl5th = 1., data->La5th = 0., data->Lb5th = 0.;
	data->Ide5thFlt = 0., data->Iqe5thFlt = 0., data->Ide5thOld = 0., data->Iqe5thOld = 0.;
	data->Ide5thErr = 0., data->Iqe5thErr = 0., data->Vde5thIntg = 0., data->Vqe5thIntg = 0.;
	data->Kicc5th = 50., data->Kpcc5th = 2.;
	data->Vde5thRefFb = 0., data->Vqe5thRefFb = 0., data->Vde5thRef = 0., data->Vqe5thRef = 0., data->V_5thRef = 0.;
	data->Vds_5thRef = 0., data->Vqs_5thRef = 0.;

	//SeventhHarmonics_Compentation()
	data->Ide7th = 0., data->Iqe7th = 0.;
	data->Wc7th = 0., data->Fcl7th = 1., data->La7th = 0., data->Lb7th = 0.;
	data->Ide7thFlt = 0., data->Iqe7thFlt = 0., data->Ide7thOld = 0., data->Iqe7thOld = 0.;
	data->Ide7thErr = 0., data->Iqe7thErr = 0., data->Vde7thIntg = 0., data->Vqe7thIntg = 0.;
	data->Kicc7th = 50., data->Kpcc7th = 1.;
	data->Vde7thRefFb = 0., data->Vqe7thRefFb = 0., data->Vde7thRef = 0., data->Vqe7thRef = 0., data->V_7thRef = 0.;
	data->Vds_7thRef = 0., data->Vqs_7thRef = 0.;

	// for Notch and low pass Filter Parameters
	data->WcTs = 0., data->denom = 0., data->La_I_res = 0., data->Lb_I_res = 0., data->Lc_I_res = 0., data->Ld_I_res = 0., data->Le_I_res = 0.;
	data->Vde_ref_NOTCH = 0., data->Vde_ref_NOTCH_old = 0., data->Vde_ref_NOTCH_old1 = 0., data->Vde_ref_old1 = 0.;
	data->Vqe_ref_NOTCH = 0., data->Vqe_ref_NOTCH_old = 0., data->Vqe_ref_NOTCH_old1 = 0., data->Vqe_ref_old1 = 0.;
	data->Vde_ref_Flt = 0., data->Vde_ref_old = 0., data->Vqe_ref_Flt = 0., data->Vqe_ref_old = 0., data->Wc_ref = 0.;


	// ptrUserData will carry the data pointer to the right function and allows multiple instances of the same DLL to have their own data->
	*ptrUserData = data;

	*pnError = 0; //Success
}


void SimulationStep(double t, double delt, double* in, double* out,
	int* pnError, char* szErrorMsg,
	void** ptrUserData, int nThreadIndex, void* pAppPtr)
{
	MyData* data = (MyData*)(*ptrUserData);

	data->t_cnt += delt;

	// For Input Parameters     
	data->Vdc = in[0];
	data->Ia = in[1];
	data->Ib = in[2];
	data->Ic = in[3];
	data->Vab_out = in[4];
	data->Vbc_out = in[5];
	data->Vca_out = in[6];
	data->Vtri_new_PS = in[7];
	data->P_Sel = in[8];


	if (data->t_cnt >= Tsamp)
	{
		if (data->P_Sel == 1)  // for 3Phase PFC Source
		{
			data->Va_out = ((2. * data->Vab_out) + data->Vbc_out) / 3.;
			data->Vb_out = data->Va_out - data->Vab_out;
			data->Vc_out = -data->Vb_out - data->Va_out;

			data->Vds_out = data->Va_out;
			data->Vqs_out = (data->Vb_out - data->Vc_out) / sqrt(3.);

			data->Ids_out = data->Ia;
			data->Iqs_out = (data->Ib - data->Ic) / sqrt(3.);
    
			Coordinates_trans(data);			//전압, 전류 좌표 변환  
		}
		if (data->P_Sel == 0)  // for 2Phase PFC Source
		{
			Voltage_APF(data);
			Current_APF(data);
			Coordinates_trans(data);			//전압, 전류 좌표 변환   
		}

		PLL(data);

		// 출력 전압 크기
		data->Vm = sqrt((data->Vds_out * data->Vds_out) + (data->Vqs_out * data->Vqs_out));
		if (data->Vm < 0.0001) { data->Vm = 0.0001; }

		if (t > m_t_start)
		{
			data->Vdc_ref = m_Vdc_reference;
			VC_inv(data);
			CC_inv(data);
		}

		data->t_cnt -= Tsamp;
	}

	if (t < m_t_off_switch)
	{
		data->Sa1 = 0, data->Sa2 = 0, data->Sb1 = 0, data->Sb2 = 0, data->Sc1 = 0, data->Sc2 = 0;
	}
	else
	{
		if (data->P_Sel == 1)
		{
			Inv_SW_3P(data);
		}
		else
		{
			Inv_SW_2P(data);
			data->Sc1 = 0, data->Sc2 = 0;
		}
	}

	if (t > 0.5)
	{
		//ThirdHarmonics_compentation_PR(data); // 3차 고조파 제어 시작
		//FifthHarmonics_compentation(data); // 5차 고조파 제어 시작
		//SeventhHarmonics_compentation(data); // 7차 고조파 제어 시작
	}


	out[0] = data->Sa1;
	out[1] = data->Sa2;
	out[2] = data->Sb1;
	out[3] = data->Sb2;
	out[4] = data->Sc1;
	out[5] = data->Sc2;
	out[6] = data->Iqe_ref_fb_intg;
	out[7] = data->Iqe_ref;
	out[8] = data->Vdc_ref;
	out[9] = data->theta;
	out[10] = data->Ta;
	out[11] = data->Tb;
	out[12] = data->Tc;
	out[13] = data->Vref_a;
	out[14] = data->Vref_b;
	out[15] = data->Vds_ref;
	out[16] = data->Ids_out;
	out[17] = data->Iqs_out;
	out[18] = data->Vds_out;
	out[19] = data->Vqs_out;
}


void SimulationEnd(const char* szId, void** ptrUserData, int nThreadIndex, void* pAppPtr)
{
	// data allocated in OPENSIMUSER is provided.
	MyData* data = (MyData*)(*ptrUserData);

	// Free all allocated memory here.
	if (data != NULL)
	{
		free(data);
	}
	
	*ptrUserData = NULL;
}
