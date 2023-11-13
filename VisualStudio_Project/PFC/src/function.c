#include "Parameters.h"
#include "Function.h"

void Coordinates_trans(MyData* data)
{
	data->Vde_out = data->Vds_out * cos(data->theta) + data->Vqs_out * sin(data->theta);
	data->Vqe_out = -data->Vds_out * sin(data->theta) + data->Vqs_out * cos(data->theta);

	data->Ide_out = data->Ids_out * cos(data->theta) + data->Iqs_out * sin(data->theta);
	data->Iqe_out = -data->Ids_out * sin(data->theta) + data->Iqs_out * cos(data->theta);
}

void Voltage_APF(MyData* data)
{
	// APF(All Pass Filter) : d축 상을 가지고 가상의 q축 상 생성//
	data->APF_w_v = 2 * PI * data->fg;
	data->Kt_v = 2. / Tsamp;
	data->La_v = (data->Kt_v - data->APF_w_v) / (data->Kt_v + data->APF_w_v);
	data->V_qs_APF = (data->La_v) * data->Vab_out - data->Vgrid_old + (data->La_v) * data->V_qs_APF;
	data->Vgrid_old = data->Vab_out;
	data->Vds_out = data->Vab_out;
	data->Vqs_out = -data->V_qs_APF;
}

void Current_APF(MyData* data)
{
	// APF(All Pass Filter) : d축 상을 가지고 가상의 q축 상 생성//
	data->APF_w_c = 2 * PI * data->fg;
	data->Kt_c = 2. / Tsamp;
	data->La_c = (data->Kt_c - data->APF_w_c) / (data->Kt_c + data->APF_w_c);
	data->I_qs_APF = (data->La_c) * data->Ia - data->Igrid_old + (data->La_c) * data->I_qs_APF;
	data->Igrid_old = data->Ia;
	data->Ids_out = data->Ia;
	data->Iqs_out = -data->I_qs_APF;
}

void PLL(MyData* data)
{
	// For Voltage Magnitude
	data->Vm = sqrt((data->Vds_out * data->Vds_out) + (data->Vqs_out * data->Vqs_out));
	if (data->Vm < 0.0001) { data->Vm = 0.0001; }

	// Digital LPF
	data->WcPLL = 1. + 2. * data->JetaPLL * data->WnPLL;
	data->La = (2. - data->WcPLL * Tsamp) / (2. + data->WcPLL * Tsamp);
	data->Lb = (data->WcPLL * Tsamp) / (2. + data->WcPLL * Tsamp);

	data->Vde_out_Flt = (data->La * data->Vde_out_Flt) + (data->Lb * (data->Vde_out + data->Vde_out_old));
	data->Vde_out_old = data->Vde_out;
	data->Vqe_out_Flt = (data->La * data->Vqe_out_Flt) + (data->Lb * (data->Vqe_out + data->Vqe_out_old));
	data->Vqe_out_old = data->Vqe_out;

	data->Vde_out_err = data->Vde_out_ref - data->Vde_out_Flt;

	// For PI controller gain
	data->KpPLL = (2. * data->JetaPLL * data->WnPLL) / data->Vm;
	data->KiPLL = (data->WnPLL * data->WnPLL) / (data->Vm * data->WcPLL);

	data->Vde_out_err_intg += data->Vde_out_err * Tsamp;
	data->wde_ref = (data->KpPLL * data->Vde_out_err) + (data->KiPLL * data->Vde_out_err_intg); // PI 제어기 1차 출력

	//Feedforward
	data->w_rated = 2. * pi * data->fg;
	data->wde_ref = data->wde_ref + data->w_rated;
	data->theta += data->wde_ref * Tsamp;

	if (data->theta > pi) { data->theta -= 2. * pi; }
	else if (data->theta < -pi) { data->theta += 2. * pi; }
}

