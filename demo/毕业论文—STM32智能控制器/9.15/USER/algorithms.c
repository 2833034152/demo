#include "algorithms.h"
#include "math.h"
float DeFuzzy(int eLevel,int ecLevel,u8 ID_item)             //����e������Index�ҵ�Kp��Index
{
		switch(ID_item)
		{
				case ID_dKp:
				return fuzzyRuleKp[ecLevel+3][eLevel+3] / Gkp;
				 
				case ID_dKi:
				return fuzzyRuleKi[ecLevel+3][eLevel+3] / Gki;
				 
				case ID_dKd:
				return fuzzyRuleKd[ecLevel+3][eLevel+3] / Gkd;
				 
				default:
				return 0;
		}
 
}
 //����ƫ���ƫ��ı仯
sPID  Fuzzifier(   sPID *  tmp)
{
 
			int eLeftIndex,eRightIndex,ecLeftIndex,ecRightIndex;
			float eLeftMs,eRightMs,ecLeftMs,ecRightMs;//������
			sPID fuzzyDetPID;
	
			float e = 0;
		    float ec = 0;
			e = tmp->e / (100*Ge);
	
			ec = tmp->ec /(100* Gec);
	
	       

			 
	       //���ж�e��ec����ģ���������������������������� ��2.5  ����eLeftIndex = 2 ,e_RightIndex = 3
			eLeftIndex = (e/levelInterval)>3.0?3:(e/levelInterval)<-3.0?-4:(e/levelInterval)>0?(int)(e/levelInterval):(int)(e/levelInterval)-1;
			eRightIndex = eLeftIndex + 1;
			 
	       //����e����eLeftIndex��������     
			eLeftMs = eLeftIndex<-3?0:eLeftIndex==3?1.0:eRightIndex-e/levelInterval;
			eRightMs = eRightIndex>3?0:eRightIndex==-3?1.0:e/levelInterval-eLeftIndex;
			 
			ecLeftIndex = (ec/levelInterval)>3.0?3:(ec/levelInterval)<-3.0?-4:(ec/levelInterval)>0?(int)(ec/levelInterval):(int)(ec/levelInterval)-1;
			ecRightIndex = ecLeftIndex + 1;
			 
			ecLeftMs = ecLeftIndex<-3?0:ecLeftIndex==3?1.0:ecRightIndex-ec/levelInterval;
			ecRightMs = ecRightIndex>3?0:ecRightIndex==-3?1.0:ec/levelInterval-ecLeftIndex;
			 
			 //����Kp��Ҫ�ĸ�Kp�������ֵ
			fuzzyDetPID.Kp = (eLeftMs * ecLeftMs * DeFuzzy(eLeftIndex, ecLeftIndex, ID_dKp)
			+ eLeftMs * ecRightMs * DeFuzzy(eLeftIndex, ecRightIndex, ID_dKp)
			+ eRightMs * ecLeftMs * DeFuzzy(eRightIndex, ecLeftIndex, ID_dKp)
			+ eRightMs * ecRightMs * DeFuzzy(eRightIndex, ecRightIndex, ID_dKp));
			
			fuzzyDetPID.Ki = (eLeftMs * ecLeftMs * DeFuzzy(eLeftIndex, ecLeftIndex, ID_dKi)
			+ eLeftMs * ecRightMs * DeFuzzy(eLeftIndex, ecRightIndex, ID_dKi)
			+ eRightMs * ecLeftMs * DeFuzzy(eRightIndex, ecLeftIndex, ID_dKi)
			+ eRightMs * ecRightMs * DeFuzzy(eRightIndex, ecRightIndex, ID_dKi));
			
			fuzzyDetPID.Kd = (eLeftMs * ecLeftMs * DeFuzzy(eLeftIndex, ecLeftIndex, ID_dKd)
			+ eLeftMs * ecRightMs * DeFuzzy(eLeftIndex, ecRightIndex, ID_dKd)
			+ eRightMs * ecLeftMs * DeFuzzy(eRightIndex, ecLeftIndex, ID_dKd)
			+ eRightMs * ecRightMs * DeFuzzy(eRightIndex, ecRightIndex, ID_dKd));
			
			
			 
			return  fuzzyDetPID;
 
}
 
sPID  pidController( float tarSpeed ,float  curSpeed , sPID * motor)
{
 
//		 motor = {1, 0.5, 0.3 , 0 , 0 ,0 , 0};
//		static float sumE = 0;
//		static int lastE = 0;
		float returnVal = 0;
		 
		sPID dPID = {0, 0, 0 ,0,0,0,0};
//		float e,ec;
                                                                                                                                                                      
		tarSpeed = tarSpeed>MaxMotorSpeed?MaxMotorSpeed:tarSpeed<-MaxMotorSpeed?-MaxMotorSpeed:tarSpeed;
		 
		motor->e = tarSpeed - curSpeed;
		motor->ec = motor->e - motor->lastE;
		motor->sumE += motor->e;
        motor->lastE = motor->e;
 
		//if(fabs(e/tarSpeed)<0.05)//���С��5%
		//dPID = Fuzzifier(motor.e, motor.ec);
	
		dPID =  Fuzzifier(motor);
		 
 //		returnVal = (motor->Kp+dPID.Kp)*motor->e + (motor->Kd+dPID.Kd)*motor->ec + (motor->Ki+dPID.Ki)*motor->sumE;//ֱ�ӷ���U��Ϊλ��ʽ
		return dPID;
//       return  motor;
		//return returnVal;
 
}

