package com.fr.privilege;

import com.fr.general.ComparatorUtils;
import com.fr.privilege.providers.dao.AbstractPasswordEncode;

public class TestPasswordValidator extends AbstractPasswordEncode{
	@Override
	public String encodePassword(String clinetPassword) {
		return (clinetPassword+"FR");//����ȡ�û����������Ȼ���ں������FR���������ݿ�����ƥ�䡣
	}

}