//DC-link Voltage Control
void VC_inv(MyData* data)
{
	data->KpVC = 2. * ZitaVC * WnVC * Cdc;
	data->KiVC = WnVC * WnVC * Cdc;

	data->Power = (data->Vdc * data->Idc) / 3.;
	data->Iqe_ref_ff = data->Power / ((3. / 2.) * (220. * sqrt(2.)));

	data->Vdc_err = (data->Vdc_ref - data->Vdc);
	data->Iqe_ref_fb_intg += data->KiVC * data->Vdc_err * Tsamp;
	data->Iqe_ref_fb = (data->KpVC * data->Vdc_err) + data->Iqe_ref_fb_intg;

	data->Iqe_ref = data->Iqe_ref_fb + data->Iqe_ref_ff;
}

void CC_inv(MyData* data)
{
	//Current error
	data->Ide_err = data->Ide_ref - data->Ide_out;		//de축 지령 전류
	data->Iqe_err = data->Iqe_ref - data->Iqe_out;		//qe축 지령 전류

	//Gain of current controller
	data->Kpc = data->Lg * data->w_cc;
	data->Kic = data->Rg * data->w_cc;
	data->Kac = (1. / data->Kpc);

	data->Vde_ref_fb_intg += data->Kic * (data->Ide_err - data->Kac * data->Vde_ref_anti) * Tsamp;
	data->Vqe_ref_fb_intg += data->Kic * (data->Iqe_err - data->Kac * data->Vqe_ref_anti) * Tsamp;

	data->Vde_ref_fb = (data->Kpc * data->Ide_err) + (data->Vde_ref_fb_intg);
	data->Vqe_ref_fb = (data->Kpc * data->Iqe_err) + (data->Vqe_ref_fb_intg);

	//feedforward
	data->Vde_ref_ff = 0;
	data->Vqe_ref_ff = 0;

	data->Vde_ref = data->Vde_ref_fb + data->Vde_ref_ff;
	data->Vqe_ref = data->Vqe_ref_fb + data->Vqe_ref_ff;

	data->Vde_ref_unlimit = data->Vde_ref;
	data->Vqe_ref_unlimit = data->Vqe_ref;

	// Limit Vde_ref and Vqe_ref within SVPWM modulation range
	if (data->Vde_ref > data->Vdc / sqrt(3.))			data->Vde_ref = data->Vdc / sqrt(3.);
	else if (data->Vde_ref < -data->Vdc / sqrt(3.))	data->Vde_ref = -data->Vdc / sqrt(3.);
	if (data->Vqe_ref > data->Vdc / sqrt(3.))			data->Vqe_ref = data->Vdc / sqrt(3.);
	else if (data->Vqe_ref < -data->Vdc / sqrt(3.))	data->Vde_ref = -data->Vdc / sqrt(3.);

	data->Vde_ref_anti = data->Vde_ref_unlimit - data->Vde_ref;
	data->Vqe_ref_anti = data->Vqe_ref_unlimit - data->Vqe_ref;

	data->Vds_ref = data->Vds_ref + data->Vds_5thRef + data->Vds_7thRef;
	data->Vqs_ref = data->Vqs_ref + data->Vqs_5thRef + data->Vqs_7thRef;

	//Vde, Vqe --> Vds, Vqs
	data->Vds_ref = data->Vde_ref * cos(data->theta) - data->Vqe_ref * sin(data->theta);
	data->Vqs_ref = data->Vde_ref * sin(data->theta) + data->Vqe_ref * cos(data->theta);

	if (data->P_Sel == 1)
	{
		//Vds, Vqs --> Vref_a, Vref_b, Vref_c
		data->Vref_a = data->Vds_ref / (data->Vdc);
		data->Vref_b = ((-1. / 2.) * data->Vds_ref + (sqrt(3.) / 2.) * data->Vqs_ref) / (data->Vdc);
		data->Vref_c = ((-1. / 2.) * data->Vds_ref - (sqrt(3.) / 2.) * data->Vqs_ref) / (data->Vdc);

		if (data->Vref_a > data->Vref_b)
		{
			data->Vmax = data->Vref_a;
			data->Vmin = data->Vref_b;
		}
		else
		{
			data->Vmax = data->Vref_b;
			data->Vmin = data->Vref_a;
		}
		if (data->Vref_c > data->Vmax)
		{
			data->Vmax = data->Vref_c;
		}
		if (data->Vref_c < data->Vmin)
		{
			data->Vmin = data->Vref_c;
		}

		data->Vsn = -(data->Vmax + data->Vmin) / 2.;

		data->Vref_an = data->Vref_a + data->Vsn + 0.5;
		data->Vref_bn = data->Vref_b + data->Vsn + 0.5;
		data->Vref_cn = data->Vref_c + data->Vsn + 0.5;

		data->Ta = data->Vref_an + data->V_3rd_refPR;
		data->Tb = data->Vref_bn + data->V_3rd_refPR;
		data->Tc = data->Vref_cn + data->V_3rd_refPR;
	}

	if (data->P_Sel == 0)
	{
		if (data->Vds_ref > data->Vdc) { data->Vds_ref = data->Vdc; }
		if (data->Vds_ref < -data->Vdc) { data->Vds_ref = -data->Vdc; }

		data->Vref_a = data->Vds_ref / (data->Vdc) + 0.5;
		data->Vref_b = -data->Vds_ref / (data->Vdc) + 0.5;
	}
}

