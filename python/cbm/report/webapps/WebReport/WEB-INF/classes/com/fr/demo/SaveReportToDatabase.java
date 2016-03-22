package com.fr.demo;  

import java.io.File;  
import java.io.FileInputStream;  
import java.io.InputStream;  
import java.sql.Connection;  
import java.sql.DriverManager;  
import java.sql.PreparedStatement;
import com.fr.base.Env; 
import com.fr.dav.LocalEnv;

public class SaveReportToDatabase {  
    public static void main(String[] args) {  
        SaveReport();  
    }  
    private static void SaveReport() {  
        try {  
            // �������ݿ�  
            String driver = "com.mysql.jdbc.Driver";  
            String url = "jdbc:mysql://192.168.100.252:3306/test?useUnicode=true&characterEncoding=gbk";  
            String user = "root";  
            String pass = "mysql252";  
            Class.forName(driver);            
            java.sql.Connection conn = java.sql.DriverManager.getConnection(url, user, pass);
            PreparedStatement presmt = conn.prepareStatement("insert into test.report1 values(?,?)");
            conn.setAutoCommit(false);
            // ������Ҫ��������ģ���ļ� 
            Env newEnv = new LocalEnv("E:\\FineReport_7.0\\WebReport\\WEB-INF");
            String envPath = newEnv.getPath();  
            File cptfile = new File(envPath  
                    + "\\reportlets\\GettingStarted.cpt");  
            int lens = (int) cptfile.length();  
            InputStream ins = new FileInputStream(cptfile);  
            // ��ģ�屣�����  
            presmt.setString(1, "gettingstarted.cpt"); // ��һ���ֶδ��ģ�����·��  
            presmt.setBinaryStream(2, ins, lens); // �ڶ����ֶδ��ģ���ļ��Ķ�������  
            presmt.execute();  
            conn.commit();  
            presmt.close();  
            conn.close();  
        } catch (Exception e) {  
            e.printStackTrace();  
        }  
    }  
}