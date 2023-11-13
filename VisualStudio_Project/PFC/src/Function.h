#pragma once
/**
 * @author  Seogyong Jeong
 * @email   seogyong86@gmail.com
 * @version v1.0
 */


#ifndef __FUNCTION__H_
#define __FUNCTION__H_

void Coordinates_trans(MyData* data);
void Voltage_APF(MyData* data);
void Current_APF(MyData* data);
void PLL(MyData* data);
void VC_inv(MyData* data);
void CC_inv(MyData* data);
void Inv_SW_3P(MyData* data);
void Inv_SW_2P(MyData* data);
void ThirdHarmonics_compentation_PR(MyData* data);
void FifthHarmonics_compentation(MyData* data);
void SeventhHarmonics_compentation(MyData* data);

#endif
