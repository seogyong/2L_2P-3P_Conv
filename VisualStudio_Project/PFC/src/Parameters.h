#ifndef __PARAMETERS__H_
#define __PARAMETERS__H_

#define Tsamp 0.0001
#define pi 3.14159265358979323846
#define PI 3.14159265358979323846
#define ZitaVC  1.0
#define WnVC  100.
#define Cdc  2200.e-6


typedef struct MyData
{
	double P_Sel;
	double t_cnt;
	double fg;
	double w_cc;
	double JetaPLL;
	double WnPLL;
	double Lg;
	double Rg;

	//AD
	double Vdc;
	double Ia;
	double Ib;
	double Ic;
	double Vab_out;
	double Vbc_out;
	double Vca_out;
	double Vtri_new_PS;


	//For Coordinates transformation
	double Va_out;
	double Vb_out;
	double Vc_out;
	double Vds_out;
	double Vqs_out;
	double Ids_out;
	double Iqs_out;
	double Vde_out;
	double Vqe_out;
	double Ide_out;
	double Iqe_out;


	//voltage APF
	double APF_w_v, Kt_v, La_v, V_qs_APF, Vgrid_old;
	//current APF
	double APF_w_c, Kt_c, La_c, I_qs_APF, Igrid_old;



	//PLL
	double theta;
	double Vm;
	double WcPLL;
	double La;
	double Lb;
	double Vde_out_Flt;
	double Vde_out_old;
	double Vqe_out_Flt;
	double Vqe_out_old;
	double Vde_out_err;
	double Vde_out_ref;
	double KpPLL;
	double KiPLL;
	double Vde_out_err_intg;
	double wde_ref;
	double w_rated;
	double Vde_ref_unlimit;
	double Vqe_ref_unlimit;
	double Vde_ref_anti;
	double Vqe_ref_anti;


	//Voltage control
	double Power, Idc, KpVC, KiVC, Vdc_err;
	double Iqe_ref_fb_intg, Iqe_ref_fb, Iqe_ref_ff, Vdc_ref;


	//Current control
	double Ide_ref;
	double Iqe_ref;
	double Ide_err;
	double Iqe_err;
	double Kpc;
	double Kpc_d;
	double Kpc_q;
	double Kic;
	double Kac;
	double Kac_d;
	double Kac_q;
	double Vde_ref_fb_intg;
	double Vqe_ref_fb_intg;
	double Vde_ref_fb;
	double Vqe_ref_fb;
	double Vde_ref_ff;
	double Vqe_ref_ff;
	double Vde_ref;
	double Vqe_ref;
	double Vds_ref;
	double Vqs_ref;
	double Vref_a;
	double Vref_b;
	double Vref_c;


	// Switching condition
	double Vmax;
	double Vmin;
	double Vsn;
	double Vref_an;
	double Vref_bn;
	double Vref_cn;
	double Ta;
	double Tb;
	double Tc;

	// Inverter switching (2-Level)
	int Sa1;
	int Sa2;
	int Sb1;
	int Sb2;
	int Sc1;
	int Sc2;


	//ThirdHarmonics_Compentation_PR()
	double GainPR3;
	double Ids_3rd_err, Iqs_3rd_err, Kt_PR, Ki_PR;
	double W0_PR, Wc_3rd_PR;
	double a1_3rd, a2_3rd, b0_3rd, b1_3rd, b2_HC_3rd;
	double V_3rd_refPR, V_3rd_refPR_old1, V_3rd_refPR_old2;
	double Ids_err_old1, Ids_err_old2;
	double Vds_Ref_comp, Vqs_Ref_comp;

	//FifthHarmonics_Compentation()
	double Ide5th, Iqe5th;
	double Wc5th, Fcl5th, La5th, Lb5th;
	double Ide5thFlt, Iqe5thFlt, Ide5thOld, Iqe5thOld;
	double Ide5thErr, Iqe5thErr, Vde5thIntg, Vqe5thIntg;
	double Kicc5th, Kpcc5th;
	double Vde5thRefFb, Vqe5thRefFb, Vde5thRef, Vqe5thRef, V_5thRef;
	double Vds_5thRef, Vqs_5thRef;

	//SeventhHarmonics_Compentation()
	double Ide7th, Iqe7th;
	double Wc7th, Fcl7th, La7th, Lb7th;
	double Ide7thFlt, Iqe7thFlt, Ide7thOld, Iqe7thOld;
	double Ide7thErr, Iqe7thErr, Vde7thIntg, Vqe7thIntg;
	double Kicc7th, Kpcc7th;
	double Vde7thRefFb, Vqe7thRefFb, Vde7thRef, Vqe7thRef, V_7thRef;
	double Vds_7thRef, Vqs_7thRef;

	// for Notch and low pass Filter Parameters
	double WcTs, denom, La_I_res, Lb_I_res, Lc_I_res, Ld_I_res, Le_I_res;
	double Vde_ref_NOTCH, Vde_ref_NOTCH_old, Vde_ref_NOTCH_old1, Vde_ref_old1;
	double Vqe_ref_NOTCH, Vqe_ref_NOTCH_old, Vqe_ref_NOTCH_old1, Vqe_ref_old1;
	double Vde_ref_Flt, Vde_ref_old, Vqe_ref_Flt, Vqe_ref_old, Wc_ref;
} MyData; //end of struct


#endif
