package com.fr.privilege;

import com.fr.general.ComparatorUtils;
import com.fr.privilege.providers.dao.AbstractPasswordEncode;

public class TestPasswordValidatorUser extends AbstractPasswordEncode {

    /**
     * ������������������㷨���������ݿ�����=FR+�û���+����+RF������true
     * @param localPassword �洢�����ݿ��е�����
     * @param clientPassword �û����������
     * @param clientUsername �û���
     * @return �Ƿ���֤�ɹ�
     */
    public String encodePassword(String clientPassword, String clientUsername) {
       return "FR" + clientUsername + clientPassword + "RF";
     
    }

    /**
     * ��֤����ʱ�Ƿ�Ҫ�����û���
     */
    public boolean shouldIgnoreUsername() {
        return false;
    }

	@Override
	public String encodePassword(String arg0) {
		// TODO Auto-generated method stub
		return null;
	}

    /**
     * 2��������������֤������ֱ��return false
     */
    }