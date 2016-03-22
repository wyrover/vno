@echo off

rem �ü��±��޸����bat�ļ�����,sublime text��Ҫ����Ϊutf-8����!�м�
rem �������ui��Դ��ʱ���������

set RCC=C:\Anaconda2\Library\bin\pyrcc4
set UIC_PY=C:\Anaconda2\Lib\site-packages\PyQt4\uic\pyuic.py

rem ����qrc��Դ
%RCC% -o uipy\usecad_rc.py usecad.qrc

rem ����ui�ļ�
python %UIC_PY% -o uipy\ui_cbm_messagebox.py uifiles\cbm_messagebox.ui
python %UIC_PY% -o uipy\ui_technology_dlg.py uifiles\technology_dlg.ui
python %UIC_PY% -o uipy\ui_tech_mode_dlg.py uifiles\tech_mode_dlg.ui
python %UIC_PY% -o uipy\ui_sample_manage.py uifiles\sample_manage.ui
python %UIC_PY% -o uipy\ui_mine_design_dlg.py uifiles\mine_design_dlg.ui
python %UIC_PY% -o uipy\ui_name_dlg.py uifiles\name_dlg.ui
python %UIC_PY% -o uipy\ui_coal_design_dlg.py uifiles\coal_design_dlg.ui
python %UIC_PY% -o uipy\ui_mine_base_param_dlg.py uifiles\mine_base_param_dlg.ui
python %UIC_PY% -o uipy\ui_coal_param_dlg.py uifiles\coal_param_dlg.ui
python %UIC_PY% -o uipy\ui_decision_dlg.py uifiles\decision_dlg.ui
python %UIC_PY% -o uipy\ui_difficult_eval_dlg.py uifiles\difficult_eval_dlg.ui
python %UIC_PY% -o uipy\ui_high_coal_dlg.py uifiles\high_coal_dlg.ui
python %UIC_PY% -o uipy\ui_high_coals_dlg.py uifiles\high_coals_dlg.ui
python %UIC_PY% -o uipy\ui_low_nearly_coals_dlg.py uifiles\low_nearly_coals_dlg.ui
python %UIC_PY% -o uipy\ui_low_far_coals_dlg.py uifiles\low_far_coals_dlg.ui
python %UIC_PY% -o uipy\ui_low_coal_dlg.py uifiles\low_coal_dlg.ui
python %UIC_PY% -o uipy\ui_mine_gas_reserves_predict_dlg1.py uifiles\mine_gas_reserves_predict_dlg1.ui
python %UIC_PY% -o uipy\ui_mine_gas_reserves_predict_dlg2.py uifiles\mine_gas_reserves_predict_dlg2.ui
python %UIC_PY% -o uipy\ui_mine_gas_reserves_predict_dlg.py uifiles\mine_gas_reserves_predict_dlg.ui
python %UIC_PY% -o uipy\ui_mine_gas_flow_predict_dlg.py uifiles\mine_gas_flow_predict_dlg.ui
python %UIC_PY% -o uipy\ui_mine_gas_flow_predict_design_dlg.py uifiles\mine_gas_flow_predict_design_dlg.ui
python %UIC_PY% -o uipy\ui_tws_gas_flow_predict_dlg.py uifiles\tws_gas_flow_predict_dlg.ui
python %UIC_PY% -o uipy\ui_ws_gas_flow_predict_dlg.py uifiles\ws_gas_flow_predict_dlg.ui
python %UIC_PY% -o uipy\ui_ws_gas_flow_predict_work_dlg.py uifiles\ws_gas_flow_predict_work_dlg.ui
python %UIC_PY% -o uipy\ui_ws_gas_flow_predict_adj_dlg.py uifiles\ws_gas_flow_predict_adj_dlg.ui
python %UIC_PY% -o uipy\ui_high_drilling_tunnel_dlg.py uifiles\high_drilling_tunnel_dlg.ui
python %UIC_PY% -o uipy\ui_high_drilling_design_dlg.py uifiles\high_drilling_design_dlg.ui
python %UIC_PY% -o uipy\ui_high_drilling_site_dlg.py uifiles\high_drilling_site_dlg.ui
python %UIC_PY% -o uipy\ui_high_drilling_pore_dlg.py uifiles\high_drilling_pore_dlg.ui
python %UIC_PY% -o uipy\ui_pore_size_dlg.py uifiles\pore_size_dlg.ui
python %UIC_PY% -o uipy\ui_pore_flow_dlg.py uifiles\pore_flow_dlg.ui
python %UIC_PY% -o uipy\ui_pore_flow_K_dlg.py uifiles\pore_flow_K_dlg.ui
python %UIC_PY% -o uipy\ui_pore_flow_b_dlg.py uifiles\pore_flow_b_dlg.ui
python %UIC_PY% -o uipy\ui_pore_flow_delta_p_dlg.py uifiles\pore_flow_delta_p_dlg.ui
python %UIC_PY% -o uipy\ui_pore_flow_delta_T_dlg.py uifiles\pore_flow_delta_T_dlg.ui
python %UIC_PY% -o uipy\ui_eval_unit_dlg.py uifiles\eval_unit_dlg.ui

python %UIC_PY% -o uipy\ui_gas_design_dlg.py uifiles\gas_design_dlg.ui
python %UIC_PY% -o uipy\ui_gas_design_p1_1_dlg.py uifiles\gas_design_p1_1_dlg.ui
python %UIC_PY% -o uipy\ui_gas_design_p1_2_dlg.py uifiles\gas_design_p1_2_dlg.ui
python %UIC_PY% -o uipy\ui_gas_design_p2_1_dlg.py uifiles\gas_design_p2_1_dlg.ui
python %UIC_PY% -o uipy\ui_gas_design_p2_3_dlg.py uifiles\gas_design_p2_3_dlg.ui
python %UIC_PY% -o uipy\ui_gas_design_p3_2_dlg.py uifiles\gas_design_p3_2_dlg.ui

python %UIC_PY% -o uipy\ui_mainwin.py uifiles\mainwindow.ui
python %UIC_PY% -o uipy\ui_reg_dlg.py uifiles\reg_dlg.ui
python %UIC_PY% -o uipy\ui_login_dlg.py uifiles\login_dlg.ui

python %UIC_PY% -o uipy\ui_curve_draw_dlg.py uifiles\curve_draw_dlg.ui
python %UIC_PY% -o uipy\ui_gas_drilling_radius_dlg.py uifiles\gas_drilling_radius_dlg.ui
python %UIC_PY% -o uipy\ui_gas_drilling_optimize_dlg.py uifiles\gas_drilling_optimize_dlg.ui

rem ����������
rem python main.py

rem ��ͣ
pause