void Inv_SW_3P(MyData* data)
{
	if (data->Ta > data->Vtri_new_PS) { data->Sa1 = 1; data->Sa2 = 0; }
	else if (data->Ta < data->Vtri_new_PS) { data->Sa1 = 0; data->Sa2 = 1; }

	if (data->Tb > data->Vtri_new_PS) { data->Sb1 = 1; data->Sb2 = 0; }
	else if (data->Tb < data->Vtri_new_PS) { data->Sb1 = 0; data->Sb2 = 1; }

	if (data->Tc > data->Vtri_new_PS) { data->Sc1 = 1; data->Sc2 = 0; }
	else if (data->Tc < data->Vtri_new_PS) { data->Sc1 = 0; data->Sc2 = 1; }
}

void Inv_SW_2P(MyData* data)
{
	if (data->Vtri_new_PS <= data->Vref_a)
	{
		data->Sa1 = 1, data->Sa2 = 0;
	}
	else
	{
		data->Sa1 = 0, data->Sa2 = 1;
	}
	if (data->Vtri_new_PS <= data->Vref_b)
	{
		data->Sb1 = 1, data->Sb2 = 0;
	}
	else
	{
		data->Sb1 = 0, data->Sb2 = 1;
	}
}

//계통 3차 고조파 제어_PR
void ThirdHarmonics_compentation_PR(MyData* data)
{
	data->Ids_3rd_err = -data->Ids_out;
	data->Iqs_3rd_err = -data->Iqs_out;

	// 게인 구하기
	data->Kt_PR = 2. / Tsamp;
	data->Ki_PR = 100.;
	data->W0_PR = 3. * 2. * PI * 60.;
	data->Wc_3rd_PR = 1.;

	data->a1_3rd = 2. * data->Ki_PR * data->Kt_PR * data->Wc_3rd_PR;
	data->a2_3rd = 2. * data->Ki_PR * data->Kt_PR * data->Wc_3rd_PR;
	data->b0_3rd = data->Kt_PR * data->Kt_PR + 2. * data->Kt_PR * data->Wc_3rd_PR + data->W0_PR * data->W0_PR;
	data->b1_3rd = 2. * data->Kt_PR * data->Kt_PR - 2. * data->W0_PR * data->W0_PR;
	data->b2_HC_3rd = data->Kt_PR * data->Kt_PR - 2. * data->Kt_PR * data->Wc_3rd_PR + data->W0_PR * data->W0_PR;

	//z변환 후
	data->V_3rd_refPR = (data->a1_3rd * (data->Ids_3rd_err - data->Ids_err_old2) + data->b1_3rd * (data->V_3rd_refPR_old1) - data->b2_HC_3rd * (data->V_3rd_refPR_old2)) / data->b0_3rd;

	data->V_3rd_refPR_old2 = data->V_3rd_refPR_old1;
	data->V_3rd_refPR_old1 = data->V_3rd_refPR;

	data->Ids_err_old2 = data->Ids_err_old1;
	data->Ids_err_old1 = data->Ids_3rd_err;
}

