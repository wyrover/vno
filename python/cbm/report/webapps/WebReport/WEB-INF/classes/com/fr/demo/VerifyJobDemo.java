package com.fr.demo;  

import java.util.logging.Level;  
import java.util.logging.Logger;  
import com.fr.base.FRContext;  
import com.fr.base.Utils;  
import com.fr.data.DefinedVerifyJob;  
import com.fr.data.JobValue;  
import com.fr.function.LOG;  
import com.fr.script.Calculator;  
  
public class VerifyJobDemo  extends DefinedVerifyJob{  
    /* 
     * ����Ҫ�����˽�б���,�������ɸģ���ʾУ��״̬ 
     * 0  ��ʾУ��ɹ���Ĭ��У��״̬λΪ0 
     * 1  ��ʾУ��ʧ�� 
     */  
    private int type = 0;   
      
    /** 
     * ��ģ���Զ����¼����ӵ����� ��������������ж�Ӧʱ������Զ���ֵ�ڴ˶�Ӧ���� 
     */  
    private JobValue salenum;   // JobValue��Ӧ��Ԫ��  
    private int minnum;       // �ǵ�Ԫ�����Ӧ��������ֵ  
  
    public void doJob(Calculator calculator) throws Exception {  
        /* 
         * ������ṩһ���򵥵��ж���ģ��ִ�й��� 
         * У�����Ϊ������Ҫ���ڵ�����С������salenum >= minnum 
         * У�鲻ͨ��,��ʾ������ֵ����С����С������ 
         */  
        if(salenum != null){  
            int sale = 0;  
            if(salenum.getValue() instanceof Integer){ //����Ԫ��ֵתΪ�����Ա����ڱȽ�  
                sale = (Integer)salenum.getValue();  
  
                  
            }else {  
                sale = Integer.parseInt(Utils.objectToString(salenum.getValue()));  
            }  
              
            if(sale < minnum){ //У���ж�  
                type = 1;  
            }  
        }else {  
            type = 1;  
        }  
  
    }  
  
    public String getMessage() {  
        // ����У��״̬�ǳɹ�����ʧ�ܣ����ö�Ӧ�ķ�����Ϣ  
        if(type == 0){  
            return "��ϲ�㣬У��ɹ�";  
        }else{  
            return "����ֵ����С����С����";  
        }  
          
    }  
    public int getType() {  
        // ����У��״̬  
        return type;  
    }

	@Override
	public void doFinish(Calculator arg0) throws Exception {
		// TODO Auto-generated method stub
		
	}  
      
}