//계통 5차 고조파 제어
void FifthHarmonics_compentation(MyData* data)
{
	//5차 전류 동기 좌표계 변환	
	data->Ide5th = cos(data->theta * 5.) * data->Ids_out + sin(data->theta * 5.) * data->Iqs_out;
	data->Iqe5th = -sin(data->theta * 5.) * data->Ids_out + cos(data->theta * 5.) * data->Iqs_out;

	//LPF
	data->Wc5th = 2. * PI * data->Fcl5th;
	data->La5th = (2. - data->Wc5th * Tsamp) / (2. + data->Wc5th * Tsamp);
	data->Lb5th = (data->Wc5th * Tsamp) / (2. + data->Wc5th * Tsamp);

	data->Ide5thFlt = data->La5th * data->Ide5thFlt + data->Lb5th * (data->Ide5th + data->Ide5thOld);
	data->Iqe5thFlt = data->La5th * data->Iqe5thFlt + data->Lb5th * (data->Iqe5th + data->Iqe5thOld);

	data->Ide5thOld = data->Ide5th;
	data->Iqe5thOld = data->Iqe5th;

	//PI 제어기
	data->Ide5thErr = (0. - data->Ide5thFlt);
	data->Iqe5thErr = (0. - data->Iqe5thFlt);

	data->Vde5thIntg += data->Kicc5th * data->Ide5thErr * Tsamp;
	data->Vde5thRefFb = data->Vde5thIntg + data->Kpcc5th * data->Ide5thErr;

	data->Vqe5thIntg += data->Kicc5th * data->Iqe5thErr * Tsamp;
	data->Vqe5thRefFb = data->Vqe5thIntg + data->Kpcc5th * data->Iqe5thErr;

	data->Vde5thRef = data->Vde5thRefFb;
	data->Vqe5thRef = data->Vqe5thRefFb;

	//5차고조파 지령 보상 전압
	data->Vds_5thRef = cos(data->theta * 5.) * data->Vde5thRef - sin(data->theta * 5.) * data->Vqe5thRef;
	data->Vqs_5thRef = sin(data->theta * 5.) * data->Vde5thRef + cos(data->theta * 5.) * data->Vqe5thRef;
}

//계통 7차 고조파 제어
void SeventhHarmonics_compentation(MyData* data)
{
	//7차 전류 동기 좌표계 변환	
	data->Ide7th = cos(-data->theta * 7.) * data->Ids_out + sin(-data->theta * 7.) * data->Iqs_out;
	data->Iqe7th = -sin(-data->theta * 7.) * data->Ids_out + cos(-data->theta * 7.) * data->Iqs_out;

	//LPF
	data->Wc7th = 2. * PI * data->Fcl7th;
	data->La7th = (2. - data->Wc7th * Tsamp) / (2. + data->Wc7th * Tsamp);
	data->Lb7th = (data->Wc7th * Tsamp) / (2. + data->Wc7th * Tsamp);

	data->Ide7thFlt = data->La7th * data->Ide7thFlt + data->Lb7th * (data->Ide7th + data->Ide7thOld);
	data->Iqe7thFlt = data->La7th * data->Iqe7thFlt + data->Lb7th * (data->Iqe7th + data->Iqe7thOld);

	data->Ide7thOld = data->Ide7th;
	data->Iqe7thOld = data->Iqe7th;

	//PI 제어기
	data->Ide7thErr = 0. - data->Ide7thFlt;
	data->Iqe7thErr = 0. - data->Iqe7thFlt;

	data->Vde7thIntg += data->Kicc7th * data->Ide7thErr * Tsamp;
	data->Vde7thRefFb = data->Vde7thIntg + data->Kpcc7th * data->Ide7thErr;

	data->Vqe7thIntg += data->Kicc7th * data->Iqe7thErr * Tsamp;
	data->Vqe7thRefFb = data->Vqe7thIntg + data->Kpcc7th * data->Iqe7thErr;

	data->Vde7thRef = data->Vde7thRefFb;
	data->Vqe7thRef = data->Vqe7thRefFb;

	//7차고조파 지령 보상 전압
	data->Vds_7thRef = cos(data->theta * 7.) * data->Vde7thRef - sin(data->theta * 7.) * data->Vqe7thRef;
	data->Vqs_7thRef = sin(data->theta * 7.) * data->Vde7thRef + cos(data->theta * 7.) * data->Vqe7thRef;
}
